#include "ClangParsing\ASTVisitorGlobal.h"
#include "ClangParsing\CommandLineOptions.h"
#include "Utils\Utils.h"
#include <queue>

using namespace std;
using namespace clang;
using namespace Utils::System;
using namespace Utils::DataConversion;

string SCCL::ASTVisitorGlobal::getNameForFunc(const FunctionDecl *decl)
{

	string FileId = "";
	if (decl->getStorageClass() == SC_Static)
	{
		assert(CurrentFileId && "File id 0 reserved for extern");
		char buf[9] = {};
		FileId += string(itoa(CurrentFileId - 1, buf, 36)) += "~";
		//this works without collision going on the notion that no one can add "~" to a function name

	}

	if (isa<CXXMethodDecl>(decl))
	{
		const CXXMethodDecl *methodDecl = cast<const CXXMethodDecl>(decl);
		const CXXRecordDecl *record = methodDecl->getParent();
		return FileId + record->getNameAsString() + "::" + methodDecl->getNameAsString();
	}
	else
	{
		return FileId + decl->getNameAsString();
	}
}

void SCCL::ASTVisitorGlobal::addStaticPadding(size_t count)
{
	if (Option_EntryFunctionPadding)
	{
		isCurrentExprEvaluable = false;
		scriptData.getCurrentStatic()->addOpSetThisStaticMult(scriptData, 0, count);
		scriptData.getCurrentStatic()->setDynamic();
	}
	else
		scriptData.getCurrentStatic()->pushNullInit(count, scriptData.getStackWidth());
}

void SCCL::ASTVisitorGlobal::addStatic(int32_t value)
{
	if (!isCurrentExprEvaluable || Option_EntryFunctionPadding)
	{
		isCurrentExprEvaluable = false;
		doesCurrentValueNeedSet = true;
		scriptData.getCurrentStatic()->addOpPushInt(value);
		scriptData.getCurrentStatic()->setDynamic();
	}
	else
	{
		scriptData.getCurrentStatic()->pushInit32(value, scriptData.getEndian());
		scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
	}
}

string SCCL::ASTVisitorGlobal::dumpName(const NamedDecl *ND)
{
	if (ND->getDeclName())
	{

		return ND->getNameAsString();
	}
	return "";
}

inline void SCCL::ASTVisitorGlobal::resetIntIndex()
{
	if (intIndex != 0)
		intIndex = 0;
}

bool SCCL::ASTVisitorGlobal::VisitDecl(Decl *D)
{
	if (isa<VarDecl>(D))
	{
		globalVarDecl = cast<VarDecl>(D);
		if (globalVarDecl->hasGlobalStorage())
		{
			//globalVarDecl->getStorageClass() == SC_Static
			if (globalVarDecl->hasAttr<GlobalVariableAttr>())
			{
				if (globalVarDecl->getStorageClass() == SC_None)
				{
					if (globalVarDecl->hasInit())
					{
						Throw("Global variables cannot be initialised", TheRewriter, D->getSourceRange());
					}
				}
				else
				{
					Throw("Global variables cannot have a storage class associated with them", TheRewriter, globalVarDecl->getSourceRange());
				}

			}
			else
			{
				bool isLocal = globalVarDecl->isStaticLocal();
				//TODO: this will have to catch externing vars
				if ((!isLocal && scriptData.findStatic(dumpName(cast<NamedDecl>(D))) == NULL) || (isLocal && scriptData.findLocalStatic(globalVarDecl->getLocation().getRawEncoding()) == NULL))
				{
					string varName = dumpName(cast<NamedDecl>(D));

					const Expr *initializer = globalVarDecl->getAnyInitializer();


					switch (globalVarDecl->getStorageClass())
					{
						case SC_None:
							scriptData.addStaticNewDecl(varName, getSizeFromBytes(getSizeOfType(globalVarDecl->getType().getTypePtr())), false);
							break;
						case SC_Extern:
							if (initializer)
								scriptData.addStaticNewDecl(varName, getSizeFromBytes(getSizeOfType(globalVarDecl->getType().getTypePtr())), false);
							else
								return true;//this is prototyped
							break;
						case SC_Static:
							if (globalVarDecl->isStaticLocal())
							{
								scriptData.addStaticLocalNewDecl(varName, getSizeFromBytes(getSizeOfType(globalVarDecl->getType().getTypePtr())), globalVarDecl->getLocation().getRawEncoding());
							}
							else
							{
								scriptData.addStaticNewDecl(varName, getSizeFromBytes(getSizeOfType(globalVarDecl->getType().getTypePtr())), true);
							}
							break;
						default:
							Throw("Unhandled Storage Class", TheRewriter, globalVarDecl->getSourceRange());
					}

					resetIntIndex();
					savedType = nullptr;

					isCurrentExprEvaluable = true;
					doesCurrentValueNeedSet = false;

					if (initializer)
					{

						ParseLiteral(initializer, false, true);

						if (doesCurrentValueNeedSet)
						{
							scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
						}
						scriptData.getCurrentStatic()->fillCapacity(scriptData.getStackWidth());
					}
					else
					{
						if (Option_EntryFunctionPadding)
						{
							scriptData.getCurrentStatic()->addOpDynamicNullThisStatic(scriptData);
						}
						scriptData.getCurrentStatic()->fillCapacity(scriptData.getStackWidth());
					}


					//if (scriptData.getStaticSize() > staticInc)
					//	Warn("Static Overflow Old:" + to_string(scriptData.getStaticSize()) + " New:" + to_string(staticInc));
					//
					//if (scriptData.getStaticSize() != scriptData.getStaticCapacity())
					//	Throw("not all values in static decl were initialized");

				}
				else
				{
					if (globalVarDecl->getStorageClass() != SC_Extern)
						Throw("Var " + dumpName(cast<NamedDecl>(D)) + " is already defined", TheRewriter, D->getLocStart());
				}

			}
		}
	}
	return true;
}

int32_t SCCL::ASTVisitorGlobal::ParseLiteral(const Expr *e, bool isAddr, bool isLtoRValue)
{
	Expr::EvalResult result;

	if (isa<ImplicitValueInitExpr>(e))
	{
		const ImplicitValueInitExpr *ivie = cast<const ImplicitValueInitExpr>(e);

		const Type* type = ivie->getType().getTypePtr();
		size_t count = getSizeFromBytes(getSizeOfType(type));

		addStaticPadding(count);

		return true;
	}
	else if (e->EvaluateAsRValue(result, context))
	{
		if (!isLtoRValue)
		{
			Warn("Static value was dropped");
			return -1;
		}
		if (result.Val.isInt())
		{

			int64_t resValue = result.Val.getInt().getSExtValue();

			if (doesInt64FitIntoInt32(resValue))
			{
				string value = to_string(resValue);
				Warn("Integer overflow. Value: " + value + " is out of bounds of (-2,147,483,648 to 2,147,483,647). Changed value to " + to_string((int32_t)resValue), TheRewriter, e->getExprLoc(), e->getExprLoc().getLocWithOffset(value.length() - 1));
			}
			const Type* typeE = e->getType().getTypePtr();
			const Type* type = typeE;//globalVarDecl->getType().getTypePtr();

			if (savedType == nullptr)
				savedType = const_cast<Type*>(type);
			else if (type != savedType)//if type change with out identifier// --------- NEED TO TEST TYPE CHANGE TO SAME TYPE WITHOUT IDENTIFIER FOR BUGS ---------
			{
				resetIntIndex();
				isCurrentExprEvaluable = true;
				savedType = const_cast<Type*>(type);
			}

			if (type->isCharType())
			{
				//if (intIndex == 0)
				//	scriptData.addStaticInit();
				//
				//scriptData.modifyLastInitStaticByte(resValue, intIndex);

				if (++intIndex >= stackWidth)
					intIndex = 0;

				//TODO:  if (!isCurrentExprEvaluable)
				scriptData.getCurrentStatic()->pushInit8(resValue);
			}
			else if (type->isSpecificBuiltinType(BuiltinType::Kind::Short) || type->isSpecificBuiltinType(BuiltinType::Kind::UShort))
			{
				//if (intIndex == 0)
				//	scriptData.addStaticInit();
				//
				//scriptData.modifyLastInitStaticShort(resValue, intIndex);

				intIndex += 2;
				if (intIndex >= stackWidth)
					intIndex = 0;

				//TODO:  if (!isCurrentExprEvaluable)
				scriptData.getCurrentStatic()->pushInit16(resValue, scriptData.getEndian());
			}
			else if (!isCurrentExprEvaluable || Option_EntryFunctionPadding)
			{
				isCurrentExprEvaluable = false;
				doesCurrentValueNeedSet = true;
				scriptData.getCurrentStatic()->addOpPushInt(resValue);
				scriptData.getCurrentStatic()->setDynamic();
			}
			else
			{

				scriptData.getCurrentStatic()->pushInit32(resValue, scriptData.getEndian());
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
			}

			return true;
		}
		else if (result.Val.isFloat())
		{
			if (!isCurrentExprEvaluable || Option_EntryFunctionPadding)
			{
				isCurrentExprEvaluable = false;
				doesCurrentValueNeedSet = true;
				scriptData.getCurrentStatic()->addOpPushFloat((float)extractAPFloat(result.Val.getFloat()));
				scriptData.getCurrentStatic()->setDynamic();
			}
			else
			{
				scriptData.getCurrentStatic()->pushInit32(FloatToInt((float)extractAPFloat(result.Val.getFloat())), scriptData.getEndian());
			}
			return true;
		}
		else if (result.Val.isComplexFloat())
		{
			if (!isCurrentExprEvaluable || Option_EntryFunctionPadding)
			{
				isCurrentExprEvaluable = false;
				doesCurrentValueNeedSet = true;
				scriptData.getCurrentStatic()->addOpPushFloat((float)extractAPFloat(result.Val.getComplexFloatReal()));
				scriptData.getCurrentStatic()->addOpPushFloat((float)extractAPFloat(result.Val.getComplexFloatImag()));
				scriptData.getCurrentStatic()->setDynamic();
			}
			else
			{
				scriptData.getCurrentStatic()->pushInit32(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatReal())), scriptData.getEndian());
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				scriptData.getCurrentStatic()->pushInit32(FloatToInt((float)extractAPFloat(result.Val.getComplexFloatImag())), scriptData.getEndian());
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
			}
			return true;
		}
		else if (result.Val.isComplexInt())
		{
			if (!isCurrentExprEvaluable || Option_EntryFunctionPadding)
			{
				isCurrentExprEvaluable = false;
				doesCurrentValueNeedSet = true;
				scriptData.getCurrentStatic()->addOpPushInt(result.Val.getComplexIntReal().getSExtValue());
				scriptData.getCurrentStatic()->addOpPushInt(result.Val.getComplexIntImag().getSExtValue());
				scriptData.getCurrentStatic()->setDynamic();
			}
			else
			{
				scriptData.getCurrentStatic()->pushInit32(result.Val.getComplexIntReal().getSExtValue(), scriptData.getEndian());
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
				scriptData.getCurrentStatic()->pushInit32(result.Val.getComplexIntImag().getSExtValue(), scriptData.getEndian());
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());

			}
			return true;
		}
	}

	if (isa<StringLiteral>(e))
	{
		const StringLiteral *literal = cast<const StringLiteral>(e);
		if (literal->getString().str().length() > 0)
		{
			if (Option_EntryFunctionPadding)
			{
				isCurrentExprEvaluable = false;
				scriptData.getCurrentStatic()->addOpPushString(literal->getString().str());
				scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
				scriptData.getCurrentStatic()->setDynamic();
			}
			else
			{
				scriptData.getCurrentStatic()->pushStringInit(literal->getString().str(), scriptData.getStackWidth() * getSizeFromBytes(getLiteralSizeOfType(e->getType().getTypePtr())));
				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());
			}

			//string strlit = literal->getString().str();
			//e->getType().getTypePtr();
			//
			//int32_t strsize = getLiteralSizeOfType(e->getType().getTypePtr());
			//
			//int32_t buffer = 0;
			//int32_t i = 0, b = 0;
			//for (; i < strsize; i++, b++)
			//{
			//	if (b >= stackWidth)
			//	{
			//		scriptData.addStaticInitBig(buffer);
			//		b = 0;
			//		buffer = 0;
			//
			//		if (i >= (int32_t)strlit.length())
			//		{
			//			scriptData.addStaticInit(0, Utils::Math::CeilDivInt(strsize - i, stackWidth));
			//			break;
			//		}
			//	}
			//	if (i >= (int32_t)strlit.length())
			//		((uint8_t*)&buffer)[b] = 0;//add padding
			//	else
			//		((uint8_t*)&buffer)[b] = strlit[i];
			//
			//}
			//if (b != 0)
			//	scriptData.addStaticInitBig(buffer);

		}

		return true;
	}
	else if (isa<InitListExpr>(e))
	{
		const InitListExpr *I = cast<const InitListExpr>(e);
		uint32_t size = getSizeFromBytes(getSizeOfType(I->getType().getTypePtr()));
		size_t curSize = scriptData.getCurrentStatic()->getStackInitSize(scriptData.getStackWidth());
		resetIntIndex();

		if (I->getType()->isStructureType())
		{
			const RecordType *record = I->getType()->getAsStructureType();


			if (RecordDecl *rd = record->getDecl())
			{
				queue<QueuedBF> QueuedBitfields;

				uint32_t offset = 0;
				uint32_t currentRes = 0;
				uint32_t size = 0;
				uint32_t currentBitFieldSize = 0;
				auto IncCurrentBitSize = [&] () -> void
				{
					assert(currentBitFieldSize <= 32 && "currentBitSize too big");

					addStatic((int32_t)currentRes);

					//pop unevaluable bitfield inits
					while (QueuedBitfields.size())
					{
						ParseLiteral(QueuedBitfields.front().Expr, false, true);

						scriptData.getCurrentStatic()->addOpAddBitField(QueuedBitfields.front().Data.offset, QueuedBitfields.front().Data.width);
						//set dynamic is not needed here because addStatic adds it

						QueuedBitfields.pop();
					}
					offset += 4;
					currentBitFieldSize = 0;
					currentRes = 0;
				};

				uint32_t i = 0;
				for (const FieldDecl *CS : rd->fields())
				{
					if (i < I->getNumInits())
					{
						if (CS->isBitField())
						{
							uint32_t bWidth = checkBitFieldWidth(CS), bOffset = 0;

							if (currentBitFieldSize + bWidth <= 32)
							{
								bOffset = currentBitFieldSize;
								currentBitFieldSize += bWidth;
							}
							else
							{
								IncCurrentBitSize();
								bOffset = currentBitFieldSize;
								currentBitFieldSize += bWidth;
							}


							if (I->getInit(i)->EvaluateAsRValue(result, context) && !result.HasSideEffects)
							{
								if (result.Val.isInt())
								{
									int32_t finalValue;
									if (CheckExprForSizeOf(e->IgnoreParens(), &finalValue));
									else
									{
										int64_t resValue = result.Val.getInt().getSExtValue();

										if (doesInt64FitIntoInt32(resValue))
										{
											string value = to_string(resValue);
											Warn("Integer overflow. Value: " + value + " is out of bounds of (-2,147,483,648 to 2,147,483,647). Changed value to " + to_string((int32_t)resValue), TheRewriter, e->getExprLoc(), e->getExprLoc().getLocWithOffset(value.length() - 1));
										}

										if (e->getType()->isBooleanType() && (int32_t)resValue == -1)
											resValue = 1;

										finalValue = (int32_t)resValue;
									}


									Utils::Bitwise::set_bits_in_range(&currentRes, bOffset, Utils::Bitwise::bitCountToIntEnd(bOffset, bWidth), finalValue & Utils::Bitwise::revbitmask(bWidth));

								}

							}
							else
							{
								isCurrentExprEvaluable = false;
								//cant eval add to bit add list
								const BitfieldData d = { bWidth, bOffset };
								QueuedBitfields.push({ d, I->getInit(i) });
							}

							i++;
							continue;
						}
						else if (currentBitFieldSize)
							IncCurrentBitSize();

						offset += max(getSizeOfType(CS->getType().getTypePtr()), stackWidth);

						isCurrentExprEvaluable = true;
						doesCurrentValueNeedSet = false;
						ParseLiteral(I->getInit(i), false, true);
						if (doesCurrentValueNeedSet)
							scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);


						i++;
					}
					else
						break;
				}
				if (currentBitFieldSize)
					IncCurrentBitSize();

				scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());

				resetIntIndex();
				isCurrentExprEvaluable = true;
				doesCurrentValueNeedSet = false;

				while (offset < size)
				{
					addStaticPadding(1);
					offset += stackWidth;
				}

				return true;
			}

		}

		for (uint32_t i = 0; i < I->getNumInits(); i++)
		{
			isCurrentExprEvaluable = true;
			doesCurrentValueNeedSet = false;
			ParseLiteral(I->getInit(i), false, true);
			if (doesCurrentValueNeedSet)
			{
				scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
			}
		}
		scriptData.getCurrentStatic()->padInitTable(scriptData.getStackWidth());

		resetIntIndex();
		isCurrentExprEvaluable = true;
		doesCurrentValueNeedSet = false;

		if (scriptData.getCurrentStatic()->getStackInitSize(scriptData.getStackWidth()) - curSize < size)
		{
			size_t count = size - (scriptData.getCurrentStatic()->getStackInitSize(scriptData.getStackWidth()) - curSize);
			addStaticPadding(count);
		}
		return true;
	}
	else if (isa<UnaryOperator>(e))
	{
		isCurrentExprEvaluable = false;
		const UnaryOperator *op = cast<const UnaryOperator>(e);
		Expr *subE = op->getSubExpr();

		if (op->getOpcode() == UO_AddrOf)
		{
			if (isa<DeclRefExpr>(subE))
			{
				const DeclRefExpr *DRE = cast<const DeclRefExpr>(subE);
				doesCurrentValueNeedSet = true;
				if (auto fDecl = dyn_cast_or_null<FunctionDecl>(DRE->getDecl()))
				{
					auto function = scriptData.getFunctionFromName(getNameForFunc(fDecl));
					if (!function)
						Throw("Static function pointer \"" + fDecl->getNameAsString() + "\" not found");

					scriptData.getCurrentStatic()->addOpFuncLoc(function);
					scriptData.getCurrentStatic()->setDynamic();
				}
				else
				{
					//we can index because the name has to be declared in clang to use the declare, we will let clang handle errors
					StaticData* staticData = scriptData.findStatic(dumpName(cast<NamedDecl>(DRE->getDecl())));
					assert(staticData && "Static Not Found");
					scriptData.getCurrentStatic()->addOpGetStaticP(staticData);
					scriptData.getCurrentStatic()->setDynamic();
				}
			}
			else
			{
				ParseLiteral(subE, true, false);
			}
			return true;

		}
	}
	else if (isa<ImplicitCastExpr>(e))
	{
		const ImplicitCastExpr *icast = cast<const ImplicitCastExpr>(e);

		switch (icast->getCastKind())
		{
			case CK_ArrayToPointerDecay:
				isCurrentExprEvaluable = false;
				if (isa<StringLiteral>(icast->getSubExpr()))//char* x = "hello";
				{
					const StringLiteral *literal = cast<const StringLiteral>(icast->getSubExpr());
					scriptData.getCurrentStatic()->addOpPushString(literal->getString().str());
					scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
					scriptData.getCurrentStatic()->setDynamic();
				}
				else if (isa<DeclRefExpr>(icast->getSubExpr()))//int vstack[10] = {1,2,3,4,5,6,7,8,9,10}, *vstack_ptr = vstack;
				{
					const DeclRefExpr *DRE = cast<const DeclRefExpr>(icast->getSubExpr());
					doesCurrentValueNeedSet = true;

					//we can index because the name has to be declared in clang to use the declare, we will let clang handle errors
					StaticData* staticData = scriptData.findStatic(dumpName(cast<NamedDecl>(DRE->getDecl())));
					assert(staticData && "Static Not Found");
					scriptData.getCurrentStatic()->addOpGetStaticP(staticData);
					scriptData.getCurrentStatic()->setDynamic();
				}
				else// need to test byte* t = {1,2,3};
					Throw("Unimplemented CK_ArrayToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()), TheRewriter, icast->getSubExpr()->getSourceRange());
				break;

			case CK_FunctionToPointerDecay://int (*ggg)(int, float) = test; // test is a function
				isCurrentExprEvaluable = false;
				if (isa<DeclRefExpr>(icast->getSubExpr()))
				{
					const DeclRefExpr *declRef = cast<const DeclRefExpr>(icast->getSubExpr());
					if (isa<FunctionDecl>(declRef->getDecl()))
					{
						const FunctionDecl *decl = cast<const FunctionDecl>(declRef->getDecl());

						auto function = scriptData.getFunctionFromName(getNameForFunc(decl));
						if (!function)
							Throw("Static function pointer \"" + decl->getNameAsString() + "\" not found");

						scriptData.getCurrentStatic()->addOpFuncLoc(function);
						scriptData.getCurrentStatic()->addOpSetThisStatic(scriptData);
						scriptData.getCurrentStatic()->setDynamic();

					}
					else Throw("Unimplemented CK_FunctionToPointerDecay DeclRefExpr for " + string(declRef->getStmtClassName()));

				}
				else
					Throw("Unimplemented CK_FunctionToPointerDecay for " + string(icast->getSubExpr()->getStmtClassName()), TheRewriter, icast->getSubExpr()->getSourceRange());
				break;

			case clang::CK_PointerToIntegral://int ptoitest = &addrptrtest;
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;
			case clang::CK_IntegralToPointer://*vstack_ptr = &vstack[9] - &vstack[0];
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;
			case clang::CK_BitCast://short* testok = &addrptrtest;//(addrptrtest is an int)
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;
			case clang::CK_NullToPointer://char* HeaderText = nullptr,
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;

			default:
				Throw("Unimplemented ImplicitCastExpr of type " + string(icast->getCastKindName()), TheRewriter, icast->getSourceRange());
		}


	}
	else if (isa<CastExpr>(e))
	{

		const CastExpr *icast = cast<const CastExpr>(e);
		switch (icast->getCastKind())
		{

			case clang::CK_ArrayToPointerDecay:
				isCurrentExprEvaluable = false;
				ParseLiteral(icast->getSubExpr(), true, false);
				break;

				//case clang::CK_DerivedToBase:
				//	ParseLiteral(icast->getSubExpr());
				//break;

			case clang::CK_PointerToIntegral://int ptoitest = (int)&addrptrtest;
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;
			case clang::CK_IntegralToPointer://*vstack_ptr = (int*)(&vstack[9] - &vstack[0]);
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;

			case clang::CK_BitCast://short* testok = (short*)&addrptrtest;//(addrptrtest is an int)
				ParseLiteral(icast->getSubExpr(), false, isLtoRValue);
				break;

			default:
				Throw("Cast " + string(icast->getCastKindName()) + " is unimplemented for a static define");

		}
	}
	else if (isa<BinaryOperator>(e))
	{
		isCurrentExprEvaluable = false;
		const BinaryOperator *bOp = cast<const BinaryOperator>(e);
		BinaryOperatorKind op = bOp->getOpcode();


		//c allows same type pointer to pointer subtraction to obtain the logical difference. 
		if (isa<PointerType>(bOp->getLHS()->getType()) && isa<PointerType>(bOp->getRHS()->getType()))
		{
			ParseLiteral(bOp->getLHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);
			ParseLiteral(bOp->getRHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);

			if (op == BO_Sub)
			{
				const Type* pTypePtr = bOp->getLHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
				int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
				int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;
				auto cur = scriptData.getCurrentStatic();
				cur->setDynamic();
				if (bOp->getLHS()->getType()->isFloatingType())
					cur->addOpFSub();
				else
					cur->addOpSub();


				if (pSize > 1)
				{
					cur->addOpPushInt(pSize);
					cur->addOpDiv();
				}

				return -1;
			}
			else
				Throw("Pointer to pointer operation not subtraction \"" + bOp->getOpcodeStr().str() + "\"", TheRewriter, bOp->getOperatorLoc());
		}
		else if (isa<PointerType>(bOp->getLHS()->getType()))
		{
			//we need to parse left as an addr if its an array else its a pointer val
			ParseLiteral(bOp->getLHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);
			ParseLiteral(bOp->getRHS(), false, true);

			if (op == BO_Add || op == BO_Sub)
			{
				const Type* pTypePtr = bOp->getLHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
				int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
				int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

				//TODO: double check this code
				if (pSize > 1)
					scriptData.getCurrentStatic()->addOpMultImm(pSize);
			}
			else
				Throw("Pointer to literal operation not addition or subtraction \"" + bOp->getOpcodeStr().str() + "\"", TheRewriter, bOp->getOperatorLoc());

		}
		else if (isa<PointerType>(bOp->getRHS()->getType()))
		{
			//we need to parse right as an addr if its an array else its a pointer val
			ParseLiteral(bOp->getLHS(), false, true);

			if (op == BO_Add || op == BO_Sub)
			{
				const Type* pTypePtr = bOp->getRHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
				int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
				int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

				if (pSize > 1)
					scriptData.getCurrentStatic()->addOpMultImm(pSize);
			}
			else
				Throw("Pointer to literal operation not addition or subtraction \"" + bOp->getOpcodeStr().str() + "\"", TheRewriter, bOp->getOperatorLoc());

			ParseLiteral(bOp->getRHS(), bOp->getRHS()->getType().getTypePtr()->isArrayType(), true);
		}
		else
		{
			//no pointer operations
			Throw("Expected pointer operation for static BinaryOperator", TheRewriter, e->getExprLoc());
			//parseExpression(bOp->getLHS(), false, true);
			//parseExpression(bOp->getRHS(), false, true);
		}

		switch (op)
		{
			case BO_Sub: scriptData.getCurrentStatic()->addOpSub();  break;
			case BO_Add: scriptData.getCurrentStatic()->addOpAdd(); break;
			default:
				Throw("Unimplemented binary op " + bOp->getOpcodeStr().str(), TheRewriter, bOp->getExprLoc());
		}

	}
	else if (isa<ParenExpr>(e))
	{
		const ParenExpr *parenExpr = cast<const ParenExpr>(e);
		ParseLiteral(parenExpr->getSubExpr(), isAddr, isLtoRValue);
	}
	else if (isa<ArraySubscriptExpr>(e))
	{
		Expr* sexpr = const_cast<Expr*>(e);
		uint32_t inc = 0, ssize = 0;
		while (isa<ArraySubscriptExpr>(sexpr))
		{
			const ArraySubscriptExpr* arr = cast<ArraySubscriptExpr>(sexpr);
			const Expr *index = arr->getIdx();
			const Expr *base = arr->getBase();

			if (isa<ImplicitCastExpr>(base))
				base = cast<ImplicitCastExpr>(base)->getSubExpr();
			else if (isa<ParenExpr>(base))
				base = cast<ParenExpr>(base)->getSubExpr();
			else
				Throw("Unimplemented static array base resolution of " + string(base->getStmtClassName()), TheRewriter, e->getSourceRange());



			const DeclRefExpr *declRef = getDeclRefExpr(base);
			Type* type = const_cast<Type*>(base->getType().getTypePtr());

			if (type == NULL)
				type = const_cast<Type*>(declRef->getType().getTypePtr());
			if (type->isPointerType())
				type = const_cast<Type*>(type->getPointeeType().getTypePtr());

			llvm::APSInt iResult;
			if (index->EvaluateAsInt(iResult, context))
			{
				doesCurrentValueNeedSet = true;
				auto cur = scriptData.getCurrentStatic();
				cur->setDynamic();
				if (!inc)
				{
					cur->addOpGetStaticP(scriptData.findStatic(dumpName(cast<NamedDecl>(declRef->getDecl()))));
				}

				if (!ssize)
				{
					uint32_t elementSize = stackWidth;
					if (type->isArrayType())
						elementSize = getSizeOfType(base->getType()->getArrayElementTypeNoTypeQual());

					cur->addOpAddImm(iResult.getSExtValue() * elementSize);
				}
				else
				{
					cur->addOpAddImm(ssize * iResult.getSExtValue());
				}

				ssize = getSizeOfType(type);
			}
			else
				Throw("Expected integer literal for static array pointer initialisation", TheRewriter, e->getSourceRange());

			inc++;
			sexpr = const_cast<Expr*>(base);
			while (isa<ParenExpr>(sexpr))
				sexpr = const_cast<Expr*>(cast<const ParenExpr>(sexpr)->getSubExpr());


		}

	}
	else if (isa<MemberExpr>(e))
	{
		if (!isAddr)
		{
			Throw("Can only get address of members for static defines", TheRewriter, e->getExprLoc());
		}
		auto cur = scriptData.getCurrentStatic();
		doesCurrentValueNeedSet = true;
		const MemberExpr *E = cast<const MemberExpr>(e);
		Expr *BaseExpr = E->getBase();


		if (E->isArrow())
		{
			ParseLiteral(BaseExpr, false, true);
		}
		else
			ParseLiteral(BaseExpr, true);


		int offset = 0;
		NamedDecl *ND = E->getMemberDecl();



		if (auto *Field = dyn_cast<FieldDecl>(ND))
		{
			const RecordDecl *record = Field->getParent();
			if (record->isUnion())
				offset = 0;
			else
			{
				for (const FieldDecl *CS : record->fields())
				{
					if (CS == Field)
						break;

					const Type* type = CS->getType().getTypePtr();
					int temp = getSizeOfType(type);
					offset += max(temp, stackWidth);
				}
			}
		}
		cur->addOpGetImmP(getSizeFromBytes(offset));
		cur->setDynamic();
		return 1;
	}
	else if (isa<DeclRefExpr>(e))
	{
		auto declRef = cast<DeclRefExpr>(e);
		if (isAddr)
		{
			if (auto varDecl = dyn_cast_or_null<VarDecl>(declRef->getFoundDecl()))
			{
				scriptData.getCurrentStatic()->addOpGetStaticP(scriptData.findStatic(dumpName(cast<NamedDecl>(varDecl))));
				scriptData.getCurrentStatic()->setDynamic();
				return 1;
			}
			else
			{
				Throw("DeclRefExpr error", TheRewriter, e->getSourceRange());
			}
		}
		else
		{
			Throw("DeclRefExpr error", TheRewriter, e->getSourceRange());
		}
	}
	else
		Throw("Class " + string(e->getStmtClassName()) + " is unimplemented for a static define");
	return -1;
}
