#include "ClangParsing/ASTVisitorLocal.h"
#include "ClangParsing/Helpers/FunctionData.h"
#include "ClangParsing/Helpers/Script.h"
#include "ClangParsing/CommandLineOptions.h"
#include <queue>

using namespace std;
using namespace clang;
using namespace llvm;
using namespace Utils::System;
using namespace Utils::DataConversion;
using namespace Utils::Hashing;

namespace SCCL
{
#pragma region Misc_Functions
    void ASTVisitorLocal::ComplexToBoolean(bool floating)
    {
        LocalVariables.addLevel();
        int index = LocalVariables.addDecl("imagPart", 1);
        if (floating)
        {
            AddInstruction(SetFrame, index);
            AddInstruction(PushFloat, 0.0f);
            AddInstruction(FCmpEq);
            AddInstruction(GetFrame, index);
            AddInstruction(PushFloat, 0.0f);
            AddInstruction(FCmpEq);
            AddInstruction(Or);
        }
        else
        {
            AddInstruction(SetFrame, index);
            AddInstruction(PushInt, 0);
            AddInstruction(CmpEq);
            AddInstruction(GetFrame, index);
            AddInstruction(PushInt, 0);
            AddInstruction(CmpEq);
            AddInstruction(Or);
        }
        LocalVariables.removeLevel();
    }

#pragma endregion

#pragma region Name_Resolution
    string ASTVisitorLocal::dumpName(const NamedDecl* ND)
    {
        if (isa<CXXMethodDecl>(ND))
        {
            const CXXMethodDecl* method = cast<const CXXMethodDecl>(ND);
            const CXXRecordDecl* record = method->getParent();
            return record->getNameAsString() + "::" + method->getNameAsString();
        }
        if (ND->getDeclName())
        {

            return ND->getNameAsString();
        }
        return "";
    }
    string ASTVisitorLocal::getNameForFunc(const FunctionDecl* decl)
    {

        string FileId = "";
        if (decl->getStorageClass() == SC_Static)
        {
            TEST(CurrentFileId, "File id 0 reserved for extern", TheRewriter, decl->getSourceRange());
            char buf[9] = {};
            FileId += string(itoa(CurrentFileId - 1, buf, 36)) += "~";
            //this works without collision going on the notion that no one can add "~" to a function name
        }

        if (isa<CXXMethodDecl>(decl))
        {
            const CXXMethodDecl* methodDecl = cast<const CXXMethodDecl>(decl);
            const CXXRecordDecl* record = methodDecl->getParent();
            return FileId + record->getNameAsString() + "::" + methodDecl->getNameAsString();
        }
        else
        {
            return FileId + decl->getNameAsString();
        }
    }
#pragma endregion

#pragma region Parsing
    string ASTVisitorLocal::parseCast(const CastExpr* castExpr)
    {
        switch (castExpr->getCastKind())
        {
        case clang::CK_LValueToRValue:
            break;
        case clang::CK_IntegralCast:
        {
            const Expr* e = castExpr->getSubExpr();
            if (isa<IntegerLiteral>(e))
            {
                const IntegerLiteral* literal = cast<const IntegerLiteral>(e);
                return to_string(literal->getValue().getSExtValue());
            }
            else if (isa<FloatingLiteral>(e))
            {
                const FloatingLiteral* literal = cast<const FloatingLiteral>(e);
                if (&literal->getValue().getSemantics() == &llvm::APFloat::IEEEsingle())
                    return to_string(literal->getValue().convertToFloat());
                else
                    return to_string(literal->getValue().convertToDouble());
            }
            else
            {
                Throw("Unhandled Integral Cast", TheRewriter, castExpr->getSourceRange());
            }
        }
        case clang::CK_FunctionToPointerDecay:
        {
            if (isa<DeclRefExpr>(castExpr->getSubExpr()->IgnoreParens()->IgnoreCasts()))
            {
                const DeclRefExpr* declRef = cast<const DeclRefExpr>(castExpr->getSubExpr()->IgnoreParens()->IgnoreCasts());
                if (isa<FunctionDecl>(declRef->getDecl()))
                {
                    const FunctionDecl* decl = cast<const FunctionDecl>(declRef->getDecl());
                    return getNameForFunc(decl);
                }
                else
                {
                    Throw("Unimplemented Cast", TheRewriter, castExpr->getSourceRange());
                }

            }
            else
            {
                Throw("Unimplemented Cast", TheRewriter, castExpr->getSourceRange());
            }
        }
        break;
        default:
            Throw("Unimplemented Cast", TheRewriter, castExpr->getSourceRange());
        }
        return "";
    }
#pragma endregion

#pragma region Decl_Handling
    //handleParamVarDecl
    void ASTVisitorLocal::printDeclWithKey(const string& key, bool isAddr, bool isLtoRValue, bool isAssign, const DeclRefExpr* declref)
    {
        uint32_t index = -1;
        StaticData* sData = nullptr;
        const clang::Type* type = declref->getType().getTypePtr();
        const VarDecl* varDecl = dyn_cast<VarDecl>(declref->getDecl());
        size_t size = getSizeOfType(type);
        bool isStackCpy = size > stackWidth && isLtoRValue && !isAddr;//if greater then 4 bytes then a to stack is in order

        if (isStackCpy)
        {
            AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
            isAddr = true;
        }

        if (LocalVariables.find(key, index))
        {
            if (isLtoRValue && !isAddr)
            {
                AddInstructionComment(GetFrame, key, index);
                if (size == 1 || size == 2)
                {
                    AddInstruction(GetConv, scriptData, size, declref->getType()->isSignedIntegerType());
                }
            }
            else if (isAddr)
            {
                AddInstructionComment(GetFrameP, key, index);
            }
            else if (isAssign)
            {
                //this for single var setting (and or) for data preservation is not needed

                if (size > stackWidth)//fromStack
                {
                    AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
                    AddInstructionComment(GetFrameP, key, index);
                    AddInstruction(FromStack);
                }
                else
                {
                    if (size == 1 || size == 2)
                    {
                        AddInstruction(SetConv, scriptData, size);
                    }
                    AddInstructionComment(SetFrame, key, index);
                }

            }
        }
        else if (LocalVariables.findNewStatic(key, sData))
        {
            scriptData.getCurrentFunction()->addUsedStatic(sData);
            if (isLtoRValue && !isAddr)
            {
                AddInstructionComment(GetStatic, key, sData);
                if (size == 1 || size == 2)
                {
                    AddInstruction(GetConv, scriptData, size, declref->getType()->isSignedIntegerType());
                }
            }
            else if (isAddr)
            {
                AddInstructionComment(GetStaticP, key, sData);
            }
            else if (isAssign)
            {
                //this for single var setting (and or) for data preservation is not needed


                if (size > stackWidth)//fromStack
                {
                    AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
                    AddInstructionComment(GetStaticP, key, sData);
                    AddInstruction(FromStack);
                }
                else
                {
                    if (size == 1 || size == 2)
                    {
                        AddInstruction(SetConv, scriptData, size);
                    }
                    AddInstructionComment(SetStatic, key, sData);
                }
            }
        }
        else if (varDecl && varDecl->hasAttr<GlobalVariableAttr>())
        {
            index = varDecl->getAttr<GlobalVariableAttr>()->getIndex();
            if (isLtoRValue && !isAddr)
            {
                AddInstructionComment(GetGlobal, key, index);
                if (size == 1 || size == 2)
                {
                    AddInstruction(GetConv, scriptData, size, declref->getType()->isSignedIntegerType());
                }
            }
            else if (isAddr)
            {
                AddInstructionComment(GetGlobalP, key, index);
            }
            else if (isAssign)
            {
                //this for single var setting (and or) for data preservation is not needed

                if (size > stackWidth)//fromStack
                {
                    AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
                    AddInstructionComment(GetGlobalP, key, index);
                    AddInstruction(FromStack);
                }
                else
                {
                    if (size == 1 || size == 2)
                    {
                        AddInstruction(SetConv, scriptData, size);
                    }
                    AddInstructionComment(SetGlobal, key, index);
                }
            }
        }
        else if (auto sData = scriptData.findStatic(dumpName(cast<NamedDecl>(declref->getDecl()))))
        {

            scriptData.getCurrentFunction()->addUsedStatic(sData);
            if (isLtoRValue && !isAddr)
            {
                AddInstructionComment(GetStatic, key, sData);
                if (size == 1 || size == 2)
                {
                    AddInstruction(GetConv, scriptData, size, declref->getType()->isSignedIntegerType());
                }
            }
            else if (isAddr)
            {
                AddInstructionComment(GetStaticP, key, sData);
            }
            else if (isAssign)
            {
                //this for single var setting (and or) for data preservation is not needed


                if (size > stackWidth)//fromStack
                {
                    AddInstructionComment(PushInt, "Type Size", getSizeFromBytes(size));
                    AddInstructionComment(GetStaticP, key, sData);
                    AddInstruction(FromStack);
                }
                else
                {
                    if (size == 1 || size == 2)
                    {
                        AddInstruction(SetConv, scriptData, size);
                    }
                    AddInstructionComment(SetStatic, key, sData);
                }
            }
        }
        else
        {
            if (isAddr || isLtoRValue)
            {
                if (auto funcDecl = dyn_cast_or_null<FunctionDecl>(declref->getDecl()))
                {
                    if (auto func = scriptData.getFunctionFromName(getNameForFunc(funcDecl)))
                    {
                        AddInstruction(FuncLoc, func);
                    }
                    else
                        Throw("Function pointer \"" + key + "\" not found");
                }
            }
            else
                Throw("Could not find decl", TheRewriter, declref->getDecl()->getSourceRange());
        }
        AddInstructionConditionally(isStackCpy, ToStack);
    }
    bool ASTVisitorLocal::handleParmVarDecl(ParmVarDecl* D)
    {
        if (isa<ParmVarDecl>(D))
        {
            ParmVarDecl* decl = cast<ParmVarDecl>(D);
            if (isa<VarDecl>(decl))
            {

                VarDecl* var = cast<VarDecl>(decl);
                auto size = getSizeOfType(decl->getType().getTypePtr());
                uint32_t curIndex = LocalVariables.getCurrentSize();

                int actsize = getSizeFromBytes(size);

                const Expr* initializer = var->getAnyInitializer();

                if (initializer)
                {
                    if (isa<CXXConstructExpr>(initializer))
                    {
                        AddInstructionComment(GetFrameP, var->getNameAsString(), curIndex);
                        parseExpression(initializer);
                    }
                    else
                    {
                        parseExpression(initializer);
                        AddInstructionComment(SetFrame, "(parm)" + var->getName().str(), curIndex);
                    }
                }
                LocalVariables.addDecl(var->getName().str(), actsize);
            }
        }
        return true;
    }
    bool ASTVisitorLocal::handleDecl(DeclStmt* decl)
    {
        for (auto& decl : decl->decls())
        {
            if (isa<VarDecl>(decl))
            {
                VarDecl* var = cast<VarDecl>(decl);

                //out << +var->getStorageClass() << endl;
                if (var->getStorageClass() != SC_Static)//static vars are initialized in the globals visitor
                {
                    auto size = getSizeOfType(var->getType().getTypePtr());

                    uint32_t curIndex = LocalVariables.getCurrentSize();

                    const clang::ArrayType* arr = NULL;
                    if ((arr = var->getType()->getAsArrayTypeUnsafe()) && arr->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl())
                    {
                        Throw("Unsupported decl of " + string(var->getDeclKindName()), TheRewriter, var->getLocation());
                    }
                    else if (var->getType()->getAsCXXRecordDecl())
                    {
                        Throw("Unsupported decl of " + string(var->getDeclKindName()), TheRewriter, var->getLocation());
                    }

                    const Expr* initializer = var->getAnyInitializer();
                    if (initializer)
                    {
                        //if (isa<CXXConstructExpr>(initializer)) {
                        //	if (isa<ConstantArrayType>(var->getType())) {
                        //		const ConstantArrayType *arr = cast<ConstantArrayType>(var->getType());
                        //		static int vTableInitInc = 0;
                        //
                        //		out << "Push 0" << endl;
                        //		out << ":vTableConditional_" << vTableInitInc << endl;
                        //		//for(int i=0; i<arr->getSize().getSExtValue(); i++) {
                        //		out << "dup //index" << endl;
                        //		out << "Push " << arr->getSize().getZExtValue() << endl;
                        //		out << "JumpGE @vTableEnd_" << vTableInitInc << endl;
                        //
                        //		out << "dup #index" << endl;
                        //		out << pFrame(curIndex) << " //" << var->getNameAsString() << endl;
                        //		out << "ArrayGetP " << getSizeFromBytes(getSizeOfCXXDecl(arr->getArrayElementTypeNoTypeQual()->getAsCXXRecordDecl(), true, true)) << "//index Array" << endl;
                        //		parseExpression(initializer, true, false, true, var);
                        //		out << "Add1 1" << endl;
                        //		out << "Jump @vTableConditional_" << vTableInitInc << endl;
                        //		out << ":vTableEnd_" << vTableInitInc << endl << endl;
                        //		//}
                        //		vTableInitInc++;
                        //		return true;
                        //	}
                        //	out << pFrame(curIndex) << " //" << var->getNameAsString() << endl;
                        //	parseExpression(initializer, true, false, true, var);
                        //	return true;
                        //}


                        parseExpression(initializer, false, true);

                        if (size > stackWidth)
                        {
                            AddInstructionComment(PushInt, "Type Size (init decl)", getSizeFromBytes(size));
                            AddInstructionComment(GetFrameP, "&" + var->getNameAsString(), curIndex);
                            AddInstruction(FromStack);
                        }
                        else
                        {
                            if (size == 1 || size == 2)
                            {
                                AddInstruction(SetConv, scriptData, size);
                            }
                            AddInstructionComment(SetFrame, "(init)" + var->getName().str(), curIndex);
                        }
                    }
                    LocalVariables.addDecl(var->getName().str(), getSizeFromBytes(size));
                }
                else
                {
                    LocalVariables.addLocalStaticDecl(var);
                }
            }
        }
        return true;
    }
#pragma endregion

#pragma region Parse/Visit_Functions
    void ASTVisitorLocal::parseCallProto(const CallExpr* call, bool& isVariadic, size_t& NumParams)
    {
        const Decl* calleeDecl = call->getCalleeDecl();
        if (isa<FunctionDecl>(calleeDecl))
        {
            const FunctionDecl* FD = cast<FunctionDecl>(calleeDecl);
            isVariadic = FD->isVariadic();
            NumParams = FD->getNumParams();
        }
        else if (calleeDecl->getFunctionType()->isFunctionProtoType())
        {
            FunctionProtoType* FPT = (FunctionProtoType*)cast<FunctionProtoType>(calleeDecl->getFunctionType());
            isVariadic = FPT->isVariadic();
            NumParams = FPT->getNumParams();
        }
        else if (calleeDecl->getFunctionType()->isFunctionNoProtoType())
        {
            isVariadic = false;
            NumParams = 0;
        }
        else
            Warn("Unknown Call Proto of type: " + string(calleeDecl->getFunctionType()->getTypeClassName()), TheRewriter, call->getSourceRange());

    }

    bool ASTVisitorLocal::isPushString(const Expr* e)
    {
        const CastExpr* cast;
        if ((cast = dyn_cast<CastExpr>(e)) && cast->getCastKind() == CK_ArrayToPointerDecay)
        {
            return isa<clang::StringLiteral>(cast->getSubExpr());
        }
        return false;
    }
    bool ASTVisitorLocal::EvaluateAsString(const Expr* cExpr, string& outStr)
    {
        Expr* expr = (Expr*)cExpr;
        while (isa<ImplicitCastExpr>(expr))
        {
            const ImplicitCastExpr* icast = cast<const ImplicitCastExpr>(expr);
            expr = (Expr*)icast->getSubExpr();
        }
        if (isa<clang::StringLiteral>(expr))
        {
            outStr = cast<const clang::StringLiteral>(expr)->getString().str();
            return true;
        }
        return false;
    }

    bool ASTVisitorLocal::checkIntrinsic(const CallExpr* call)
    {
        const FunctionDecl* callee = call->getDirectCallee();

        if (callee == NULL || !callee->hasAttr<IntrinsicFuncAttr>())
            return false;

        if (callee->getStorageClass() != SC_Extern)
            Throw("Intrinsic functions must be declared with the 'extern' keyword", TheRewriter, callee->getLocation());

        string funcName = dumpName(cast<NamedDecl>(callee));

        if (callee->getAttr<IntrinsicFuncAttr>()->getIsUnsafe() && !scriptData.isUnsafeContext())
            Warn("Unsafe Intrinsic \"" + funcName + "\" used in an unsafe context. This could lead to crashes", TheRewriter, call->getSourceRange());


        const Expr* const* argArray = call->getArgs();
        int argCount = call->getNumArgs();
        bool ret = false;


#define ChkHashCol(str) if(strcmp(funcName.c_str(), str) != 0) goto _IntrinsicNotFound;
#define BadIntrin else Throw("Intrinsic not correctly defined", TheRewriter, callee->getSourceRange());
#define EvalFailed else Throw("Value must be a integer literal", TheRewriter, call->getSourceRange());
#define EvalFailedFlt else Throw("Value must be a floating literal", TheRewriter, call->getSourceRange());
#define EvalFailedStr else Throw("Value must be a string literal", TheRewriter, call->getSourceRange());
#define BadIntrinArgC else Throw("Bad arg count", TheRewriter, call->getSourceRange());


        auto AddAsmIntrinsic = [&](const char* str, void(FunctionData::* func)(void)) -> void
        {
            if (strcmp(funcName.c_str(), str) != 0)
                Throw("No intrinsic function found named " + funcName, TheRewriter, callee->getLocation());
            if (argCount == 0 && callee->getReturnType()->isVoidType())
            {
                (scriptData.getCurrentFunction()->*func)();
                ret = true;
                return;
            } BadIntrin
        };
        auto AddAsmIntrinsic8 = [&](const char* str, void(FunctionData::* func)(uint8_t)) -> void
        {
            if (strcmp(funcName.c_str(), str) != 0)
                Throw("No intrinsic function found named " + funcName, TheRewriter, callee->getLocation());
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult apCount;
                if (argArray[0]->EvaluateAsInt(apCount, context))
                {
                    (scriptData.getCurrentFunction()->*func)(apCount.Val.getInt().getSExtValue());
                    ret = true;
                    return;
                } EvalFailed
            } BadIntrin
        };
        auto AddAsmIntrinsic16 = [&](const char* str, void(FunctionData::* func)(uint16_t)) -> void
        {
            if (strcmp(funcName.c_str(), str) != 0)
                Throw("No intrinsic function found named " + funcName, TheRewriter, callee->getLocation());
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult apCount;
                if (argArray[0]->EvaluateAsInt(apCount, context))
                {
                    (scriptData.getCurrentFunction()->*func)(apCount.Val.getInt().getSExtValue());
                    ret = true;
                    return;
                } EvalFailed
            } BadIntrin
        };
        auto AddAsmIntrinsicLocal = [&](const char* str, void(FunctionData::* func)(uint16_t)) -> void
        {
            if (strcmp(funcName.c_str(), str) != 0)
                Throw("No intrinsic function found named " + funcName, TheRewriter, callee->getLocation());
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType())
            {
                string str;
                if (EvaluateAsString(argArray[0], str))
                {
                    uint32_t index = 0;
                    if (LocalVariables.find(str, index))
                    {
                        (scriptData.getCurrentFunction()->*func)(index);
                        scriptData.getCurrentFunction()->pushComment("(ASM Named Local) " + str);
                        ret = true;
                        return;
                    }
                    else
                        Throw("varName \"" + str + "\" not found", TheRewriter, call->getSourceRange());
                } EvalFailedStr
            } BadIntrin
        };
        auto AddAsmIntrinsicStatic = [&](const char* str, void(FunctionData::* func)(StaticData*)) -> void
        {
            if (strcmp(funcName.c_str(), str) != 0)
                Throw("No intrinsic function found named " + funcName, TheRewriter, callee->getLocation());
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType())
            {
                string str;
                if (EvaluateAsString(argArray[0], str))
                {
                    StaticData* data = scriptData.findStatic(str);
                    if (data)
                    {
                        (scriptData.getCurrentFunction()->*func)(data);
                        scriptData.getCurrentFunction()->pushComment("(ASM Named Static) " + str);
                        ret = true;
                        return;
                    }
                    else
                        Throw("varName \"" + str + "\" not found", TheRewriter, call->getSourceRange());
                } EvalFailedStr
            } BadIntrin
        };
        auto AddAsmIntrinsic32 = [&](const char* str, void(FunctionData::* func)(int)) -> void
        {
            if (strcmp(funcName.c_str(), str) != 0)
                Throw("No intrinsic function found named " + funcName, TheRewriter, callee->getLocation());
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult apCount;
                if (argArray[0]->EvaluateAsInt(apCount, context))
                {
                    (scriptData.getCurrentFunction()->*func)(apCount.Val.getInt().getSExtValue());
                    ret = true;
                    return;
                } EvalFailed
            } BadIntrin
        };
        auto AddAsmIntrinsicJump = [&](const char* str, void(FunctionData::* func)(const string&)) -> void
        {
            if (strcmp(funcName.c_str(), str) != 0)
                Throw("No intrinsic function found named " + funcName, TheRewriter, callee->getLocation());

            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType())
            {
                string str;
                if (EvaluateAsString(argArray[0], str))
                {
                    (scriptData.getCurrentFunction()->*func)(str + scriptData.getInlineJumpLabelAppend());
                    ret = true;
                    return;
                } EvalFailedStr
            } BadIntrin
        };

        auto getSafeIntrinSize = [&](const Expr* expression)
        {
            if (auto implicit = dyn_cast<ImplicitCastExpr>(expression))
            {
                if (implicit->getCastKind() == CK_ArrayToPointerDecay)
                {
                    if (auto arrayType = dyn_cast<ConstantArrayType>(implicit->getSubExpr()->getType().getTypePtr()))
                    {
                        auto size = arrayType->getSize().getSExtValue();
                        if (size > 0 && size < 256)
                        {
                            return size;
                        }
                        Throw("Char array size for safe intrinsics must be between 1 and 255", TheRewriter, expression->getSourceRange());
                    }
                }
            }
            Throw("First param for safe string intrinsics must be a char array", TheRewriter, expression->getSourceRange());
            return -1LL;
        };

        switch (JoaatCased(const_cast<char*>(funcName.c_str())))
        {
#pragma region String

            //isAddr is false on memory functions because we dont want to force addressof
        case JoaatCasedConst("memcpyold"):
        {
            ChkHashCol("memcpy");
            if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType() && argArray[2]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult apCount;
                int iCount;
                if (argArray[2]->EvaluateAsInt(apCount, context) && (iCount = apCount.Val.getInt().getSExtValue(), iCount > 0) && iCount % stackWidth == 0)
                {
                    int itemCount = iCount / stackWidth;
                    if (itemCount == 1)
                    {

                        parseExpression(argArray[1], false, true);
                        AddInstruction(PGet);
                        parseExpression(argArray[0], false, true);
                        AddInstruction(PSet);
                    }
                    else if (itemCount <= 50)
                    {
                        AddInstruction(PushInt, itemCount);
                        parseExpression(argArray[1], false, true);
                        AddInstruction(ToStack);
                        AddInstruction(PushInt, itemCount);
                        parseExpression(argArray[0], false, true);
                        AddInstruction(FromStack);
                    }
                    else
                    {
                        const int maxCopyAmount = 100;
                        LocalVariables.addLevel();
                        int destIndex = LocalVariables.addDecl("dest", 1);
                        int srcIndex = LocalVariables.addDecl("src", 1);
                        parseExpression(argArray[1], false, true);
                        AddInstruction(SetFrame, srcIndex);
                        parseExpression(argArray[0], false, true);
                        AddInstruction(SetFrame, destIndex);
                        for (int remaining = itemCount; remaining > 0; remaining -= maxCopyAmount)
                        {
                            int count = min(remaining, maxCopyAmount);
                            AddInstruction(PushInt, count);
                            AddInstruction(GetFrame, srcIndex);
                            AddInstruction(ToStack);
                            AddInstruction(PushInt, count);
                            AddInstruction(GetFrame, destIndex);
                            AddInstruction(FromStack);
                            if (remaining > maxCopyAmount)
                            {
                                AddInstruction(GetFrame, srcIndex);
                                AddInstruction(GetImmP, maxCopyAmount);
                                AddInstruction(SetFrame, srcIndex);
                                AddInstruction(GetFrame, destIndex);
                                AddInstruction(GetImmP, maxCopyAmount);
                                AddInstruction(SetFrame, destIndex);
                            }
                        }
                    }
                }
                else
                {
                    //TODO: fix for pc
                    static uint32_t loopLblCount = -1;
                    loopLblCount++;

                    LocalVariables.addLevel();

                    int destIndex = LocalVariables.addDecl("__memcpy-loop-dest", 1);
                    int srcIndex = LocalVariables.addDecl("__memcpy-loop-src", 1);
                    int sizeIndex = LocalVariables.addDecl("__memcpy-loop-size", 1);

                    parseExpression(argArray[0], false, true);//dest
                    AddInstruction(SetFrame, destIndex);

                    parseExpression(argArray[1], false, true);//src
                    AddInstruction(SetFrame, srcIndex);
                    parseExpression(argArray[2], false, true);//size


                    AddInstruction(SetFrame, sizeIndex);
                    AddInstruction(PushInt, 0);
                    AddInstruction(Label, "__memcpy-loop-" + to_string(loopLblCount));
                    AddInstruction(Dup);
                    AddInstruction(GetFrame, sizeIndex);
                    AddInstruction(JumpGE, "__memcpy-loopend-" + to_string(loopLblCount));

                    AddInstruction(GetFrame, srcIndex);
                    AddInstruction(PGet);
                    AddInstruction(ShiftLeft, 24);
                    AddInstruction(GetFrame, destIndex);
                    AddInstruction(PGet);
                    AddInstruction(PushInt, 0xFFFFFF);
                    AddInstruction(And);
                    AddInstruction(Or);
                    AddInstruction(GetFrame, destIndex);
                    AddInstruction(PSet);

                    AddInstruction(GetFrame, destIndex);
                    AddInstruction(AddImm, 1);
                    AddInstruction(SetFrame, destIndex);
                    AddInstruction(GetFrame, srcIndex);
                    AddInstruction(AddImm, 1);
                    AddInstruction(SetFrame, srcIndex);

                    AddInstruction(AddImm, 1);
                    AddInstruction(Jump, "__memcpy-loop-" + to_string(loopLblCount));
                    AddInstruction(Label, "__memcpy-loopend-" + to_string(loopLblCount));
                    AddInstruction(Drop);
                    LocalVariables.removeLevel();
                }


            }
            else
                Throw("memcpy must have signature \"extern __intrinsic void memcpy(void* dst, void* src, int len);\"", TheRewriter, callee->getSourceRange());
            return true;
        } break;
        case JoaatCasedConst("memsetold"):
        {
            ChkHashCol("memset");
            if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isCharType() && argArray[2]->getType()->isIntegerType())
            {
                static uint32_t loopLblCount = -1;
                loopLblCount++;

                clang::Expr::EvalResult sResult, vResult;
                if (argArray[2]->EvaluateAsInt(sResult, context) && sResult.Val.getInt().getSExtValue() % stackWidth == 0 && argArray[1]->EvaluateAsInt(vResult, context))
                {
                    auto size = sResult.Val.getInt().getSExtValue();
                    uint32_t value = (uint32_t)vResult.Val.getInt().getSExtValue();

                    if (size <= 0)
                        Throw("memset size must greater then 0", TheRewriter, callee->getSourceRange());
                    if (value > 255)
                        Throw("memset value must be a byte", TheRewriter, callee->getSourceRange());

                    value &= 0xFF;
                    value = value << 24 | value << 16 | value << 8 | value;
                    int itemCount = size / stackWidth;
                    if (itemCount <= 50)
                    {
                        if (value == 0)
                        {
                            for (int i = 0; i < itemCount; i++)
                            {
                                AddInstruction(PushNullPtr);//push_0
                            }
                        }
                        else
                        {
                            for (int i = 0; i < itemCount; i++)
                            {
                                if (stackWidth == 8)
                                    AddInstruction(PushInt64, value, value);//value to set
                                else
                                    AddInstruction(PushInt, value);//value to set

                            }
                        }
                        AddInstruction(PushInt, itemCount);
                        parseExpression(argArray[0], false, true);
                        AddInstruction(FromStack);
                    }
                    else
                    {
                        LocalVariables.addLevel();
                        int destIndex = LocalVariables.addDecl("__memset-loop-dest", 1);
                        int incIndex = LocalVariables.addDecl("__memset-loop-inc", 1);

                        parseExpression(argArray[0], false, true);//dest
                        AddInstruction(SetFrame, destIndex);
                        AddInstruction(PushInt, 0);
                        AddInstruction(SetFrame, incIndex);

                        AddInstruction(Label, "__memset-loop-" + to_string(loopLblCount));
                        AddInstruction(GetFrame, incIndex);
                        AddInstruction(PushInt, size);
                        AddInstruction(JumpGE, "__memset-loopend-" + to_string(loopLblCount));

                        if (value == 0)
                        {
                            AddInstruction(PushNullPtr);//push 0
                        }
                        else
                        {
                            if (stackWidth == 8)
                                AddInstruction(PushInt64, value, value);//value to set
                            else
                                AddInstruction(PushInt, value);//value to set
                        }
                        AddInstruction(GetFrame, destIndex);
                        AddInstruction(GetFrame, incIndex);

                        AddInstruction(Add);

                        AddInstruction(PSet);

                        AddInstruction(GetFrame, incIndex);
                        AddInstruction(GetImmP, 1);//add imm 4 or 8 based on stack width
                        AddInstruction(SetFrame, incIndex);
                        AddInstruction(Jump, "__memset-loop-" + to_string(loopLblCount));
                        AddInstruction(Label, "__memset-loopend-" + to_string(loopLblCount));
                        LocalVariables.removeLevel();
                    }
                }
                else
                {

                    //TODO: fix for pc

                    LocalVariables.addLevel();

                    int destIndex = LocalVariables.addDecl("__memset-loop-dest", 1);
                    int valIndex = LocalVariables.addDecl("__memset-loop-val", 1);
                    int sizeIndex = LocalVariables.addDecl("__memset-loop-size", 1);

                    parseExpression(argArray[0], true, true);//dest
                    AddInstruction(SetFrame, destIndex);

                    parseExpression(argArray[1], false, true);//value
                    AddInstruction(ShiftLeft, 24);
                    AddInstruction(SetFrame, valIndex);

                    parseExpression(argArray[2], false, true);//size
                    AddInstruction(SetFrame, sizeIndex);

                    AddInstruction(PushInt, 0);
                    AddInstruction(Label, "__memset-loop-" + to_string(loopLblCount));
                    AddInstruction(Dup);
                    AddInstruction(GetFrame, sizeIndex);
                    AddInstruction(JumpGE, "__memset-loopend-" + to_string(loopLblCount));

                    AddInstruction(GetFrame, valIndex);
                    AddInstruction(GetFrame, destIndex);
                    AddInstruction(PGet);
                    AddInstruction(PushInt, 0xFFFFFF);
                    AddInstruction(And);
                    AddInstruction(Or);
                    AddInstruction(GetFrame, destIndex);
                    AddInstruction(PSet);

                    AddInstruction(GetFrame, destIndex);
                    AddInstruction(AddImm, 1);
                    AddInstruction(SetFrame, destIndex);

                    AddInstruction(AddImm, 1);
                    AddInstruction(Jump, "__memset-loop-" + to_string(loopLblCount));
                    AddInstruction(Label, "__memset-loopend-" + to_string(loopLblCount));
                    AddInstruction(Drop);
                    LocalVariables.removeLevel();
                }

            }
            else
                Throw("memset must have signature \"extern __intrinsic void memset(void* ptr, byte src, size_t len);\"", TheRewriter, callee->getSourceRange());
            return true;
        } break;
        case JoaatCasedConst("strcpy"):
        {
            ChkHashCol("strcpy");
            if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType() && argArray[2]->getType()->isIntegerType())
            {
                auto firstArgPointee = argArray[0]->getType().getTypePtr()->getPointeeType();
                if (!firstArgPointee.getTypePtr()->isCharType())
                {
                    Throw("First parameter of strcpy must be a char type pointer", TheRewriter, argArray[0]->getSourceRange());
                }
                if (firstArgPointee.isConstQualified())
                {
                    Throw("First parameter of strcpy cannot be a const qualified", TheRewriter, argArray[0]->getSourceRange());
                }
                parseExpression(argArray[1], false, true);
                parseExpression(argArray[0], false, true);

                clang::Expr::EvalResult result;
                if (argArray[2]->EvaluateAsInt(result, context))
                {
                    int64_t iValue = result.Val.getInt().isSigned() ? result.Val.getInt().getSExtValue() : result.Val.getInt().getExtValue();

                    if (iValue > 0 && iValue < 256)
                    {
                        AddInstruction(StrCopy, iValue);
                        return true;
                    }
                    else
                        Throw("Integer constant for string max length argument in strcpy must be between 1 and 255, got " + to_string(iValue), TheRewriter, argArray[2]->getSourceRange());
                }
                else
                    Throw("Expected integer constant for string max length argument in strcpy", TheRewriter, argArray[2]->getSourceRange());
            }
            else
                Throw("strcpy must have signature \"extern __intrinsic void strcpy(char* dest, const char* src, const byte len);\"", TheRewriter, callee->getSourceRange());

            return false;
        } break;
        case JoaatCasedConst("strcpy_s"):
        {
            ChkHashCol("strcpy_s");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType())
            {
                auto firstArgPointee = argArray[0]->getType().getTypePtr()->getPointeeType();
                if (!firstArgPointee.getTypePtr()->isCharType())
                {
                    Throw("First parameter of strcpy must be a char type pointer", TheRewriter, argArray[0]->getSourceRange());
                }
                if (firstArgPointee.isConstQualified())
                {
                    Throw("First parameter of strcpy cannot be a const qualified", TheRewriter, argArray[0]->getSourceRange());
                }
                auto size = getSafeIntrinSize(argArray[0]);
                parseExpression(argArray[1], false, true);
                parseExpression(argArray[0], false, true);
                AddInstruction(StrCopy, size);
                return true;
            }
            else
                Throw("strcpy_s must have signature \"extern __intrinsic void strcpy_s(char* dest, const char* src);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("stradd"):
        {
            ChkHashCol("stradd");
            if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType() && argArray[2]->getType()->isIntegerType())
            {
                parseExpression(argArray[1], false, true);
                if (isPushString(argArray[0]))
                {
                    Throw("stradd called with string literal as destination index", TheRewriter, argArray[0]->getSourceRange());
                }
                parseExpression(argArray[0], false, true);

                clang::Expr::EvalResult result;
                if (argArray[2]->EvaluateAsInt(result, context))
                {
                    int64_t iValue = result.Val.getInt().isSigned() ? result.Val.getInt().getSExtValue() : result.Val.getInt().getExtValue();
                    if (iValue > 0 && iValue < 256)
                    {
                        AddInstruction(StrAdd, iValue);
                        return true;
                    }
                    else
                        Throw("Integer constant for string max length argument in stradd must be between 1 and 255, got " + to_string(iValue), TheRewriter, argArray[2]->getSourceRange());
                }
                else
                    Throw("Expected integer constant for string max length argument in stradd", TheRewriter, argArray[2]->getSourceRange());
            }
            else
                Throw("stradd must have signature \"extern __intrinsic void stradd(char* dest, char* append, const byte len);\"", TheRewriter, callee->getSourceRange());

            return false;
        } break;
        case JoaatCasedConst("stradd_s"):
        {
            ChkHashCol("stradd_s");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isPointerType())
            {
                auto firstArgPointee = argArray[0]->getType().getTypePtr()->getPointeeType();
                if (!firstArgPointee.getTypePtr()->isCharType())
                {
                    Throw("First parameter of stradd_s must be a char type pointer", TheRewriter, argArray[0]->getSourceRange());
                }
                if (firstArgPointee.isConstQualified())
                {
                    Throw("First parameter of stradd_s cannot be a const qualified", TheRewriter, argArray[0]->getSourceRange());
                }
                auto size = getSafeIntrinSize(argArray[0]);
                parseExpression(argArray[1], false, true);
                parseExpression(argArray[0], false, true);
                AddInstruction(StrAdd, size);
                return true;
            }
            else
                Throw("stradd_s must have signature \"extern __intrinsic void stradd_s(char* dest, const char* src);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("straddi"):
        {
            ChkHashCol("straddi");
            if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
            {
                parseExpression(argArray[1], false, true);
                if (isPushString(argArray[0]))
                {
                    Throw("straddi called with string literal as destination index", TheRewriter, argArray[0]->getSourceRange());
                }
                parseExpression(argArray[0], false, true);

                clang::Expr::EvalResult result;
                if (argArray[2]->EvaluateAsInt(result, context))
                {
                    int64_t iValue = result.Val.getInt().isSigned() ? result.Val.getInt().getSExtValue() : result.Val.getInt().getExtValue();
                    if (iValue > 0 && iValue < 256)
                    {
                        AddInstruction(StrAddI, iValue);
                        return true;
                    }
                    else
                        Throw("Integer constant for string max length argument in straddi must be between 1 and 255, got " + to_string(iValue), TheRewriter, argArray[2]->getSourceRange());
                }
                else
                    Throw("Expected integer constant for string max length argument in straddi", TheRewriter, argArray[2]->getSourceRange());
            }
            else
                Throw("straddi must have signature \"extern __intrinsic void straddi(char* dest, int append, const byte len);\"", TheRewriter, callee->getSourceRange());

            return false;
        } break;
        case JoaatCasedConst("straddi_s"):
        {
            ChkHashCol("straddi_s");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType())
            {
                auto firstArgPointee = argArray[0]->getType().getTypePtr()->getPointeeType();
                if (!firstArgPointee.getTypePtr()->isCharType())
                {
                    Throw("First parameter of straddi_s must be a char type pointer", TheRewriter, argArray[0]->getSourceRange());
                }
                if (firstArgPointee.isConstQualified())
                {
                    Throw("First parameter of straddi_s cannot be a const qualified", TheRewriter, argArray[0]->getSourceRange());
                }
                auto size = getSafeIntrinSize(argArray[0]);
                parseExpression(argArray[1], false, true);
                parseExpression(argArray[0], false, true);
                AddInstruction(StrAddI, size);
                return true;
            }
            else
                Throw("straddi_s must have signature \"extern __intrinsic void straddi_s(char* dest, int value);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("itos"):
        {
            ChkHashCol("itos");
            if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
            {
                parseExpression(argArray[1], false, true);
                if (isPushString(argArray[0]))
                {
                    Throw("itos called with string literal as destination index", TheRewriter, argArray[0]->getSourceRange());
                }
                parseExpression(argArray[0], false, true);

                clang::Expr::EvalResult result;
                if (argArray[2]->EvaluateAsInt(result, context))
                {
                    int64_t iValue = result.Val.getInt().isSigned() ? result.Val.getInt().getSExtValue() : result.Val.getInt().getExtValue();
                    if (iValue > 0 && iValue < 256)
                    {
                        AddInstruction(ItoS, iValue);
                        return true;
                    }
                    else
                        Throw("Integer constant for string max length argument in itos must be between 1 and 255, got " + to_string(iValue), TheRewriter, argArray[2]->getSourceRange());
                }
                else
                    Throw("Expected integer constant for string max length argument in itos", TheRewriter, argArray[2]->getSourceRange());
            }
            else
                Throw("itos must have signature \"extern __intrinsic void itos(char* dest, int value, const byte len);\"", TheRewriter, callee->getSourceRange());

            return false;
        } break;
        case JoaatCasedConst("itos_s"):
        {
            ChkHashCol("itos_s");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType())
            {
                auto firstArgPointee = argArray[0]->getType().getTypePtr()->getPointeeType();
                if (!firstArgPointee.getTypePtr()->isCharType())
                {
                    Throw("First parameter of itos_s must be a char type pointer", TheRewriter, argArray[0]->getSourceRange());
                }
                if (firstArgPointee.isConstQualified())
                {
                    Throw("First parameter of itos_s cannot be a const qualified", TheRewriter, argArray[0]->getSourceRange());
                }
                auto size = getSafeIntrinSize(argArray[0]);
                parseExpression(argArray[1], false, true);
                parseExpression(argArray[0], false, true);
                AddInstruction(ItoS, size);
                return true;
            }
            else
                Throw("itos_s must have signature \"extern __intrinsic void itos_s(char* dest, int value);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("getHashKey"):
        {
            ChkHashCol("getHashKey");
            if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isPointerType() && argArray[0]->getType()->getPointeeType()->isCharType())
            {
                parseExpression(argArray[0], false, true);
                AddInstruction(GetHash);
                return true;
            }
            Throw("getHashKey must have signature \"extern __intrinsic int getHashKey(char *string);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
#pragma endregion
#pragma region Misc_Opcodes
        case JoaatCasedConst("__varIndex"):
        {
            ChkHashCol("__varIndex");

            if (argCount == 1 && callee->getReturnType()->isIntegerType())
            {
                string str;
                if (EvaluateAsString(argArray[0], str))
                {
                    uint32_t index = 0;
                    StaticData* sData = NULL;
                    if (LocalVariables.find(str, index))
                    {
                        AddInstruction(PushInt, index);
                        return true;
                    }
                    else if ((sData = scriptData.findStatic(str)))
                    {
                        AddInstruction(PushInt, sData->getIndex());
                        return true;
                    }
                    else
                        Throw("__varIndex varName not found", TheRewriter, callee->getSourceRange());
                } EvalFailedStr
            }
            else Throw("__varIndex must have signature \"extern __unsafeIntrinsic const uint __varIndex(const char* varName);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("__getReturnAddress"):
        {
            ChkHashCol("__getReturnAddress");

            if (argCount == 0 && callee->getReturnType()->isIntegerType())
            {
                AddInstruction(GetFrame, scriptData.getCurrentFunction()->getParamCount());
                return true;
            }
            else
            {
                Throw("__getReturnAddress must have signature \"extern __unsafeIntrinsic int __getReturnAddress();\"", TheRewriter, callee->getSourceRange());
            }
        } break;
        case JoaatCasedConst("__addressOFReturnAddress"):
        {
            ChkHashCol("__addressOFReturnAddress");

            if (argCount == 0 && callee->getReturnType()->isPointerType() && callee->getReturnType()->getPointeeType()->isIntegerType())
            {
                AddInstruction(GetFrameP, scriptData.getCurrentFunction()->getParamCount());
                return true;
            }
            else
            {
                Throw("__addressOFReturnAddress must have signature \"extern __unsafeIntrinsic int* __addressOFReturnAddress();\"", TheRewriter, callee->getSourceRange());
            }
        } break;
#pragma endregion
#pragma region Math/Conversions
        case JoaatCasedConst("reinterpretIntToFloat"):
        {
            ChkHashCol("reinterpretIntToFloat");
            if (argCount == 1 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isIntegerType())
            {
                parseExpression(argArray[0], false, true);
                return true;
            }
            Throw("reinterpretIntToFloat must have signature \"extern __intrinsic float reinterpretIntToFloat(int intValue);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("reinterpretFloatToInt"):
        {
            ChkHashCol("reinterpretFloatToInt");
            if (argCount == 1 && callee->getReturnType()->isIntegerType() && argArray[0]->getType()->isRealFloatingType())
            {
                parseExpression(argArray[0], false, true);
                return true;
            }
            Throw("reinterpretFloatToInt must have signature \"extern __intrinsic int reinterpretFloatToInt(float floatValue);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("toVector3"):
        {
            ChkHashCol("toVector3");

            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && argArray[0]->getType()->isRealFloatingType())
            {
                parseExpression(argArray[0], false, true);
                AddInstruction(FtoV);
                return true;
            }
            Throw("tovector3 must have signature \"extern __intrinsic vector3 tovector3(float value);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector3Add"):
        {
            ChkHashCol("vector3Add");

            if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
            {

                parseExpression(argArray[0], false, true);
                parseExpression(argArray[1], false, true);
                AddInstruction(VAdd);
                return true;
            }
            Throw("vector3Add must have signature \"extern __intrinsic vector3 vector3Add(vector3 left, vector3 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector3Sub"):
        {
            ChkHashCol("vector3Sub");

            if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
            {

                parseExpression(argArray[0], false, true);
                parseExpression(argArray[1], false, true);
                AddInstruction(VSub);
                return true;
            }
            Throw("vector3Sub must have signature \"extern __intrinsic vector3 vector3Sub(vector3 left, vector3 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector3Mult"):
        {
            ChkHashCol("vector3Mult");

            if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
            {

                parseExpression(argArray[0], false, true);
                parseExpression(argArray[1], false, true);
                AddInstruction(VMult);
                return true;
            }
            Throw("vector3Mult must have signature \"extern __intrinsic vector3 vector3Mult(vector3 left, vector3 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector3Div"):
        {
            ChkHashCol("vector3Div");

            if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
            {

                parseExpression(argArray[0], false, true);
                parseExpression(argArray[1], false, true);
                AddInstruction(VDiv);
                return true;
            }
            Throw("vector3Div must have signature \"extern __intrinsic vector3 vector3Div(vector3 left, vector3 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector3Neg"):
        {
            ChkHashCol("vector3Neg");

            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
            {

                parseExpression(argArray[0], false, true);
                AddInstruction(VNeg);
                return true;
            }
            Throw("vector3Neg must have signature \"extern __intrinsic vector3 vector3Neg(vector3 vector)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector3Dot"):
        {
            ChkHashCol("vector3Dot");

            if (argCount == 2 && callee->getReturnType()->isRealFloatingType() && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 3)
            {

                parseExpression(argArray[0], false, true);
                parseExpression(argArray[1], false, true);
                AddInstruction(VMult);
                AddInstruction(FAdd);
                AddInstruction(FAdd);
                return true;
            }
            Throw("vector3Dot must have signature \"extern __intrinsic float vector3Dot(vector3 left, vector3 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("toVector2"):
        {
            ChkHashCol("toVector2");

            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && argArray[0]->getType()->isRealFloatingType())
            {
                parseExpression(argArray[0], false, true);
                AddInstruction(Dup);
                return true;
            }
            Throw("tovector2 must have signature \"extern __intrinsic vector2 tovector2(float value);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector2Add"):
        {
            ChkHashCol("vector2Add");

            if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
            {

                parseExpression(argArray[0], false, true);
                AddInstruction(PushFloat, 0.0f);
                parseExpression(argArray[1], false, true);
                AddInstruction(PushFloat, 0.0f);
                AddInstruction(VAdd);
                AddInstruction(Drop);
                return true;
            }
            Throw("vector2Add must have signature \"extern __intrinsic vector2 vector2Add(vector2 left, vector2 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector2Sub"):
        {
            ChkHashCol("vector2Sub");

            if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
            {
                parseExpression(argArray[0], false, true);
                AddInstruction(PushFloat, 0.0f);
                parseExpression(argArray[1], false, true);
                AddInstruction(PushFloat, 0.0f);
                AddInstruction(VSub);
                AddInstruction(Drop);
                return true;
            }
            Throw("vector2Sub must have signature \"extern __intrinsic vector2 vector2Sub(vector2 left, vector2 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector2Mult"):
        {
            ChkHashCol("vector2Mult");

            if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
            {

                parseExpression(argArray[0], false, true);
                AddInstruction(PushFloat, 0.0f);
                parseExpression(argArray[1], false, true);
                AddInstruction(PushFloat, 0.0f);
                AddInstruction(VMult);
                AddInstruction(Drop);
                return true;
            }
            Throw("vector2Mult must have signature \"extern __intrinsic vector2 vector3Mult(vector2 left, vector2 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector2Div"):
        {
            ChkHashCol("vector2Div");

            if (argCount == 2 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
            {

                parseExpression(argArray[0], false, true);
                AddInstruction(PushFloat, 0.0f);
                parseExpression(argArray[1], false, true);
                AddInstruction(PushFloat, 0.0f);
                AddInstruction(VDiv);
                AddInstruction(Drop);
                return true;
            }
            Throw("vector2Div must have signature \"extern __intrinsic vector2 vector2Div(vector2 left, vector2 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector2Neg"):
        {
            ChkHashCol("vector2Neg");

            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2)
            {

                parseExpression(argArray[0], false, true);
                AddInstruction(PushFloat, 0.0f);
                AddInstruction(VNeg);
                AddInstruction(Drop);
                return true;
            }
            Throw("vector2Neg must have signature \"extern __intrinsic vector2 vector2Neg(vector2 vector)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector2Dot"):
        {
            ChkHashCol("vector2Dot");

            if (argCount == 2 && callee->getReturnType()->isRealFloatingType() && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 2)
            {

                parseExpression(argArray[0], false, true);
                AddInstruction(PushFloat, 0.0f);
                parseExpression(argArray[1], false, true);
                AddInstruction(PushFloat, 0.0f);
                AddInstruction(VMult);
                AddInstruction(Drop);
                AddInstruction(FAdd);
                return true;
            }
            Throw("vector2Dot must have signature \"extern __intrinsic float vector2Dot(vector2 left, vector2 right)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("fMod"):
        {
            ChkHashCol("fMod");
            if (argCount == 2 && callee->getReturnType()->isRealFloatingType() && argArray[0]->getType()->isRealFloatingType() && argArray[1]->getType()->isRealFloatingType())
            {
                parseExpression(argArray[0], false, true);
                parseExpression(argArray[1], false, true);
                AddInstruction(FMod);
                return true;
            }
        } break;
        case JoaatCasedConst("bitTest"):
        {
            ChkHashCol("bitTest");
            if (argCount == 2 && callee->getReturnType()->isBooleanType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult result;
                if (argArray[1]->EvaluateAsInt(result, context))
                {
                    auto iResult = result.Val.getInt().getSExtValue();
                    if (iResult < 32 && iResult >= 0)
                    {
                        parseExpression(argArray[0], false, true);
                        AddInstruction(IsBitSet, (uint8_t)iResult);
                        return true;
                    }
                }
                Throw("bitIndex argument for bitTest must be a compile time constant integer between 0 and 31", TheRewriter, argArray[1]->getSourceRange());
            }
            Throw("bitTest must have signature \"extern __intrinsic bool bitTest(int value, const byte bitIndex);\"", TheRewriter, callee->getSourceRange());
        } break;
        case JoaatCasedConst("bitSet"):
        {
            ChkHashCol("bitSet");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[0]->getType()->getPointeeType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult result;
                if (argArray[1]->EvaluateAsInt(result, context))
                {
                    auto iResult = result.Val.getInt().getSExtValue();
                    if (iResult < 32 && iResult >= 0)
                    {
                        parseExpression(argArray[0], false, true);
                        AddInstruction(BitSet, (uint8_t)iResult);
                        return true;
                    }
                }
                Throw("bitIndex argument for bitSet must be a compile time constant integer between 0 and 31", TheRewriter, argArray[1]->getSourceRange());
            }
            Throw("bitSet must have signature \"extern __intrinsic bool bitSet(int* address, const byte bitIndex);\"", TheRewriter, callee->getSourceRange());
        } break;
        case JoaatCasedConst("bitReset"):
        {
            ChkHashCol("bitReset");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[0]->getType()->getPointeeType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult result;
                if (argArray[1]->EvaluateAsInt(result, context))
                {
                    auto iResult = result.Val.getInt().getSExtValue();
                    if (iResult < 32 && iResult >= 0)
                    {
                        parseExpression(argArray[0], false, true);
                        AddInstruction(BitReset, (uint8_t)iResult);
                        return true;
                    }
                }
                Throw("bitIndex argument for bitReset must be a compile time constant integer between 0 and 31", TheRewriter, argArray[1]->getSourceRange());
            }
            Throw("bitReset must have signature \"extern __intrinsic bool bitReset(int* address, const byte bitIndex);\"", TheRewriter, callee->getSourceRange());
        } break;
        case JoaatCasedConst("bitFlip"):
        {
            ChkHashCol("bitFlip");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[0]->getType()->getPointeeType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult result;
                if (argArray[1]->EvaluateAsInt(result, context))
                {
                    auto iResult = result.Val.getInt().getSExtValue();
                    if (iResult < 32 && iResult >= 0)
                    {
                        parseExpression(argArray[0], false, true);
                        AddInstruction(BitFlip, (uint8_t)iResult);
                        return true;
                    }
                }
                Throw("bitIndex argument for bitFlip must be a compile time constant integer between 0 and 31", TheRewriter, argArray[1]->getSourceRange());
            }
            Throw("bitFlip must have signature \"extern __intrinsic bool bitFlip(int* address, const byte bitIndex);\"", TheRewriter, callee->getSourceRange());
        } break;
        case JoaatCasedConst("vector3ToVector2"):
        {
            ChkHashCol("vector3ToVector2");

            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 2 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
            {

                parseExpression(argArray[0], false, true);
                AddInstruction(Drop);
                return true;
            }
            Throw("vector3ToVector2 must have signature \"extern __intrinsic vector2 vector3ToVector2(vector3 vector)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector2ToVector3"):
        {
            ChkHashCol("vector2ToVector3");

            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 2)
            {

                parseExpression(argArray[0], false, true);
                AddInstruction(PushFloat, 0.0f);
                return true;
            }
            Throw("vector2ToVector3 must have signature \"extern __intrinsic vector3 vector2ToVector3(vector2 vector)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("vector3Flatten"):
        {
            ChkHashCol("vector3Flatten");

            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3 && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
            {
                parseExpression(argArray[0], false, true);


                //GTA Coord Type = Y Depth
                //RDR Coord Type = Z Depth
                if (scriptData.getBuildType() == BT_RDR_SCO || BT_RDR_XSC)
                {
                    AddInstruction(PushFloat, 1.0f);
                    AddInstruction(PushFloat, 0.0f);
                    AddInstruction(PushFloat, 1.0f);
                    AddInstruction(VMult);
                }
                else
                {
                    AddInstruction(Drop);
                    AddInstruction(PushFloat, 0.0f);
                }

                return true;
            }
            Throw("vector3Flatten must have signature \"extern __intrinsic vector3 vector3Flatten(vector3 vector)\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("setLoDWord"):
        {
            ChkHashCol("setLoDWord");

            if (scriptData.getStackWidth() == 8)
            {
                if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 1)
                {
                    parseExpression(argArray[0], false, true);
                    AddInstruction(Dup);
                    AddInstruction(PGet);
                    AddInstruction(PushInt, 0);
                    AddInstructionComment(And, "clear lower bits");
                    parseExpression(argArray[1], false, true);
                    AddInstruction(Or);
                    AddInstruction(PeekSet);
                    AddInstruction(Drop);
                    return true;
                }
                else
                {
                    Throw("setLoDWord must have signature \"extern __intrinsic void setLoDWord(void* addr, int value)\"", TheRewriter, callee->getSourceRange());
                }
            }
            else
            {
                Throw("setHiDWord intrinsic is only available on 64 bit builds");
            }
        } break;
        case JoaatCasedConst("setHiDWord"):
        {
            ChkHashCol("setHiDWord");

            if (scriptData.getStackWidth() == 8)
            {
                if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 1)
                {
                    parseExpression(argArray[0], false, true);
                    AddInstruction(AddImm, 4);
                    AddInstruction(Dup);
                    AddInstruction(PGet);
                    AddInstruction(PushInt, 0);
                    AddInstructionComment(And, "clear lower bits");
                    parseExpression(argArray[1], false, true);
                    AddInstruction(Or);
                    AddInstruction(PeekSet);
                    AddInstruction(Drop);
                    return true;
                }
                else
                {
                    Throw("setHiDWord must have signature \"extern __intrinsic void setHiDWord(void* addr, int value)\"", TheRewriter, callee->getSourceRange());
                }
            }
            else
            {
                Throw("setHiDWord intrinsic is only available on 64 bit builds");
            }
        } break;
        case JoaatCasedConst("getLoDWord"):
        {
            ChkHashCol("getLoDWord");

            if (scriptData.getStackWidth() == 8)
            {
                if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1 && argArray[0]->getType()->isPointerType())
                {
                    //AddInstruction(PushNullPtr);
                    parseExpression(argArray[0], false, true);
                    AddInstruction(PGet);
                    //AddInstruction(Or);
                    return true;
                }
                else
                {
                    Throw("getLoDWord must have signature \"extern __intrinsic int getLoDWord(void* addr)\"", TheRewriter, callee->getSourceRange());
                }
            }
            else
            {
                Throw("getLoDWord intrinsic is only available on 64 bit builds");
            }
        } break;
        case JoaatCasedConst("getHiDWord"):
        {
            ChkHashCol("getHiDWord");

            if (scriptData.getStackWidth() == 8)
            {
                if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1 && argArray[0]->getType()->isPointerType())
                {
                    //AddInstruction(PushNullPtr);
                    parseExpression(argArray[0], false, true);
                    AddInstruction(AddImm, 4);
                    AddInstruction(PGet);
                    //AddInstruction(Or);
                    return true;
                }
                else
                {
                    Throw("getHiDWord must have signature \"extern __intrinsic int getHiDWord(void* addr)\"", TheRewriter, callee->getSourceRange());
                }
            }
            else
            {
                Throw("getHiDWord intrinsic is only available on 64 bit builds");
            }
        } break;
        case JoaatCasedConst("getByte"):
        {
            ChkHashCol("getByte");
            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1 && argArray[0]->getType()->isPointerType())
            {
                parseExpression(argArray[0], false, true);
                AddInstruction(PGet);
                if (scriptData.getBuildPlatform() == P_PC)
                {
                    AddInstruction(PushInt, 255);
                    AddInstruction(And);
                }
                else
                {
                    AddInstruction(ShiftRight, 24);
                }
                return true;
            }
            else
            {
                Throw("getByte must have signature \"extern __intrinsic unsigned char getByte(void* addr)\"", TheRewriter, callee->getSourceRange());
            }
        } break;
        case JoaatCasedConst("setByte"):
        {
            ChkHashCol("setByte");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 1)
            {
                parseExpression(argArray[0], false, true);
                AddInstruction(Dup);
                AddInstruction(PGet);
                AddInstruction(PushInt, 0x00FFFFFF);
                AddInstruction(And);
                parseExpression(argArray[1], false, true);

                if (scriptData.getBuildPlatform() == P_PC)
                {
                    AddInstruction(PushInt, 255);
                    AddInstruction(And);
                }
                else
                {
                    AddInstruction(ShiftLeft, 24);
                }

                AddInstruction(Or);
                AddInstruction(PeekSet);
                AddInstruction(Drop);
                return true;

                //old set_bits_in_range code
                //parseExpression(argArray[0], false, true);
                //AddInstruction(PushInt, 0);
                //AddInstruction(PushInt, 7);
                //clang::Expr::EvalResult result;
                //if (argArray[1]->EvaluateAsInt(result, context))
                //{
                //	if (result.Val.getInt().getExtValue() > 0xFF)
                //	{
                //		Warn("Result does not fit into a byte", TheRewriter, argArray[1]->getSourceRange());
                //	}
                //	AddInstruction(PushInt, result.Val.getInt().getExtValue() & 0xFF);
                //}
                //else
                //{
                //	parseExpression(argArray[1], false, true);
                //	AddInstruction(PushInt, 0xFF);
                //	AddInstruction(And);
                //}
                //AddInstruction(Native, "set_bits_in_range", (scriptData.getBuildPlatform() == P_PC ? 0x8EF07E15701D61ED : JoaatConst("set_bits_in_range")), 4, 0);
                //return true;
            }
            else
            {
                Throw("setByte must have signature \"extern __intrinsic void setByte(void* addr, unsigned char value)\"", TheRewriter, callee->getSourceRange());
            }
        } break;
#pragma endregion
#pragma region Variables 
        case JoaatCasedConst("setStaticAtIndex"):
        {
            ChkHashCol("setStaticAtIndex");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 1)
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->EvaluateAsInt(result, context))
                {
                    parseExpression(argArray[1], false, true);
                    AddInstruction(SetStaticRaw, result.Val.getInt().getSExtValue());
                    return true;
                } EvalFailed
            } BadIntrin
        } break;
        case JoaatCasedConst("getStaticAtIndex"):
        {
            ChkHashCol("getStaticAtIndex");
            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->EvaluateAsInt(result, context))
                {
                    AddInstruction(GetStaticRaw, result.Val.getInt().getSExtValue());
                    return true;
                } EvalFailed
            } BadIntrin
        } break;
        case JoaatCasedConst("getStaticPtrAtIndex"):
        {
            ChkHashCol("getStaticPtrAtIndex");
            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->EvaluateAsInt(result, context))
                {
                    AddInstruction(GetStaticPRaw, result.Val.getInt().getSExtValue());
                    return true;
                } EvalFailed
            } BadIntrin
        } break;
        case JoaatCasedConst("setGlobalAtIndex"):
        {
            ChkHashCol("setGlobalAtIndex");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && getSizeFromBytes(getSizeOfType(argArray[1]->getType().getTypePtr())) == 1)
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->EvaluateAsInt(result, context))
                {
                    parseExpression(argArray[1], false, true);
                    AddInstruction(SetGlobal, result.Val.getInt().getSExtValue());
                    return true;
                } EvalFailed
            } BadIntrin
        } break;
        case JoaatCasedConst("getGlobalAtIndex"):
        {
            ChkHashCol("getGlobalAtIndex");
            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->EvaluateAsInt(result, context))
                {
                    AddInstruction(GetGlobal, result.Val.getInt().getSExtValue());
                    return true;
                } EvalFailed
            } BadIntrin
        } break;
        case JoaatCasedConst("getGlobalPtrAtIndex"):
        {
            ChkHashCol("getGlobalPtrAtIndex");
            if (argCount == 1 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 1)
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->EvaluateAsInt(result, context))
                {
                    AddInstruction(GetGlobalP, result.Val.getInt().getSExtValue());
                    return true;
                } EvalFailed
            } BadIntrin
        } break;
        case JoaatCasedConst("getPtrFromArrayIndex"):
        {
            ChkHashCol("getPtrFromArrayIndex");
            if (argCount == 3 && callee->getReturnType()->isPointerType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult itemSize;
                if (argArray[2]->EvaluateAsInt(itemSize, context))
                {
                    if (itemSize.Val.getInt().getSExtValue() < 1 || itemSize.Val.getInt().getSExtValue() > 0xFFFF)
                        Throw("getPtrFromArrayIndex item size expected a value between 1 and 65535, got'" + to_string(itemSize.Val.getInt().getSExtValue()) + "'", TheRewriter, argArray[2]->getSourceRange());

                    clang::Expr::EvalResult index;
                    if (Option_OptimizationLevel > OptimisationLevel::OL_Trivial && argArray[1]->EvaluateAsInt(index, context) && ((itemSize.Val.getInt().getSExtValue() * index.Val.getInt().getSExtValue()) < 0xFFFF))
                    {
                        parseExpression(argArray[0], false, true);
                        AddInstruction(GetImmP, 1 + itemSize.Val.getInt().getSExtValue() * index.Val.getInt().getSExtValue());
                        return true;
                    }
                    else
                    {
                        //get_arrayp
                        parseExpression(argArray[1], false, true);//index

                        const int BT = scriptData.getBuildType();
                        if (BT == BT_GTAIV || BT == BT_GTAIV_TLAD || BT == BT_GTAIV_TBOGT)
                        {
                            AddInstruction(PushInt, (int32_t)itemSize.Val.getInt().getSExtValue());
                        }
                        parseExpression(argArray[0], false, true);//pointer
                        AddInstruction(GetArrayP, itemSize.Val.getInt().getSExtValue());
                        return true;
                    }
                } EvalFailed
            } BadIntrin
        } break;
        case JoaatCasedConst("getPtrImmIndex"):
        {
            ChkHashCol("getPtrImmIndex");
            if (argCount == 2 && callee->getReturnType()->isPointerType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult index;
                if (argArray[1]->EvaluateAsInt(index, context) && index.Val.getInt().getSExtValue() >= 0 && index.Val.getInt().getSExtValue() <= 0xFFFF)
                {
                    parseExpression(argArray[0], false, true);
                    AddInstructionComment(GetImmP, "imm_" + to_string(index.Val.getInt().getSExtValue()), index.Val.getInt().getSExtValue());
                    return true;
                }
                else
                {
                    parseExpression(argArray[0], false, true);
                    parseExpression(argArray[1], false, true);
                    AddInstruction(GetImmPStack);
                    return true;
                }
            } BadIntrin
        } break;
#pragma endregion
#pragma region Custom_ASM
        case JoaatCasedConst("__popMult"):
        {
            ChkHashCol("__popMult");
            //	out << call->getExprLoc().
            if (argCount == 1 && callee->getReturnType()->isVoidType())
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->getType()->isIntegerType())
                {
                    if (argArray[0]->EvaluateAsInt(result, context))
                    {
                        int intValue = result.Val.getInt().getSExtValue();
                        if (intValue <= 0)
                        {
                            Throw("Expected positive integer constant for pop amount argument in popMult, got " + to_string(intValue), TheRewriter, argArray[0]->getSourceRange());
                            return false;
                        }
                        for (int i = 0; i < intValue; i++)
                        {
                            AddInstruction(Drop);
                        }
                        return true;;
                    }
                    Throw("Expected positive integer constant for pop amount argument in popMult", TheRewriter, argArray[0]->getSourceRange());
                    return false;
                }
            }
            Throw("popMult must have signature \"extern __intrinsic void popMult(const int amount);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("__pushV"):
        {
            ChkHashCol("__pushV");

            if (argCount == 1 && callee->getReturnType()->isVoidType() && getSizeFromBytes(getSizeOfType(argArray[0]->getType().getTypePtr())) == 3)
            {
                parseExpression(argArray[0], false, true);
                return true;
            }
            Throw("pushVector3 must have signature \"extern __intrinsic void pushVector3(vector3 vec3Value);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("__pushStruct"):
        {
            ChkHashCol("__pushStruct");
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isVoidPointerType())
            {
                if (isa<CastExpr>(argArray[0]))
                {
                    const CastExpr* castee = cast<CastExpr>(argArray[0]);
                    if (castee->getCastKind() == CK_BitCast)
                    {
                        int size = getSizeFromBytes(getSizeOfType(castee->getSubExpr()->getType()->getPointeeType().getTypePtr()));
                        AddInstructionConditionallyComment(size > 1, PushInt, "Struct Size", size);
                        parseExpression(argArray[0], false, true);
                        AddInstructionCondition(size > 1, ToStack, PGet);
                        return true;
                    }
                }
                Throw("Couldnt extract type information from the argument in pushStruct", TheRewriter, argArray[0]->getSourceRange());
                return false;
            }
            Throw("pushStruct must have signature \"extern __intrinsic void pushStruct(void *Struct);\"", TheRewriter, callee->getSourceRange());
            return false;;
        } break;
        case JoaatCasedConst("__popStruct"):
        {
            ChkHashCol("__popStruct");

            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isVoidPointerType())
            {
                if (isa<CastExpr>(argArray[0]))
                {
                    const CastExpr* castee = cast<CastExpr>(argArray[0]);
                    if (castee->getCastKind() == CK_BitCast)
                    {
                        int size = getSizeFromBytes(getSizeOfType(castee->getSubExpr()->getType()->getPointeeType().getTypePtr()));
                        AddInstructionConditionallyComment(size > 1, PushInt, "Struct Size", size);
                        parseExpression(argArray[0], false, true);
                        AddInstructionCondition(size > 1, FromStack, PSet);
                        return true;
                    }
                }
                Throw("Couldnt extract type information from the argument in popStruct", TheRewriter, argArray[0]->getSourceRange());
                return false;
            }
            Throw("popStruct must have signature \"extern __intrinsic void popStruct(void *Struct);\"", TheRewriter, callee->getSourceRange());
            return false;;
        } break;
        case JoaatCasedConst("__rev"):
        {
            ChkHashCol("__rev");

            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->EvaluateAsInt(result, context))
                {
                    int64_t value = result.Val.getInt().getSExtValue();
                    if (value >= 2)
                    {
                        LocalVariables.addLevel();
                        int startDeclIndex = LocalVariables.addDecl("__rev-container-var-decl", value);

                        //FromStack into it
                        AddInstruction(PushInt, value);
                        AddInstruction(GetFrameP, startDeclIndex);
                        AddInstruction(FromStack);

                        //Put them back on stack in reverse
                        for (int i = startDeclIndex + value - 1; i >= startDeclIndex; i--)
                        {
                            AddInstruction(GetFrame, i);
                        }

                        LocalVariables.removeLevel();
                    }
                    else
                        Warn("Reverse called with " + to_string(value) + " exchange num.  Expected >= 2", TheRewriter, argArray[0]->getSourceRange());
                }
                else
                {
                    Throw("Reverse count must be called with a compile time constant", TheRewriter, argArray[0]->getSourceRange());
                    return false;
                }
                return true;
            }
            Throw("rev must have signature \"extern __intrinsic void rev(const int numItems);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("__exch"):
        {
            ChkHashCol("__exch");

            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->EvaluateAsInt(result, context))
                {
                    const Expr* expr = argArray[0]->IgnoreParens()->IgnoreCasts();
                    if (isa<UnaryExprOrTypeTraitExpr>(expr) && cast<UnaryExprOrTypeTraitExpr>(expr)->getKind() == UETT_SizeOf)
                    {
                        Warn("Exchange called with a sizeof operation, did you mean to use stacksizeof", TheRewriter, argArray[0]->getSourceRange());
                    }
                    int64_t value = result.Val.getInt().getSExtValue();
                    if (value > 0)
                    {
                        LocalVariables.addLevel();
                        int firstItemIndex = LocalVariables.addDecl("__exchangeItem1", value);
                        int secondItemIndex = LocalVariables.addDecl("__exchangeItem2", value);

                        if (value > 1)
                        {
                            //FromStack into it
                            AddInstruction(PushInt, value);
                            AddInstruction(GetFrameP, firstItemIndex);
                            AddInstruction(FromStack);
                            AddInstruction(PushInt, value);
                            AddInstruction(GetFrameP, secondItemIndex);
                            AddInstruction(FromStack);

                            //Put them back on stack in reverse
                            AddInstruction(PushInt, value);
                            AddInstruction(GetFrameP, firstItemIndex);
                            AddInstruction(ToStack);
                            AddInstruction(PushInt, value);
                            AddInstruction(GetFrameP, secondItemIndex);
                            AddInstruction(ToStack);

                        }
                        else
                        {
                            AddInstruction(SetFrame, firstItemIndex);
                            AddInstruction(SetFrame, secondItemIndex);
                            AddInstruction(GetFrame, firstItemIndex);
                            AddInstruction(GetFrame, secondItemIndex);
                        }
                        LocalVariables.removeLevel();
                    }
                    else
                        Warn("Exchange called with " + to_string(value) + " item size num.  Expected a positive value", TheRewriter, argArray[0]->getSourceRange());
                }
                else
                {
                    Throw("Exchange structSize must be called with a compile time constant", TheRewriter, argArray[0]->getSourceRange());
                    return false;
                }
                return true;
            }
            Throw("exchange must have signature \"extern __intrinsic void exchange(const int structStackSize);\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("__popI"):
        {
            ChkHashCol("__popI");
            if (argCount == 0 && callee->getReturnType()->isIntegerType())
            {
                return true;
            }
            Throw("popInt must have signature \"extern __intrinsic int pushInt();\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("__popF"):
        {
            ChkHashCol("__popF");
            if (argCount == 0 && callee->getReturnType()->isRealFloatingType())
            {
                return true;
            }
            Throw("popFloat must have signature \"extern __intrinsic float pushFloat();\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
        case JoaatCasedConst("__popV"):
        {
            ChkHashCol("__popV");

            if (argCount == 0 && getSizeFromBytes(getSizeOfType(callee->getReturnType().getTypePtr())) == 3)
            {
                return true;
            }
            Throw("popVector3 must have signature \"extern __intrinsic vector3 popVector3();\"", TheRewriter, callee->getSourceRange());
            return false;
        } break;
#pragma endregion
#pragma region ASM 
        case JoaatCasedConst("__nop"):
        {
            ChkHashCol("__nop");
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult result;
                if (argArray[0]->EvaluateAsInt(result, context) && result.Val.getInt().getSExtValue() > 0 && result.Val.getInt().getSExtValue() <= 4096)
                {
                    AddInstruction(Nop, result.Val.getInt().getSExtValue());
                    return true;
                }
                else
                    Throw("nopCount argument must be a constant integer between 1 and 4096", TheRewriter, argArray[0]->getSourceRange());
            } BadIntrin
        } break;
        case JoaatCasedConst("__add"):			AddAsmIntrinsic("__add", GetInsPtr(Add)); break;
        case JoaatCasedConst("__sub"):			AddAsmIntrinsic("__sub", GetInsPtr(Sub)); break;
        case JoaatCasedConst("__mult"):			AddAsmIntrinsic("__mult", GetInsPtr(Mult)); break;
        case JoaatCasedConst("__div"):			AddAsmIntrinsic("__div", GetInsPtr(Div)); break;
        case JoaatCasedConst("__mod"):			AddAsmIntrinsic("__mod", GetInsPtr(Mod)); break;
        case JoaatCasedConst("__not"):			AddAsmIntrinsic("__not", GetInsPtr(Not)); break;
        case JoaatCasedConst("__neg"):			AddAsmIntrinsic("__neg", GetInsPtr(Neg)); break;
        case JoaatCasedConst("__cmpEq"):		AddAsmIntrinsic("__cmpEq", GetInsPtr(CmpEq)); break;
        case JoaatCasedConst("__cmpNe"):		AddAsmIntrinsic("__cmpNe", GetInsPtr(CmpNe)); break;
        case JoaatCasedConst("__cmpGt"):		AddAsmIntrinsic("__cmpGt", GetInsPtr(CmpGt)); break;
        case JoaatCasedConst("__cmpGe"):		AddAsmIntrinsic("__cmpGe", GetInsPtr(CmpGe)); break;
        case JoaatCasedConst("__cmpLt"):		AddAsmIntrinsic("__cmpLt", GetInsPtr(CmpLt)); break;
        case JoaatCasedConst("__cmpLe"):		AddAsmIntrinsic("__cmpLe", GetInsPtr(CmpLe)); break;
        case JoaatCasedConst("__addF"):			AddAsmIntrinsic("__addF", GetInsPtr(FAdd)); break;
        case JoaatCasedConst("__subF"):			AddAsmIntrinsic("__subF", GetInsPtr(FSub)); break;
        case JoaatCasedConst("__multF"):		AddAsmIntrinsic("__multF", GetInsPtr(FMult)); break;
        case JoaatCasedConst("__divF"):			AddAsmIntrinsic("__divF", GetInsPtr(FDiv)); break;
        case JoaatCasedConst("__modF"):			AddAsmIntrinsic("__modF", GetInsPtr(FMod)); break;
        case JoaatCasedConst("__negF"):			AddAsmIntrinsic("__negF", GetInsPtr(FNeg)); break;
        case JoaatCasedConst("__cmpEqF"):		AddAsmIntrinsic("__cmpEqF", GetInsPtr(FCmpEq)); break;
        case JoaatCasedConst("__cmpNeF"):		AddAsmIntrinsic("__cmpNeF", GetInsPtr(FCmpNe)); break;
        case JoaatCasedConst("__cmpGtF"):		AddAsmIntrinsic("__cmpGtF", GetInsPtr(FCmpGt)); break;
        case JoaatCasedConst("__cmpGeF"):		AddAsmIntrinsic("__cmpGeF", GetInsPtr(FCmpGe)); break;
        case JoaatCasedConst("__cmpLtF"):		AddAsmIntrinsic("__cmpLtF", GetInsPtr(FCmpLt)); break;
        case JoaatCasedConst("__cmpLeF"):		AddAsmIntrinsic("__cmpLeF", GetInsPtr(FCmpLe)); break;
        case JoaatCasedConst("__addV"):			AddAsmIntrinsic("__addV", GetInsPtr(VAdd)); break;
        case JoaatCasedConst("__subV"):			AddAsmIntrinsic("__subV", GetInsPtr(VSub)); break;
        case JoaatCasedConst("__multV"):		AddAsmIntrinsic("__multV", GetInsPtr(VMult)); break;
        case JoaatCasedConst("__divV"):			AddAsmIntrinsic("__divV", GetInsPtr(VDiv)); break;
        case JoaatCasedConst("__negV"):			AddAsmIntrinsic("__negV", GetInsPtr(VNeg)); break;
        case JoaatCasedConst("__and"):			AddAsmIntrinsic("__and", GetInsPtr(And)); break;
        case JoaatCasedConst("__or"):			AddAsmIntrinsic("__or", GetInsPtr(Or)); break;
        case JoaatCasedConst("__xor"):			AddAsmIntrinsic("__xor", GetInsPtr(Xor)); break;
        case JoaatCasedConst("__iToF"):			AddAsmIntrinsic("__iToF", GetInsPtr(ItoF)); break;
        case JoaatCasedConst("__fToI"):			AddAsmIntrinsic("__fToI", GetInsPtr(FtoI)); break;
        case JoaatCasedConst("__fToV"):			AddAsmIntrinsic("__fToV", GetInsPtr(FtoV)); break;
        case JoaatCasedConst("__push2"):
        {
            ChkHashCol("__push2");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult apCount;
                if (argArray[0]->EvaluateAsInt(apCount, context))
                {
                    AddInstruction(PushInt, apCount.Val.getInt().getSExtValue());
                    if (argArray[1]->EvaluateAsInt(apCount, context))
                    {
                        AddInstruction(PushInt, apCount.Val.getInt().getSExtValue());
                        return true;
                    } EvalFailed
                } EvalFailed
            }  BadIntrin
        } break;
        case JoaatCasedConst("__push3"):
        {
            ChkHashCol("__push3");
            if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult apCount;
                if (argArray[0]->EvaluateAsInt(apCount, context))
                {
                    AddInstruction(PushInt, apCount.Val.getInt().getSExtValue());
                    if (argArray[1]->EvaluateAsInt(apCount, context))
                    {
                        AddInstruction(PushInt, apCount.Val.getInt().getSExtValue());
                        if (argArray[2]->EvaluateAsInt(apCount, context))
                        {
                            AddInstruction(PushInt, apCount.Val.getInt().getSExtValue());
                            return true;
                        } EvalFailed
                    } EvalFailed
                } EvalFailed
            } BadIntrin
        } break;
        case JoaatCasedConst("__push"):			AddAsmIntrinsic32("__push", GetInsPtr(PushInt)); break;
        case JoaatCasedConst("__pushF"):
        {
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isRealFloatingType())
            {
                Expr::EvalResult ER;
                if (argArray[0]->EvaluateAsRValue(ER, context))
                {
                    AddInstruction(PushFloat, ER.Val.getFloat().convertToFloat());
                    return true;
                } EvalFailed
            } BadIntrin
        } break;
        case JoaatCasedConst("__dup"):			AddAsmIntrinsic("__dup", GetInsPtr(Dup)); break;
        case JoaatCasedConst("__drop"):			AddAsmIntrinsic("__drop", GetInsPtr(Drop)); break;
        case JoaatCasedConst("__callNative"):
        {
            //TODO: add hash translation to pc
            ChkHashCol("__callNative");
            if (argCount == 3 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult apCount, apCount1, apCount2;
                if (argArray[0]->EvaluateAsInt(apCount, context))
                {
                    if (argArray[1]->EvaluateAsInt(apCount1, context))
                    {
                        if (argArray[2]->EvaluateAsInt(apCount2, context))
                        {
                            AddInstruction(Native, apCount.Val.getInt().getSExtValue() & 0xFFFFFFFF, apCount1.Val.getInt().getSExtValue(), apCount2.Val.getInt().getSExtValue());
                            return true;
                        } EvalFailed
                    } EvalFailed
                } EvalFailed
            }  BadIntrin
        } break;
        case JoaatCasedConst("__callNativePc"):
        {
            ChkHashCol("__callNativePc");
            if (argCount == 4 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType() && argArray[2]->getType()->isIntegerType() && argArray[3]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult apCount, apCount1, apCount2, apCount3;
                if (argArray[0]->EvaluateAsInt(apCount, context))
                {
                    if (argArray[1]->EvaluateAsInt(apCount1, context))
                    {
                        if (argArray[2]->EvaluateAsInt(apCount2, context))
                        {
                            if (argArray[3]->EvaluateAsInt(apCount2, context))
                            {
                                AddInstruction(Native, (apCount.Val.getInt().getSExtValue() << 32) | apCount1.Val.getInt().getSExtValue(), apCount2.Val.getInt().getSExtValue(), apCount3.Val.getInt().getSExtValue());
                                return true;
                            } EvalFailed
                        } EvalFailed
                    } EvalFailed
                } EvalFailed
            }  BadIntrin
        } break;
        case JoaatCasedConst("__return"):
        {
            ChkHashCol("__return");
            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isIntegerType() && argArray[1]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult apCount, apCount1;
                if (argArray[0]->EvaluateAsInt(apCount, context) && apCount.Val.getInt().getSExtValue() <= 255)
                {
                    if (argArray[1]->EvaluateAsInt(apCount1, context) && apCount.Val.getInt().getSExtValue() <= 255)
                    {
                        AddInstruction(Return, apCount.Val.getInt().getSExtValue(), apCount1.Val.getInt().getSExtValue());
                        return true;
                    } EvalFailed
                } EvalFailed
            }  BadIntrin
        } break;
        case JoaatCasedConst("__pGet"):			AddAsmIntrinsic("__pGet", GetInsPtr(PGet)); break;
        case JoaatCasedConst("__pSet"):			AddAsmIntrinsic("__pSet", GetInsPtr(PSet)); break;
        case JoaatCasedConst("__pPeekSet"):		AddAsmIntrinsic("__pPeekSet", GetInsPtr(PeekSet)); break;
        case JoaatCasedConst("__toStack"):		AddAsmIntrinsic("__toStack", GetInsPtr(ToStack)); break;
        case JoaatCasedConst("__fromStack"):	AddAsmIntrinsic("__fromStack", GetInsPtr(FromStack)); break;
        case JoaatCasedConst("__getArrayP"):	AddAsmIntrinsic16("__getArrayP", GetInsPtr(GetArrayP)); break;
        case JoaatCasedConst("__getArray"):		AddAsmIntrinsic16("__getArray", GetInsPtr(GetArray)); break;
        case JoaatCasedConst("__setArray"):		AddAsmIntrinsic16("__setArray", GetInsPtr(SetArray)); break;
        case JoaatCasedConst("__getFrameP"):	AddAsmIntrinsic16("__getFrameP", GetInsPtr(GetFrameP)); break;
        case JoaatCasedConst("__getNamedFrameP"):AddAsmIntrinsicLocal("__getNamedFrameP", GetInsPtr(GetFrameP)); break;
        case JoaatCasedConst("__getFrame"):		AddAsmIntrinsic16("__getFrame", GetInsPtr(GetFrame)); break;
        case JoaatCasedConst("__getNamedFrame"):AddAsmIntrinsicLocal("__getNamedFrame", GetInsPtr(GetFrame)); break;
        case JoaatCasedConst("__setFrame"):		AddAsmIntrinsic16("__setFrame", GetInsPtr(SetFrame)); break;
        case JoaatCasedConst("__setNamedFrame"):AddAsmIntrinsicLocal("__setNamedFrame", GetInsPtr(SetFrame)); break;
        case JoaatCasedConst("__getStaticP"):	AddAsmIntrinsic16("__getStaticP", GetInsPtr(GetStaticPRaw)); break;
        case JoaatCasedConst("__getNamedStaticP"):AddAsmIntrinsicStatic("__getNamedStaticP", GetInsPtr(GetStaticP)); break;
        case JoaatCasedConst("__getStatic"):	AddAsmIntrinsic16("__getStatic", GetInsPtr(GetStaticRaw)); break;
        case JoaatCasedConst("__getNamedStatic"):AddAsmIntrinsicStatic("__getNamedStatic", GetInsPtr(GetStatic)); break;
        case JoaatCasedConst("__setStatic"):	AddAsmIntrinsic16("__setStatic", GetInsPtr(SetStaticRaw)); break;
        case JoaatCasedConst("__setNamedStatic"):AddAsmIntrinsicStatic("__setNamedStatic", GetInsPtr(SetStatic)); break;
        case JoaatCasedConst("__addImm"):		AddAsmIntrinsic32("__addImm", GetInsPtr(AddImm)); break;
        case JoaatCasedConst("__multImm"):		AddAsmIntrinsic32("__multImm", GetInsPtr(MultImm)); break;
        case JoaatCasedConst("__getImmP"):		AddAsmIntrinsic16("__getImmP", GetInsPtr(GetImmP)); break;
        case JoaatCasedConst("__getImm"):		AddAsmIntrinsic16("__getImm", GetInsPtr(GetImm)); break;
        case JoaatCasedConst("__setImm"):		AddAsmIntrinsic16("__setImm", GetInsPtr(SetImm)); break;
        case JoaatCasedConst("__getGlobalP"):	AddAsmIntrinsic32("__getGlobalP", GetInsPtr(GetGlobalP)); break;
        case JoaatCasedConst("__getGlobal"):	AddAsmIntrinsic32("__getGlobal", GetInsPtr(GetGlobal)); break;
        case JoaatCasedConst("__setGlobal"):	AddAsmIntrinsic32("__setGlobal", GetInsPtr(SetGlobal)); break;
        case JoaatCasedConst("__switch"):
        {
            ChkHashCol("__switch");
            if (argCount >= 2 && callee->getReturnType()->isVoidType())
            {
                if (argCount >= 2 && argCount % 2 == 0)
                {
                    clang::Expr::EvalResult apCount;
                    string str;
                    bool isSwitchOver255 = argCount >= 255 * 2;
                    int SwitchCount = 1, tempSwitchIndex = 0;
                    if (isSwitchOver255)
                    {
                        LocalVariables.addLevel();
                        tempSwitchIndex = LocalVariables.addDecl("Switch Temp", 1);
                        AddInstruction(Dup);
                        AddInstructionComment(SetFrame, "Switch temporary variable", tempSwitchIndex);
                        AddInstruction(Switch);
                    }
                    else
                    {
                        AddInstruction(Switch);
                    }

                    for (int i = 0; i < argCount; i += 2)
                    {
                        if (i >= (255 * 2) * SwitchCount)
                        {
                            AddInstructionComment(GetFrame, "Switch temporary variable", tempSwitchIndex);
                            AddInstruction(Switch);
                            SwitchCount++;
                        }
                        if (argArray[i]->EvaluateAsInt(apCount, context))
                        {
                            if (EvaluateAsString(argArray[i + 1], str))
                            {
                                scriptData.getCurrentFunction()->addSwitchCase(apCount.Val.getInt().getSExtValue(), str + scriptData.getInlineJumpLabelAppend());

                            } EvalFailedStr
                        } EvalFailed
                    }
                    if (isSwitchOver255)
                        LocalVariables.removeLevel();
                    return true;
                } BadIntrinArgC
            } BadIntrin
        } break;
        case JoaatCasedConst("__jump"):			AddAsmIntrinsicJump("__jump", GetInsPtr(Jump)); break;
        case JoaatCasedConst("__jumpFalse"):	AddAsmIntrinsicJump("__jumpFalse", GetInsPtr(JumpFalse)); break;
        case JoaatCasedConst("__jumpNE"):		AddAsmIntrinsicJump("__jumpNE", GetInsPtr(JumpNE)); break;
        case JoaatCasedConst("__jumpEQ"):		AddAsmIntrinsicJump("__jumpEQ", GetInsPtr(JumpEQ)); break;
        case JoaatCasedConst("__jumpLE"):		AddAsmIntrinsicJump("__jumpLE", GetInsPtr(JumpLE)); break;
        case JoaatCasedConst("__jumpLT"):		AddAsmIntrinsicJump("__jumpLT", GetInsPtr(JumpLT)); break;
        case JoaatCasedConst("__jumpGE"):		AddAsmIntrinsicJump("__jumpGE", GetInsPtr(JumpGE)); break;
        case JoaatCasedConst("__jumpGT"):		AddAsmIntrinsicJump("__jumpGT", GetInsPtr(JumpGT)); break;
        case JoaatCasedConst("__call"):
        {
            ChkHashCol("__call");
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType())
            {
                string str;
                if (EvaluateAsString(argArray[0], str))
                {
                    if (FunctionData* func = scriptData.getFunctionFromName(str))//TODO:  check if this works with static functions
                    {
                        AddInstruction(Call, func);
                        return true;
                    }
                    else
                        Throw("__call: Function \"" + str + "\" not found", TheRewriter, call->getExprLoc());
                    return true;
                } EvalFailedStr
            } BadIntrin
        } break;
        case JoaatCasedConst("__pushString"):
        {
            ChkHashCol("__pushString");
            if (argCount == 1 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType())
            {
                string str;
                if (EvaluateAsString(argArray[0], str))
                {
                    AddInstruction(PushString, str);
                    return true;
                } EvalFailedStr
            } BadIntrin
        } break;
        case JoaatCasedConst("__getHash"):		AddAsmIntrinsic("__getHash", GetInsPtr(GetHash)); break;
        case JoaatCasedConst("__strCopy"):		AddAsmIntrinsic8("__strCopy", GetInsPtr(StrCopy)); break;
        case JoaatCasedConst("__iToS"):			AddAsmIntrinsic8("__iToS", GetInsPtr(ItoS)); break;
        case JoaatCasedConst("__strAdd"):		AddAsmIntrinsic8("__strAdd", GetInsPtr(StrAdd)); break;
        case JoaatCasedConst("__strAddI"):		AddAsmIntrinsic8("__strAddI", GetInsPtr(StrAddI)); break;
        case JoaatCasedConst("__memCopy"):		AddAsmIntrinsic("__memCopy", GetInsPtr(MemCopy)); break;
        case JoaatCasedConst("__pCall"):		AddAsmIntrinsic("__pCall", GetInsPtr(PCall)); break;
        case JoaatCasedConst("__ptrToStack"):
        {
            ChkHashCol("__ptrToStack");

            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult result;
                if (argArray[1]->EvaluateAsInt(result, context) && result.Val.getInt().getSExtValue() == 1)
                {
                    parseExpression(argArray[0], false, true);
                    AddInstruction(PGet);
                }
                else
                {
                    parseExpression(argArray[1], false, true);
                    parseExpression(argArray[0], false, true);
                    AddInstruction(ToStack);
                }
                return true;
            }
            else
            {
                Throw("__ptrToStack must have signature \"extern __unsafeIntrinsic void __ptrToStack(const void* address, int count);\"", TheRewriter, callee->getSourceRange());
            }
        } break;
        case JoaatCasedConst("__ptrFromStack"):
        {
            ChkHashCol("__ptrFromStack");

            if (argCount == 2 && callee->getReturnType()->isVoidType() && argArray[0]->getType()->isPointerType() && argArray[1]->getType()->isIntegerType())
            {
                clang::Expr::EvalResult result;
                if (argArray[1]->EvaluateAsInt(result, context) && result.Val.getInt().getSExtValue() == 1)
                {
                    parseExpression(argArray[0], false, true);
                    AddInstruction(PSet);
                }
                else
                {
                    parseExpression(argArray[1], false, true);
                    parseExpression(argArray[0], false, true);
                    AddInstruction(FromStack);
                }
                return true;
            }
            else
            {
                Throw("__ptrFromStack must have signature \"extern __unsafeIntrinsic void __ptrFromStack(const void* address, int count);\"", TheRewriter, callee->getSourceRange());
            }
        } break;

#pragma endregion 

        default:
        _IntrinsicNotFound:
            Throw("No intrinsic function found named " + funcName, TheRewriter, callee->getLocation());
        }

#undef ChkHashCol
#undef BadIntrin
#undef EvalFailed
#undef EvalFailedStr
#undef BadIntrinArgC
        return ret;
    }

    bool ASTVisitorLocal::findAnyLabel(const Stmt* stmt)
    {
        for (const auto& childStmt : stmt->children())
        {
            if (isa<LabelStmt>(childStmt))
                return true;
            return findAnyLabel(childStmt);
        }
        return false;
    }
    void ASTVisitorLocal::parseJumpFalse(const Expr* conditional, const string& jumpFalseLoc)
    {
        const BinaryOperator* binaryOp;
        if ((binaryOp = dyn_cast<BinaryOperator>(conditional->IgnoreParens())) && binaryOp->getOpcode() == BO_LAnd)
        {
            parseJumpFalse(binaryOp->getLHS(), jumpFalseLoc);
            parseJumpFalse(binaryOp->getRHS(), jumpFalseLoc);
        }
        else
        {
            parseExpression(conditional, false, true);
            AddJumpInlineCheckStr(JumpFalse, jumpFalseLoc);
        }
    }

    void ASTVisitorLocal::parseCondition(const Expr* conditional, const string& trueLoc, const string& falseLoc)
    {
        const BinaryOperator* binaryOp;
        static int counter = 0;
        string label = "__pcf_" + to_string(counter++);
        if ((binaryOp = dyn_cast<BinaryOperator>(conditional->IgnoreParens())))
        {
            switch (binaryOp->getOpcode())
            {
            case BO_LAnd:
                //parseJumpFalse(binaryOp->getLHS(), falseLoc);
                //parseJumpFalse(binaryOp->getRHS(), falseLoc);
                parseCondition(binaryOp->getLHS(), label, falseLoc);
                AddJumpInlineCheckStr(Label, label);
                parseCondition(binaryOp->getRHS(), trueLoc, falseLoc);
                return;
            case BO_LOr:
                //parseJumpTrue(binaryOp->getLHS(), trueLoc);
                parseCondition2(binaryOp->getLHS(), trueLoc, label);
                AddJumpInlineCheckStr(Label, label);
                parseCondition(binaryOp->getRHS(), trueLoc, falseLoc);
                return;
            case BO_Comma:
                parseExpression(binaryOp->getLHS());
                parseCondition(binaryOp->getRHS(), trueLoc, falseLoc);
                return;
            default:
                parseExpression(conditional, false, true);
                if (conditional->getType()->isAnyComplexType())
                {
                    ComplexToBoolean(conditional->getType()->isComplexType());
                }
                else if (conditional->getType()->isRealFloatingType())
                {
                    AddInstruction(PushFloat, 0.0);
                    AddInstruction(FCmpNe);
                }
                AddJumpInlineCheckStr(JumpFalse, falseLoc);
                return;

            }
        }
        else
        {
            parseExpression(conditional, false, true);
            if (conditional->getType()->isAnyComplexType())
            {
                ComplexToBoolean(conditional->getType()->isComplexType());
            }
            else if (conditional->getType()->isRealFloatingType())
            {
                AddInstruction(PushFloat, 0.0);
                AddInstruction(FCmpNe);
            }
            AddJumpInlineCheckStr(JumpFalse, falseLoc);
        }
    }
    void ASTVisitorLocal::parseCondition2(const Expr* conditional, const string& trueLoc, const string& falseLoc)
    {
        const BinaryOperator* binaryOp;
        static int counter = 0;
        string label = "__pct_" + to_string(counter++);
        if ((binaryOp = dyn_cast<BinaryOperator>(conditional->IgnoreParens())))
        {
            switch (binaryOp->getOpcode())
            {
            case BO_LAnd:
                //parseJumpFalse(binaryOp->getLHS(), falseLoc);
                parseCondition(binaryOp->getLHS(), label, falseLoc);
                AddJumpInlineCheckStr(Label, label);
                parseCondition2(binaryOp->getRHS(), trueLoc, falseLoc);
                return;
            case BO_LOr:
                //parseJumpTrue(binaryOp->getLHS(), trueLoc);
                parseCondition2(binaryOp->getLHS(), trueLoc, label);
                AddJumpInlineCheckStr(Label, label);
                parseCondition2(binaryOp->getRHS(), trueLoc, falseLoc);
                return;
            case BO_Comma:
                parseExpression(binaryOp->getLHS());
                parseCondition2(binaryOp->getRHS(), trueLoc, falseLoc);
                return;
            default:
                parseExpression(conditional, false, true);
                if (conditional->getType()->isAnyComplexType())
                {
                    ComplexToBoolean(conditional->getType()->isComplexType());
                }
                else if (conditional->getType()->isRealFloatingType())
                {
                    AddInstruction(PushFloat, 0.0);
                    AddInstruction(FCmpNe);
                }
                AddJumpInlineCheckStr(JumpTrue, trueLoc);
                return;

            }
        }
        else
        {
            parseExpression(conditional, false, true);
            if (conditional->getType()->isAnyComplexType())
            {
                ComplexToBoolean(conditional->getType()->isComplexType());
            }
            else if (conditional->getType()->isRealFloatingType())
            {
                AddInstruction(PushFloat, 0.0);
                AddInstruction(FCmpNe);
            }
            AddJumpInlineCheckStr(JumpTrue, trueLoc);
        }
    }
    void ASTVisitorLocal::parseJumpTrue(const Expr* conditional, const string& jumpTrueLoc)
    {
        const BinaryOperator* binaryOp;
        if ((binaryOp = dyn_cast<BinaryOperator>(conditional->IgnoreParens())) && binaryOp->getOpcode() == BO_LOr)
        {
            parseJumpTrue(binaryOp->getLHS(), jumpTrueLoc);
            parseJumpTrue(binaryOp->getRHS(), jumpTrueLoc);
        }
        else
        {
            parseExpression(conditional, false, true);
            AddJumpInlineCheckStr(JumpTrue, jumpTrueLoc);
        }
    }
    bool ASTVisitorLocal::parseStatement(Stmt* s, const string& breakLoc, const string& continueLoc)
    {
        if (isa<CompoundStmt>(s))
        {
            CompoundStmt* cSt = cast<CompoundStmt>(s);
            LocalVariables.addLevel();
            for (auto* CS : cSt->body())
            {
                parseStatement(cast<Stmt>(CS), breakLoc, continueLoc);
            }
            LocalVariables.removeLevel();
        }
        else if (isa<DeclStmt>(s))
        {
            DeclStmt* decl = cast<DeclStmt>(s);
            handleDecl(decl);
        }
        else if (isa<IfStmt>(s))
        {
            static int ifCounter = 0;
            const string currentCounter = to_string(ifCounter++);//prevents issues with nested if statements
            IfStmt* IfStatement = cast<IfStmt>(s);
            Expr* conditional = IfStatement->getCond();
            Stmt* Then = IfStatement->getThen();
            Stmt* Else = IfStatement->getElse();
            bool rev = false;
            if (Else && (isa<NullStmt>(Else) || (isa<CompoundStmt>(Else) && cast<CompoundStmt>(Else)->size() == 0)))
            {
                Else = NULL;
            }
            if (isa<NullStmt>(Then) || (isa <CompoundStmt>(Then) && cast<CompoundStmt>(Then)->size() == 0))
            {
                if (Else)
                {
                    rev = true;
                    Then = Else;
                    Else = NULL;
                }
                else
                {
                    if (conditional->HasSideEffects(context, true))
                    {
                        parseExpression(conditional);//parse then drop
                    }
                    return true;
                }
            }
            string IfLocEnd = "__if_end_" + currentCounter;

            Expr::EvalResult eResult;
            bool bValue = false, ignoreCondition = false;
            if (conditional->EvaluateAsRValue(eResult, context) && eResult.Val.isInt())
            {
                bValue = eResult.Val.getInt().getBoolValue();
                if (!isa<IntegerLiteral>(conditional->IgnoreParenCasts()))
                    Warn("if condition always evaluates to " + (bValue ? string("true") : string("false")), TheRewriter, conditional->getSourceRange());
                ignoreCondition = Option_OptimizationLevel > OptimisationLevel::OL_None && !conditional->HasSideEffects(context, true);
            }
            if (ignoreCondition)
            {
                if (bValue ^ rev)
                {
                    LocalVariables.addLevel();
                    parseStatement(Then, breakLoc, continueLoc);
                    LocalVariables.removeLevel();
                    if (Else && !findAnyLabel(Else))
                    {
                        Else = NULL;// if there are no labels in the else just mark it as null as the code will never be executed
                    }
                    bool ifEndRet = scriptData.getCurrentFunction()->endsWithReturn() || (scriptData.getInlineCount() && scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()));
                    if (Else)
                    {
                        AddJumpInlineCheckConditionallyStr(!ifEndRet, Jump, IfLocEnd);
                        LocalVariables.addLevel();
                        parseStatement(Else, breakLoc, continueLoc);
                        LocalVariables.removeLevel();
                        AddJumpInlineCheckConditionallyStr(!ifEndRet, Label, IfLocEnd);
                    }
                }
                else
                {
                    if (findAnyLabel(Then))
                    {
                        if (Else)
                        {
                            AddJumpInlineCheckStr(Jump, "__if_else_" + currentCounter);
                            LocalVariables.addLevel();
                            parseStatement(Then, breakLoc, continueLoc);
                            LocalVariables.removeLevel();


                            bool ifEndRet = scriptData.getCurrentFunction()->endsWithReturn() || (scriptData.getInlineCount() && scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()));
                            if (Else)
                            {
                                AddJumpInlineCheckConditionallyStr(!ifEndRet, Jump, IfLocEnd);

                                AddJumpInlineCheckStr(Label, "__if_else_" + currentCounter);
                                LocalVariables.addLevel();
                                parseStatement(Else, breakLoc, continueLoc);
                                LocalVariables.removeLevel();
                            }
                            AddJumpInlineCheckConditionallyStr(!ifEndRet || !Else, Label, IfLocEnd);
                        }
                        else
                        {
                            AddJumpInlineCheckStr(Jump, IfLocEnd);
                            LocalVariables.addLevel();
                            parseStatement(Then, breakLoc, continueLoc);
                            LocalVariables.removeLevel();
                            AddJumpInlineCheckStr(Label, IfLocEnd);

                        }
                    }
                    else
                    {
                        //ignore the then case
                        if (Else)
                        {
                            LocalVariables.addLevel();
                            parseStatement(Else, breakLoc, continueLoc);
                            LocalVariables.removeLevel();
                        }
                    }
                }
            }
            else
            {
                if (rev)
                {
                    parseCondition2(conditional, IfLocEnd, "__if_else_" + currentCounter);
                    AddJumpInlineCheckStr(Label, "__if_else_" + currentCounter);
                }
                else
                {
                    parseCondition(conditional, "__if_then_" + currentCounter, Else ? "__if_else_" + currentCounter : IfLocEnd);
                    AddJumpInlineCheckStr(Label, "__if_then_" + currentCounter);
                }
                LocalVariables.addLevel();
                parseStatement(Then, breakLoc, continueLoc);
                LocalVariables.removeLevel();
                bool ifEndRet = scriptData.getCurrentFunction()->endsWithReturn() || (scriptData.getInlineCount() && scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()));
                AddJumpInlineCheckConditionallyStr(!ifEndRet && Else, Jump, IfLocEnd);//if the last instruction is a return, no point adding a jump

                if (Else)
                {
                    AddJumpInlineCheckStr(Label, "__if_else_" + currentCounter);
                    LocalVariables.addLevel();
                    parseStatement(Else, breakLoc, continueLoc);
                    LocalVariables.removeLevel();
                }

                AddJumpInlineCheckConditionallyStr(!ifEndRet || !Else, Label, IfLocEnd);

            }
        }
        else if (isa<WhileStmt>(s))
        {
            static int whileCounter = 0;
            const string currentCounter = to_string(whileCounter++);
            WhileStmt* whileStmt = cast<WhileStmt>(s);
            Expr* conditional = whileStmt->getCond();

            Stmt* body = whileStmt->getBody();
            LocalVariables.addLevel();

            Expr::EvalResult eResult;
            bool bValue = false, ignoreCondition = false;
            if (conditional->EvaluateAsRValue(eResult, context) && eResult.Val.isInt())
            {
                bValue = eResult.Val.getInt().getBoolValue();
                if (!isa<IntegerLiteral>(conditional->IgnoreParenCasts()))
                    Warn("While condition always evaluates to " + (bValue ? string("true") : string("false")), TheRewriter, conditional->getSourceRange());
                ignoreCondition = Option_OptimizationLevel > OptimisationLevel::OL_None && !conditional->HasSideEffects(context, true);
            }
            if (ignoreCondition)
            {
                if (bValue)
                {
                    AddJumpInlineCheckStr(Label, "__while_body_" + currentCounter);

                    parseStatement(body, "__while_end_" + currentCounter, "__while_body_" + currentCounter);

                    AddJumpInlineCheckStr(Jump, "__while_body_" + currentCounter);
                    AddJumpInlineCheckStr(Label, "__while_end_" + currentCounter);
                }
                else
                {
                    AddJumpInlineCheckStr(Label, "__while_body_" + currentCounter);
                    AddJumpInlineCheckStr(Jump, "__while_end_" + currentCounter);

                    parseStatement(body, "__while_end_" + currentCounter, "__while_body_" + currentCounter);

                    AddJumpInlineCheckStr(Label, "__while_end_" + currentCounter);
                }

            }
            else
            {
                parseCondition(conditional, "__while_body_" + currentCounter, "__while_end_" + currentCounter);
                AddJumpInlineCheckStr(Label, "__while_body_" + currentCounter);

                parseStatement(body, "__while_end_" + currentCounter, "__while_cond_" + currentCounter);

                AddJumpInlineCheckStr(Label, "__while_cond_" + currentCounter);

                parseCondition2(conditional, "__while_body_" + currentCounter, "__while_end_" + currentCounter);

                AddJumpInlineCheckStr(Label, "__while_end_" + currentCounter);
            }
            LocalVariables.removeLevel();
        }
        else if (isa<ForStmt>(s))
        {
            static int forCounter = 0;
            const string currentCounter = to_string(forCounter++);
            ForStmt* forStmt = cast<ForStmt>(s);
            Stmt* decl = forStmt->getInit();
            Expr* conditional = forStmt->getCond();
            Expr* increment = forStmt->getInc();
            Stmt* body = forStmt->getBody();
            LocalVariables.addLevel();
            if (decl)
            {
                parseStatement(decl, "", "");
            }

            if (conditional)
            {
                parseCondition(conditional, "__for_body_" + currentCounter, "__for_end_" + currentCounter);
            }
            AddJumpInlineCheckStr(Label, "__for_body_" + currentCounter);

            parseStatement(
                body,
                "__for_end_" + currentCounter,
                (increment || conditional ? "__for_continue_" : "__for_body_") + currentCounter);

            if (increment || conditional)
            {
                AddJumpInlineCheckStr(Label, "__for_continue_" + currentCounter);
            }

            if (increment)
                parseExpression(increment);

            if (conditional)
            {
                parseCondition2(conditional, "__for_body_" + currentCounter, "__for_end_" + currentCounter);
            }
            else
            {
                AddJumpInlineCheckStr(Jump, "__for_body_" + currentCounter);
            }

            AddJumpInlineCheckStr(Label, "__for_end_" + currentCounter);
            LocalVariables.removeLevel();


        }
        else if (isa<UnaryOperator>(s))
        {
            parseExpression(cast<const Expr>(s));
        }
        else if (isa<DoStmt>(s))
        {
            static int doCounter = 0;
            const string  currentCounter = to_string(doCounter++);
            DoStmt* doStmt = cast<DoStmt>(s);
            Expr* conditional = doStmt->getCond();

            Stmt* body = doStmt->getBody();
            LocalVariables.addLevel();

            AddJumpInlineCheckStr(Label, "__do_body_" + currentCounter);
            parseStatement(body, "__do_end_" + currentCounter, "__do_cond_" + currentCounter);

            AddJumpInlineCheckStr(Label, "__do_cond_" + currentCounter);

            Expr::EvalResult eResult;
            bool bValue = false, ignoreCondition = false;
            if (conditional->EvaluateAsRValue(eResult, context) && eResult.Val.isInt())
            {
                bValue = eResult.Val.getInt().getBoolValue();
                if (!isa<IntegerLiteral>(conditional->IgnoreParenCasts()))
                    Warn("do While condition always evaluates to " + (bValue ? string("true") : string("false")), TheRewriter, conditional->getSourceRange());
                ignoreCondition = Option_OptimizationLevel > OptimisationLevel::OL_None && !conditional->HasSideEffects(context, true);
            }
            if (ignoreCondition)
            {
                AddJumpInlineCheckConditionallyStr(bValue, Jump, "__do_body_" + currentCounter);
                //no need for else, just jump right out
            }
            else
            {
                parseCondition2(conditional, "__do_body_" + currentCounter, "__do_end_" + currentCounter);
            }

            AddJumpInlineCheckStr(Label, "__do_end_" + currentCounter);
            LocalVariables.removeLevel();

        }
        else if (isa<ReturnStmt>(s))
        {
            const ReturnStmt* ret = cast<const ReturnStmt>(s);
            const Expr* retVal = ret->getRetValue();
            if (retVal)
                parseExpression(retVal, false, true);

            if (!scriptData.getInlineCount())
            {
                int size = 0;
                if (ret->getRetValue())
                {
                    QualType type = ret->getRetValue()->getType();
                    size = context.getTypeInfoDataSizeInChars(type).Width.getQuantity();
                }

                int32_t paramSize = 0;
                for (uint32_t i = 0; i < currFunction->getNumParams(); i++)
                {
                    paramSize += getSizeFromBytes(getSizeOfType(currFunction->getParamDecl(i)->getType().getTypePtr()));
                }
                AddInstruction(Return);
            }
            else
            {
                AddInstructionComment(Jump, "Inline return", scriptData.getInlineJumpLabelAppend());
            }

        }
        else if (isa<Expr>(s))
        {
            parseExpression(cast<const Expr>(s));
        }
        else if (isa<BreakStmt>(s))
        {
            AddJumpInlineCheckStrComment(Jump, "brkstmt jmp", breakLoc);
        }
        else if (isa<NullStmt>(s))
        {
        }
        else if (isa<ContinueStmt>(s))
        {
            AddJumpInlineCheckStrComment(Jump, "contstmt jmp", continueLoc);
        }
        else if (isa<DefaultStmt>(s))
        {
            Throw("Default case should be handled");
            /*DefaultStmt *caseD = cast<DefaultStmt>(s);
            AddInstruction(Label, to_string(caseD->getLocStart().getRawEncoding()) + scriptData.getInlineJumpLabelAppend());
            LocalVariables.addLevel();

            if (caseD->getSubStmt())
            parseStatement(caseD->getSubStmt(), breakLoc, continueLoc);
            LocalVariables.removeLevel();*/
        }
        else if (isa<CaseStmt>(s))
        {
            Throw("Case Statement should be handled");
            /*CaseStmt *caseS = cast<CaseStmt>(s);
            AddInstruction(Label, to_string(caseS->getLocStart().getRawEncoding()) + scriptData.getInlineJumpLabelAppend());

            LocalVariables.addLevel();
            if (caseS->getRHS())
            parseExpression(caseS->getRHS());

            if (caseS->getSubStmt())
            parseStatement(caseS->getSubStmt(), breakLoc, continueLoc);
            LocalVariables.removeLevel();*/
        }
        else if (isa<SwitchStmt>(s))
        {
            static int counter = 0;
            string label = "__sw_" + to_string(counter++) + "_";
            string endLabel = label + "end";
            SwitchStmt* switchStmt = cast<SwitchStmt>(s);
            parseExpression(switchStmt->getCond(), false, true);

            struct switchCaseLocPair
            {
                int val;
                string loc;
            };
            vector<switchCaseLocPair> caseLabels;
            int labelCount = 0;
            unordered_map<SwitchCase*, pair<string, SwitchCase*>> caseMap;

            string defaultLoc = "";

            auto addLabel = [&](SwitchCase* sCase, const string& loc)
            {
                if (isa<CaseStmt>(sCase))
                {
                    CaseStmt* caseS = cast<CaseStmt>(sCase);

                    clang::Expr::EvalResult result;
                    if (caseS->getLHS()->EvaluateAsInt(result, context))
                    {
                        int val;
                        if (!CheckExprForSizeOf(caseS->getLHS()->IgnoreParens(), &val))
                        {
                            val = result.Val.getInt().getSExtValue();
                        }
                        if (caseS->getRHS())
                        {
                            if (caseS->getRHS()->EvaluateAsInt(result, context))
                            {
                                int valR;
                                if (!CheckExprForSizeOf(caseS->getLHS()->IgnoreParens(), &valR))
                                {
                                    valR = result.Val.getInt().getSExtValue();
                                }
                                if (val > valR)
                                {
                                    Throw("GNU switch range min value is greater than max value", TheRewriter, SourceRange(caseS->getLHS()->getBeginLoc(), caseS->getRHS()->getEndLoc()));
                                }
                                for (int i = val; i <= valR; i++)
                                {
                                    caseLabels.push_back({ i, loc });
                                }
                            }
                        }
                        else
                        {
                            caseLabels.push_back({ val, loc });
                        }
                    }
                    else Throw("Unsupported case statement \"" + string(caseS->getLHS()->getStmtClassName()) + "\"", TheRewriter, caseS->getLHS()->getSourceRange());

                }
                else if (isa<DefaultStmt>(sCase))
                {
                    if (defaultLoc.size() != 0)
                    {
                        Throw("Multiple default statements found in switch", TheRewriter, sCase->getSourceRange());
                    }
                    defaultLoc = loc;
                }
                return;
            };
            for (auto stmt : switchStmt->getBody()->children())
            {
                if (stmt && isa<SwitchCase>(stmt))
                {
                    string caseLoc = label + (isa<DefaultStmt>(stmt) ? "def" : to_string(labelCount++)) + scriptData.getInlineJumpLabelAppend();
                    auto sCase = cast<SwitchCase>(stmt);
                    SwitchCase* caseCode = sCase;
                    addLabel(sCase, caseLoc);
                    while (isa<SwitchCase>(caseCode->getSubStmt()))
                    {
                        caseCode = cast<SwitchCase>(caseCode->getSubStmt());
                        addLabel(caseCode, caseLoc);
                    }
                    auto it = caseMap.find(sCase);
                    if (it == caseMap.end())
                    {
                        caseMap.insert({ sCase,{ caseLoc, caseCode } });
                    }
                    else
                    {
                        Throw("Error");
                    }

                }
            }

            int sSize = caseLabels.size();
            if (!sSize)
            {
                Warn("Switch statement contains no cases", TheRewriter, switchStmt->getSourceRange());
                AddInstruction(Switch);
            }
            else if (sSize > 255)
            {
                //multiple switch statements needed
                LocalVariables.addLevel();
                int index = LocalVariables.addDecl("Switch Temp", 1);
                AddInstruction(Dup);
                AddInstructionComment(SetFrame, "Switch temporary variable", index);
                AddInstruction(Switch);
                int i = 0;
                for (auto sCase : caseLabels)
                {
                    if (i++ == 255)
                    {
                        i = 1;
                        AddInstructionComment(GetFrame, "Switch temporary variable", index);
                        AddInstruction(Switch);
                    }
                    scriptData.getCurrentFunction()->addSwitchCase(sCase.val, sCase.loc);
                }
                LocalVariables.removeLevel();
            }
            else
            {
                AddInstruction(Switch);
                for (auto sCase : caseLabels)
                {
                    scriptData.getCurrentFunction()->addSwitchCase(sCase.val, sCase.loc);
                }
            }


            if (defaultLoc.size())
            {
                scriptData.getCurrentFunction()->setSwitchDefaultCaseLoc(defaultLoc);
            }
            else
            {
                scriptData.getCurrentFunction()->setSwitchDefaultCaseLoc(endLabel + scriptData.getInlineJumpLabelAppend());
            }
            LocalVariables.addLevel();
            for (auto stmt : switchStmt->getBody()->children())
            {
                if (stmt)
                {
                    if (isa<SwitchCase>(stmt))
                    {
                        auto sCase = cast<SwitchCase>(stmt);
                        auto it = caseMap.find(sCase);
                        if (it != caseMap.end())
                        {
                            AddInstruction(Label, it->second.first);
                            parseStatement(it->second.second->getSubStmt(), endLabel, continueLoc);
                        }
                        else
                        {
                            Throw("Error");
                        }


                    }
                    else
                    {
                        parseStatement(stmt, endLabel, continueLoc);
                    }
                }
            }
            LocalVariables.removeLevel();

            AddJumpInlineCheckStr(Label, endLabel);
        }
        else if (isa<GotoStmt>(s))
        {
            GotoStmt* gotoStmt = cast<GotoStmt>(s);
            AddJumpInlineCheckStr(Jump, gotoStmt->getLabel()->getNameAsString());
        }
        else if (isa<LabelStmt>(s))
        {
            LabelStmt* labelStmt = cast<LabelStmt>(s);
            AddJumpInlineCheckStr(Label, string(labelStmt->getName()));
            parseStatement(labelStmt->getSubStmt(), breakLoc, continueLoc);
        }
        else if (isa<GCCAsmStmt>(s))
        {
            GCCAsmStmt* asmstmt = cast<GCCAsmStmt>(s);
            Throw("GCCAsmStmt isnt supported", TheRewriter, s->getSourceRange());//throw an error as the new method of compiling wont support this
            if (scriptData.getInlineCount())
            {
                Warn("Using a __asm__ statement in an inlined function may lead to undesireable effects\r\nConsider marking the function as __attribute__((__noinline__))", TheRewriter, asmstmt->getSourceRange());
            }
        }
        else if (isa<IndirectGotoStmt>(s))
        {
            auto indirectGoto = cast<IndirectGotoStmt>(s);
            parseExpression(indirectGoto->getTarget(), false, true);
            AddInstruction(GoToStack);
        }
        else
            Throw("Undefined statement \"" + string(s->getStmtClassName()) + "\"", TheRewriter, s->getBeginLoc());

        return true;
    }

    /// <summary>
    /// Parses the expression.
    /// </summary>
    /// <param name="e">The e.</param>
    /// <param name="isAddr">if set to <c>true</c> [is addr].</param>
    /// <param name="isLtoRValue">if set to <c>true</c> [is lto r value].</param>
    /// <param name="printVTable">if set to <c>true</c> [print v table].</param>
    /// <param name="isAssign">if set to <c>true</c> [is assign].</param>
    /// <returns></returns>
    int ASTVisitorLocal::parseExpression(const Expr* e, bool isAddr, bool isLtoRValue, bool printVTable, bool isAssign, bool isArrToPtrDecay)
    {
        Expr::EvalResult result;
        if (!isAddr && e->EvaluateAsRValue(result, context) && !result.HasSideEffects)
        {
            if (result.Val.isInt())
            {
                int64_t resValue = result.Val.getInt().getSExtValue();
                if (!isLtoRValue)
                    return -1;
                int val;
                if (CheckExprForSizeOf(e->IgnoreParens(), &val))
                {
                    AddInstruction(PushInt, val);
                }
                else
                {

                    if (doesInt64FitIntoInt32(resValue))
                    {
                        if (stackWidth == 8)
                            AddInstruction(PushInt64, resValue);
                        else
                        {
                            string value = to_string(resValue);
                            Warn("Integer overflow. Value: " + value + " is out of bounds of (-2,147,483,648 to 2,147,483,647). Changed value to " + to_string((int32_t)resValue), TheRewriter, e->getExprLoc(), e->getExprLoc().getLocWithOffset(value.length() - 1));

                        }
                    }
                    else
                    {
                        if (e->getType()->isBooleanType() && (int32_t)resValue == -1)
                            resValue = 1;

                        AddInstruction(PushInt, (int32_t)resValue);
                    }

                }
                return -1;
            }
            else if (result.Val.isFloat())
            {
                if (!isLtoRValue)
                    return -1;
                AddInstruction(PushFloat, extractAPFloat(result.Val.getFloat()));
                return -1;
            }
            else if (result.Val.isComplexFloat())
            {
                if (!isLtoRValue)
                    return -1;
                AddInstruction(PushFloat, extractAPFloat(result.Val.getComplexFloatReal()));
                AddInstruction(PushFloat, extractAPFloat(result.Val.getComplexFloatImag()));
                return -1;
            }
            else if (result.Val.isComplexInt())
            {
                if (!isLtoRValue)
                    return -1;
                AddInstruction(PushInt, result.Val.getComplexIntReal().getSExtValue());
                AddInstruction(PushInt, result.Val.getComplexIntImag().getSExtValue());
                return -1;
            }
        }

        if (isa<CompoundLiteralExpr>(e))
        {
            const CompoundLiteralExpr* cLit = cast<const CompoundLiteralExpr>(e);
            parseExpression(cLit->getInitializer(), isAddr, isLtoRValue);
            if (isArrToPtrDecay && isLtoRValue)
            {
                int size = getSizeFromBytes(getSizeOfType(e->getType().getTypePtr()));
                int index = LocalVariables.addDecl("", size);
                if (size > 1)
                {
                    AddInstructionComment(PushInt, "Type Size (compound decl)", size);
                    AddInstruction(GetFrameP, index);
                    AddInstruction(FromStack);
                    AddInstructionComment(GetFrameP, "compound literal ptr decay", index);
                }
                else
                {
                    AddInstruction(SetFrame, index);
                    AddInstructionComment(GetFrameP, "compound literal ptr decay", index);
                }
            }

        }
        else if (isa<clang::StringLiteral>(e))
        {
            string str = cast<const clang::StringLiteral>(e)->getString().str();
            if (isLtoRValue)
            {
                if (isArrToPtrDecay)
                {
                    AddInstruction(PushString, str);
                }
                else
                {
                    AddInstruction(PushInt, getSizeFromBytes(getSizeOfType(e->getType().getTypePtr())));
                    AddInstructionComment(PushString, "string array", str);
                    AddInstruction(ToStack);
                }
            }


        }
        else if (isa<CallExpr>(e))
        {
            const CallExpr* call = cast<const CallExpr>(e);
            if (checkIntrinsic(call))
            {
                if (call->getType()->isVoidType() == false)
                {
                    if (!isLtoRValue)
                    {
                        AddInstructionComment(Drop, "Function Result Unused");
                        int size = getSizeFromBytes(getSizeOfType(call->getType().getTypePtr()));
                        for (int i = 1; i < size; i++)
                        {
                            AddInstruction(Drop);
                        }
                    }
                }
                return 1;
            }
            const Expr* callee = call->getCallee();
            if (isAddr)
            {
                Throw("cannot take the address of an rvalue of type '" + QualType::getAsString(call->getCallReturnType(context).split(), SCCL::printingPolicy) + "'", TheRewriter, call->getSourceRange());
            }
            LocalVariables.addLevel();
            if (isa<MemberExpr>(callee))
            {
                //const MemberExpr *expr = cast<const MemberExpr>(call->getCallee());
                Throw("Unhandled Call Member Expression", TheRewriter, e->getSourceRange());
            }
            else if (isa<CastExpr>(callee))
            {
                const Expr* const* argArray = call->getArgs();
                std::string funcName = parseCast(cast<const CastExpr>(callee));

                size_t VariadicSize = 0, VariadicPCount = 0, NumParams = 0;
                bool isVariadic = 0;

                parseCallProto(call, isVariadic, NumParams);

                for (uint32_t i = 0; i < call->getNumArgs(); i++)
                {

                    if (isVariadic && i >= NumParams)
                    {
                        VariadicSize += getSizeFromBytes(getSizeOfType(argArray[i]->getType().getTypePtr()));
                        VariadicPCount++;
                    }

                    parseExpression(argArray[i], false, true);
                    const clang::Type* type = argArray[i]->getType().getTypePtr();
                    if (type->isCharType() || type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
                    {
                        AddInstruction(SetConv, scriptData, getSizeOfType(type));
                    }


                }

                if (isVariadic && !call->getDirectCallee()->hasAttr<NativeFuncAttr>())
                {
                    if (!VariadicSize)
                    {
                        int index = LocalVariables.addDecl("", 1);
                        AddInstruction(PushInt, 0);
                        AddInstruction(SetFrame, index);
                        AddInstructionComment(GetFrameP, "__builtin_va_list", index);
                        AddInstructionComment(PushInt, "__builtin_va_pcount", 0);
                        AddInstructionComment(PushInt, "__builtin_va_scount", 0);
                    }
                    else
                    {
                        int index = LocalVariables.addDecl("", VariadicSize);
                        if (VariadicSize > 1)
                        {
                            AddInstructionComment(PushInt, "Type Size (va list)", VariadicSize);
                            AddInstruction(GetFrameP, index);
                            AddInstruction(FromStack);
                            AddInstructionComment(GetFrameP, "__builtin_va_list", index);

                            AddInstructionComment(PushInt, "__builtin_va_pcount", VariadicPCount);
                            AddInstructionComment(PushInt, "__builtin_va_scount", VariadicSize);
                        }
                        else
                        {
                            AddInstruction(SetFrame, index);
                            AddInstructionComment(GetFrameP, "__builtin_va_list", index);
                            AddInstructionComment(PushInt, "__builtin_va_pcount", 1);
                            AddInstructionComment(PushInt, "__builtin_va_scount", 1);
                        }
                    }
                }


                if (call->getDirectCallee() && call->getDirectCallee()->hasAttr<NativeFuncAttr>())
                {
                    NativeFuncAttr* attr = call->getDirectCallee()->getAttr<NativeFuncAttr>();

                    if (call->getDirectCallee()->getStorageClass() != SC_Extern)
                    {
                        Throw("Natives should be defined with the 'extern' keyword", TheRewriter, call->getDirectCallee()->getLocation());
                    }
                    const QualType type = call->getDirectCallee()->getReturnType();
                    int pCount = 0;
                    for (unsigned i = 0; i < call->getDirectCallee()->getNumParams(); i++)
                    {
                        pCount += getSizeFromBytes(getSizeOfType(call->getDirectCallee()->getParamDecl(i)->getType().getTypePtr()));
                    }
                    if (attr->getX64HiDwordHash() || attr->getHash())
                    {
                        //clang attribute arguments cannot be 64bits wide, so using 2 32 bit args can manually joining them is the nicest way to support pc
                        //when using 32 bit(xbox/ps3) the hi dword would be 0 so can be neglected

                        if (isVariadic)
                        {
                            pCount += VariadicSize;
                        }

                        AddInstruction(Native, call->getDirectCallee()->getNameAsString(), ((uint64_t)attr->getX64HiDwordHash() << 32) | attr->getHash(), pCount, getSizeFromBytes(getSizeOfType(type.getTypePtr())));
                    }
                    else
                    {
                        AddInstruction(Native, call->getDirectCallee()->getNameAsString(), pCount, getSizeFromBytes(getSizeOfType(type.getTypePtr())));
                    }

                }
                //else if (call->getDirectCallee() && !call->getDirectCallee()->isDefined() && call->getDirectCallee()->getStorageClass() != StorageClass::SC_Extern)
                //	Throw("Function \"" + call->getDirectCallee()->getNameAsString() + "\" Not Defined", TheRewriter, call->getExprLoc());
                else if (isa<clang::PointerType>(callee->getType()) && !call->getDirectCallee())
                {
                    parseExpression(call->getCallee(), false, true);
                    AddInstruction(PCall);
                }
                else
                {
                    bool inlined = false;
                    if (Option_OptimizationLevel > OptimisationLevel::OL_None)
                    {
                        if (const FunctionDecl* cDecl = call->getDirectCallee())
                        {
                            string name = getNameForFunc(cDecl);
                            string curName = dumpName(cast<NamedDecl>(currFunction));
                            if (cDecl->hasBody() && !scriptData.isFunctionInInlineStack(name) && curName != name)
                            {
                                CompoundStmt* body = cast<CompoundStmt>(cDecl->getBody());
                                Stmt* subBody = body;
                                bool isEmpty = false;
                                if (!cDecl->hasAttr<NoInlineAttr>())
                                {
                                    if (body->size() == 0)
                                    {
                                        isEmpty = true;
                                    }
                                    else if (body->size() == 1)
                                    {
                                        subBody = body->body_front();
                                    }
                                    if (isEmpty)
                                    {
                                        inlined = true;
                                        for (uint32_t i = 0; i < cDecl->getNumParams(); i++)
                                        {
                                            for (int32_t paramSize = getSizeFromBytes(getSizeOfType(cDecl->getParamDecl(i)->getType().getTypePtr())); paramSize--;)
                                            {
                                                AddInstruction(Drop);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        bool isRet = isa<ReturnStmt>(subBody);
                                        bool isExpr = isa<Expr>(subBody);
                                        bool inlineSpec = cDecl->isInlineSpecified();
                                        if (isRet || isExpr || inlineSpec) //inline it
                                        {
                                            inlined = true;
                                            if (!scriptData.addFunctionInline(name, to_string(e->getEndLoc().getRawEncoding())))
                                            {
                                                TEST(false, "Could not inline function", TheRewriter, e->getSourceRange());
                                            }
                                            LocalVariables.addLevel();
                                            int Index = LocalVariables.getCurrentSize();
                                            int32_t paramSize = 0;
                                            for (uint32_t i = 0; i < cDecl->getNumParams(); i++)
                                            {
                                                paramSize += getSizeFromBytes(getSizeOfType(cDecl->getParamDecl(i)->getType().getTypePtr()));
                                                handleParmVarDecl((ParmVarDecl*)(cDecl->getParamDecl(i)));
                                            }
                                            if (paramSize == 1)
                                            {
                                                AddInstructionComment(SetFrame, "Inline Argument Setting", Index);
                                            }
                                            else if (paramSize > 1)
                                            {
                                                AddInstruction(PushInt, paramSize);
                                                AddInstruction(GetFrameP, Index);
                                                AddInstructionComment(FromStack, "Inline Argument Setting");
                                            }
                                            if (isRet)
                                            {
                                                parseExpression(cast<ReturnStmt>(subBody)->getRetValue(), false, true);
                                            }
                                            else if (isExpr)
                                            {
                                                parseExpression(cast<Expr>(subBody));
                                            }
                                            else
                                            {
                                                parseStatement(body, "", "");
                                                if (scriptData.getCurrentFunction()->endsWithInlineReturn(scriptData.getInlineJumpLabelAppend()))
                                                {
                                                    scriptData.getCurrentFunction()->RemoveLast();
                                                    //remove the last jump, but keep the label, just incase other places in the function have returns
                                                }
                                                AddInstructionComment(Label, "Inline return location", scriptData.getInlineJumpLabelAppend());
                                            }
                                            LocalVariables.removeLevel();
                                            scriptData.removeFunctionInline(name);

                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (!inlined)
                    {
                        string name = getNameForFunc(call->getDirectCallee());
                        if (auto func = scriptData.getFunctionFromName(name))
                        {
                            AddInstructionComment(Call, "NumArgs: " + to_string(call->getNumArgs()), func);
                        }
                        else
                            Throw("Function \"" + name + "\" not found", TheRewriter, call->getExprLoc());

                    }

                }

                if (call->getType()->isVoidType() == false)
                {
                    if (!isLtoRValue)
                    {
                        AddInstructionComment(Drop, "Function Result Unused");
                        int size = getSizeFromBytes(getSizeOfType(call->getType().getTypePtr()));
                        for (int i = 1; i < size; i++)
                        {
                            AddInstruction(Drop);
                        }
                    }
                }
            }
            else
                Throw("Unexpected Expression for Callee!", TheRewriter, callee->getExprLoc());
            LocalVariables.removeLevel();
            return 1;

        }
        else if (isa<CastExpr>(e))
        {
            const CastExpr* icast = cast<const CastExpr>(e);
            switch (icast->getCastKind())
            {
            case clang::CK_IntegralToFloating:
            {
                if (isa<IntegerLiteral>(icast->getSubExpr()))
                {
                    const IntegerLiteral* literal = cast<const IntegerLiteral>(icast->getSubExpr());

                    AddInstructionConditionally(isLtoRValue, PushFloat, (float)(int)(literal->getValue().getSExtValue()));
                    return true;
                }
                else
                {
                    parseExpression(icast->getSubExpr(), false, isLtoRValue);
                    AddInstructionConditionally(isLtoRValue, ItoF);
                    return true;
                }
            }
            case clang::CK_FloatingCast:
            case clang::CK_IntegralCast:
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                break;
            case clang::CK_ArrayToPointerDecay:
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue, printVTable, isAssign, true);
                break;
            case clang::CK_LValueToRValue:
            {
                parseExpression(icast->getSubExpr(), isAddr, true, printVTable);
                if (!isLtoRValue)
                {
                    for (int i = getSizeFromBytes(getSizeOfType(icast->getSubExpr()->getType().getTypePtr())); i--;)
                    {
                        AddInstructionComment(Drop, "unused result (CK_LValueToRValue)");
                    }
                }
                //const Expr *subE = icast->getSubExpr();

                //handleRValueDeclRef(subE);
                break;
            }
            case clang::CK_UncheckedDerivedToBase:
            {
                //CXX
                //if (isa<DeclRefExpr>(icast->getSubExpr()))
                    //parseExpression(icast->getSubExpr());

                Throw("Unsupported Cast", TheRewriter, icast->getSourceRange());
                break;

            }
            case clang::CK_DerivedToBase:
            {
                parseExpression(icast->getSubExpr());
                break;
            }
            case clang::CK_PointerToIntegral:
            {

                parseExpression(icast->getSubExpr(), false, isLtoRValue);
                break;
            }
            case clang::CK_PointerToBoolean:
            {
                parseExpression(icast->getSubExpr(), false, isLtoRValue);
                AddInstructionConditionally(isLtoRValue, IsNotZero);
                break;
            }
            case clang::CK_IntegralToPointer:
            {
                //Fixed support for:
                //char* test = GET_STRING_PTR();
                //and other pointers
                parseExpression(icast->getSubExpr(), false, isLtoRValue);
                break;
            }
            case clang::CK_FloatingToIntegral:
            {

                parseExpression(icast->getSubExpr(), false, isLtoRValue);
                AddInstructionConditionally(isLtoRValue, FtoI);
                break;
            }
            case clang::CK_NoOp:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                break;
            }
            case clang::CK_FunctionToPointerDecay:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                break;
            }
            case clang::CK_BitCast:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                break;
            }
            case clang::CK_IntegralToBoolean:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                if (isLtoRValue)
                {
                    const BinaryOperator* bOp;
                    if (!icast->getSubExpr()->isEvaluatable(context, Expr::SE_NoSideEffects) && !((bOp = dyn_cast<BinaryOperator>(icast->getSubExpr())) && (bOp->getOpcode() == BO_LOr || bOp->getOpcode() == BO_LAnd)))
                    {
                        AddInstruction(IsNotZero);
                    }
                }
                break;
            }
            case clang::CK_FloatingToBoolean:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                if (isLtoRValue)
                {
                    AddInstruction(PushFloat, 0);
                    AddInstruction(FCmpNe);
                }
                break;
            }
            case clang::CK_FloatingComplexToReal:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                AddInstructionConditionally(!isLtoRValue, Drop);
                break;
            }
            case clang::CK_IntegralComplexToReal:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                AddInstructionConditionally(!isLtoRValue, Drop);
                break;
            }
            case clang::CK_NullToPointer:
            {
                if (isLtoRValue)
                {
                    AddInstruction(PushNullPtr);
                }
                else
                {
                    parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                }
                break;
            }
            case clang::CK_FloatingRealToComplex:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                AddInstructionConditionally(isLtoRValue, PushFloat, 0.0);
                break;
            }
            case clang::CK_IntegralRealToComplex:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                AddInstructionConditionally(isLtoRValue, PushInt, 0);
                break;
            }
            case clang::CK_FloatingComplexToIntegralComplex:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                if (isLtoRValue)
                {
                    LocalVariables.addLevel();
                    int index = LocalVariables.addDecl("imagPart", 1);
                    AddInstruction(SetFrame, index);
                    AddInstruction(FtoI);
                    AddInstruction(GetFrame, index);
                    AddInstruction(FtoI);
                    LocalVariables.removeLevel();
                }
                break;
            }
            case clang::CK_IntegralComplexToFloatingComplex:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                if (isLtoRValue)
                {
                    LocalVariables.addLevel();
                    int index = LocalVariables.addDecl("imagPart", 1);
                    AddInstruction(SetFrame, index);
                    AddInstruction(ItoF);
                    AddInstruction(GetFrame, index);
                    AddInstruction(ItoF);
                    LocalVariables.removeLevel();
                }
                break;
            }
            case clang::CK_FloatingComplexCast:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                break;
            }
            case clang::CK_IntegralComplexCast:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                break;
            }
            case clang::CK_FloatingComplexToBoolean:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                if (isLtoRValue)ComplexToBoolean(true);
                break;
            }
            case clang::CK_IntegralComplexToBoolean:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);
                if (isLtoRValue)ComplexToBoolean(false);
                break;
            }
            case clang::CK_ToUnion:
            {
                parseExpression(icast->getSubExpr(), isAddr, isLtoRValue);//clang does check to make sure this is valid	
                break;
            }
            case clang::CK_ToVoid:
            {
                Expr::EvalResult result;

                if (!isAddr && icast->getSubExpr()->EvaluateAsRValue(result, context) && !result.HasSideEffects)
                {
                    if (result.Val.isInt())
                        AddComment("(Void Cast) Literal NO-OP Value: " + to_string(result.Val.getInt().getSExtValue()));
                    else
                        AddComment("(Void Cast) Literal non int NO-OP");
                    //no-op cast
                    return true;
                }
                else
                {
                    parseExpression(icast->getSubExpr(), false, isLtoRValue);

                }
                break;
            }
            default:
                Throw("Unhandled cast (CK) of type " + string(icast->getCastKindName()), TheRewriter, e->getSourceRange());

            }
        }
        else if (isa<DeclRefExpr>(e))
        {
            const DeclRefExpr* declref = cast<const DeclRefExpr>(e);

            if (isa<EnumConstantDecl>(declref->getDecl()))
            {
                const EnumConstantDecl* enumDecl = cast<const EnumConstantDecl>(declref->getDecl());
                AddInstructionConditionally(isLtoRValue, PushInt, enumDecl->getInitVal().getSExtValue());
                return 1;
            }

            string key = declref->getNameInfo().getAsString();

            if (declref->getDecl()->getType().getTypePtr()->isArrayType())
            {
                printDeclWithKey(key, true, isLtoRValue, isAssign, declref);
            }
            else
                printDeclWithKey(key, isAddr, isLtoRValue, isAssign, declref);

            return true;
        }
        else if (isa<ArraySubscriptExpr>(e))
        {
            return parseArraySubscriptExpr(e, isAddr, isLtoRValue, isArrToPtrDecay);
        }
        else if (isa<ParenExpr>(e))
        {
            const ParenExpr* parenExpr = cast<const ParenExpr>(e);
            parseExpression(parenExpr->getSubExpr(), isAddr, isLtoRValue, false, isAssign, isArrToPtrDecay);
        }
        else if (isa<UnaryOperator>(e))
        {
            const UnaryOperator* op = cast<const UnaryOperator>(e);

            Expr* subE = op->getSubExpr();
            if (op->getOpcode() == UO_Minus)
            {
                if (isa<Expr>(subE))
                {
                    parseExpression(subE, isAddr, isLtoRValue);
                    if (isLtoRValue)
                    {
                        if (subE->getType()->isComplexType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("imagPart", 1);
                            AddInstruction(SetFrame, index);
                            AddInstruction(FNeg);
                            AddInstruction(GetFrame, index);
                            AddInstruction(FNeg);
                            LocalVariables.removeLevel();
                        }
                        else if (subE->getType()->isComplexIntegerType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("imagPart", 1);
                            AddInstruction(SetFrame, index);
                            AddInstruction(Neg);
                            AddInstruction(GetFrame, index);
                            AddInstruction(Neg);
                            LocalVariables.removeLevel();
                        }
                        else if (subE->getType()->isRealFloatingType())
                        {
                            AddInstruction(FNeg);
                        }
                        else
                        {
                            AddInstruction(Neg);
                        }
                    }
                }
                else
                {
                    Throw("unimplmented UO_MINUS", TheRewriter, e->getSourceRange());
                }
                return false;
            }
            else if (op->getOpcode() == UO_LNot)
            {
                if (isa<IntegerLiteral>(subE))
                {
                    const IntegerLiteral* literal = cast<const IntegerLiteral>(subE);
                    AddInstructionConditionally(isLtoRValue, PushInt, !literal->getValue().getSExtValue());
                }
                else if (isa<FloatingLiteral>(subE))
                {
                    const FloatingLiteral* literal = cast<const FloatingLiteral>(subE);
                    AddInstructionConditionally(isLtoRValue, PushFloat, !extractAPFloat(literal->getValue()));
                }
                else if (isa<Expr>(subE))
                {
                    parseExpression(subE, isAddr, isLtoRValue);
                    if (isLtoRValue)
                    {
                        if (subE->getType()->isComplexType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("imagPart", 1);
                            AddInstruction(SetFrame, index);
                            AddInstruction(PushFloat, 0);
                            AddInstruction(FCmpEq);
                            AddInstruction(GetFrame, index);
                            AddInstruction(PushFloat, 0);
                            AddInstruction(FCmpEq);
                            AddInstruction(And);
                            LocalVariables.removeLevel();
                        }
                        else if (subE->getType()->isComplexIntegerType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("imagPart", 1);
                            AddInstruction(SetFrame, index);
                            AddInstruction(Not);
                            AddInstruction(GetFrame, index);
                            AddInstruction(Not);
                            AddInstruction(And);
                            LocalVariables.removeLevel();
                        }
                        else if (subE->getType()->isFloatingType())
                        {
                            AddInstruction(PushFloat, 0);
                            AddInstruction(FCmpEq);
                        }
                        else
                        {
                            AddInstruction(Not);
                        }
                    }
                }
                else
                {
                    Throw("unimplmented UO_LNot", TheRewriter, e->getSourceRange());
                }

                return true;
            }
            else if (op->getOpcode() == UO_Not)
            {
                if (isa<IntegerLiteral>(subE))
                {
                    const IntegerLiteral* literal = cast<const IntegerLiteral>(subE);
                    AddInstructionConditionally(isLtoRValue, PushInt, ~(int)literal->getValue().getSExtValue());
                }
                else if (isa<Expr>(subE))
                {
                    parseExpression(subE, isAddr, isLtoRValue);
                    //Not operator for complex numbers is the conjugate
                    if (isLtoRValue)
                    {
                        if (subE->getType()->isComplexIntegerType())
                        {
                            AddInstruction(Neg);
                        }
                        else if (subE->getType()->isComplexType())
                        {
                            AddInstruction(FNeg);
                        }
                        else
                        {
                            AddInstruction(PushInt, -1);
                            AddInstruction(Xor);
                        }
                    }
                }
                else
                {
                    Throw("unimplmented UO_Not", TheRewriter, e->getSourceRange());
                }
                return true;
            }
            else if (op->getOpcode() == UO_AddrOf)
            {
                if (isa<ArraySubscriptExpr>(subE))
                {
                    parseArraySubscriptExpr(subE, true);
                }
                else if (isa<DeclRefExpr>(subE))
                {
                    parseExpression(subE, true, false);
                    if (!isLtoRValue && !isAddr)
                    {
                        AddInstructionComment(Drop, "unused result (UO_AddrOf - DeclRefExpr)");
                    }
                }
                else if (isa<CompoundLiteralExpr>(subE))
                {
                    Throw("error: taking address of temporary", TheRewriter, subE->getSourceRange());
                }
                else
                {
                    parseExpression(subE, true, false);
                    if (!isLtoRValue)
                    {
                        AddInstructionComment(Drop, "unused result (UO_AddrOf - else)");
                    }
                }
                return  true;

            }
            else if (op->getOpcode() == UO_Deref)
            {
                const clang::Type* type = e->getType().getTypePtr();
                int size = getSizeOfType(type);
                int bSize = getSizeFromBytes(size);

                if (!isAddr && !isArrToPtrDecay)
                {
                    if (bSize > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
                    {
                        AddInstructionComment(PushInt, "Type Size (Deref)", bSize);
                    }
                    else if ((size == 1 || size == 2) && isAssign)
                    {
                        LocalVariables.addLevel();

                        if (scriptData.getBuildPlatform() == P_PC)
                        {
                            int index = LocalVariables.addDecl("DerefSavedVar", 1);
                            int buffer = LocalVariables.addDecl("64BitTempStorage", 2);

                            AddInstruction(SetConv, scriptData, size);

                            AddInstruction(PushInt, 0);
                            AddInstructionComment(SetFrame, "64BitTempStorage[0]", buffer);
                            AddInstruction(PushInt, 0);
                            AddInstructionComment(SetFrame, "64BitTempStorage[1]", buffer + 1);



                            parseExpression(subE, subE->getType().getTypePtr()->isArrayType(), true);
                            AddInstruction(Dup);
                            AddInstructionComment(SetFrame, "DerefSavedVar", index);


                            AddInstruction(PGet);
                            AddInstruction(PushInt, size == 1 ? 0xFFFFFF : 0xFFFF0000);
                            AddInstruction(And);
                            AddInstruction(Or);
                            AddInstructionComment(SetFrame, "64BitTempStorage[0]", buffer);

                            AddInstructionComment(GetFrame, "DerefSavedVar", index);
                            AddInstruction(AddImm, 4);
                            AddInstruction(PGet);
                            AddInstructionComment(GetFrameP, "64BitTempStorage[0]", buffer);
                            AddInstruction(AddImm, 4);
                            AddInstruction(PSet);

                            AddInstructionComment(GetFrame, "64BitTempStorage[0]", buffer);
                            AddInstructionComment(GetFrame, "DerefSavedVar", index);
                        }
                        else
                        {
                            int index = LocalVariables.addDecl("DerefSavedVar", 1);
                            AddInstruction(SetConv, scriptData, size);

                            parseExpression(subE, subE->getType().getTypePtr()->isArrayType(), true);
                            AddInstruction(Dup);
                            AddInstructionComment(SetFrame, "DerefSavedVar", index);

                            AddInstruction(PGet);
                            AddInstruction(PushInt, size == 1 ? 0xFFFFFF : 0xFFFF);
                            AddInstruction(And);
                            AddInstruction(Or);

                            AddInstructionComment(GetFrame, "DerefSavedVar", index);
                        }
                        LocalVariables.removeLevel();
                        goto DerefPtrOnStack;
                    }
                }

                if (isa<ArraySubscriptExpr>(subE))
                    parseArraySubscriptExpr(subE, false, isArrToPtrDecay);
                else if (isa<DeclRefExpr>(subE))
                    parseExpression(subE, false, false);
                else
                    parseExpression(subE, false, true);

            DerefPtrOnStack:


                if (!isAddr && !isArrToPtrDecay)
                {
                    if (isLtoRValue)
                    {
                        if (bSize > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
                        {
                            AddInstruction(ToStack);
                        }
                        else
                        {
                            if (bSize > 1 && type->isArrayType())
                                return true;

                            AddInstruction(PGet);
                            if (size == 1 || size == 2)
                            {
                                AddInstruction(GetConv, scriptData, size, e->getType()->isSignedIntegerType());
                            }
                        }
                    }
                    else
                    {
                        if (bSize > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
                        {
                            AddInstruction(FromStack);
                        }
                        else
                        {
                            AddInstruction(PSet);
                        }
                    }
                }


                return true;
            }
            else if (op->getOpcode() == UO_Real)
            {
                if (isa<Expr>(subE))
                {
                    parseExpression(subE, isAddr, isLtoRValue);
                    if (subE->getType()->isAnyComplexType())
                    {
                        if (isLtoRValue)
                        {
                            AddInstruction(Drop);
                        }
                    }
                    else
                    {
                        Throw("__real operator used on non complex data type");
                    }
                }
                else
                {
                    Throw("unimplmented UO_Real", TheRewriter, e->getSourceRange());
                }
                return true;
            }
            else if (op->getOpcode() == UO_Imag)
            {
                if (isa<Expr>(subE))
                {
                    parseExpression(subE, isAddr, isLtoRValue);
                    if (subE->getType()->isAnyComplexType())
                    {
                        if (isLtoRValue)
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("imagPart", 1);
                            AddInstruction(SetFrame, index);
                            AddInstruction(Drop);
                            AddInstruction(GetFrame, index);
                            LocalVariables.removeLevel();
                        }
                    }
                    else
                    {
                        Throw("__imag operator used on non complex data type");
                    }
                }
                else
                {
                    Throw("unimplmented UO_Imag", TheRewriter, e->getSourceRange());
                }
                return true;
            }

            int pMult = 1;
            if ((op->isPrefix() || op->isPostfix()) && subE->getType().getTypePtr()->isAnyPointerType())
            {
                const clang::Type* pTypePtr = subE->getType().getTypePtr()->getPointeeType().getTypePtr();

                int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
                pMult = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;
            }

            if (op->isPrefix())
            {

                if (op->isIncrementOp())
                {

                    if (subE->getType()->isBooleanType())
                    {
                        AddInstruction(PushInt, 1);//bool inc operation can only be 1
                    }
                    else
                    {
                        parseExpression(subE, false, true);

                        if (subE->getType()->isRealFloatingType())
                        {
                            AddInstruction(FAddImm, 1.0);
                        }
                        else if (subE->getType()->isComplexType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("complexTemp", 1);
                            AddInstruction(SetFrame, index);
                            AddInstruction(FAddImm, 1.0);
                            AddInstruction(GetFrame, index);
                            LocalVariables.removeLevel();
                        }
                        else if (subE->getType()->isComplexIntegerType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("complexTemp", 1);
                            AddInstruction(SetFrame, index);
                            AddInstruction(AddImm, 1);
                            AddInstruction(GetFrame, index);
                            LocalVariables.removeLevel();
                        }
                        else if (getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
                        {
                            Throw("Incriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split(), SCCL::printingPolicy) + "'", TheRewriter, subE->getSourceRange());
                        }
                        else
                        {
                            AddInstruction(AddImm, pMult);
                        }

                    }
                    if (isLtoRValue)
                    {
                        if (subE->getType()->isAnyComplexType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("complex", 2);
                            AddInstruction(SetFrame, index + 1);//store imag
                            AddInstruction(Dup);//dup real
                            AddInstruction(SetFrame, index);//store real
                            AddInstruction(GetFrame, index + 1);//restore imag
                            AddInstruction(GetFrame, index);//push real
                            AddInstruction(GetFrame, index + 1);//push imag
                            LocalVariables.removeLevel();
                        }
                        else
                        {
                            AddInstruction(Dup);
                        }
                    }
                    parseExpression(subE, false, false, true, true);
                    return 1;
                }
                else if (op->isDecrementOp())
                {

                    parseExpression(subE, false, true);

                    if (subE->getType()->isRealFloatingType())
                    {
                        AddInstruction(FAddImm, -1.0);
                    }
                    else if (subE->getType()->isBooleanType())
                    {
                        AddInstruction(AddImm, -pMult);
                        AddInstruction(IsNotZero);//bool dec operation can be 1 or 0
                    }
                    else if (subE->getType()->isComplexType())
                    {
                        LocalVariables.addLevel();
                        int index = LocalVariables.addDecl("complexTemp", 1);
                        AddInstruction(SetFrame, index);
                        AddInstruction(FAddImm, -1.0);
                        AddInstruction(GetFrame, index);
                        LocalVariables.removeLevel();
                    }
                    else if (subE->getType()->isComplexIntegerType())
                    {
                        LocalVariables.addLevel();
                        int index = LocalVariables.addDecl("complexTemp", 1);
                        AddInstruction(SetFrame, index);
                        AddInstruction(AddImm, -1);
                        AddInstruction(GetFrame, index);
                        LocalVariables.removeLevel();
                    }
                    else if (getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
                    {
                        Throw("Decriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split(), SCCL::printingPolicy) + "'", TheRewriter, subE->getSourceRange());
                    }
                    else
                    {
                        AddInstruction(AddImm, -pMult);
                    }
                    if (isLtoRValue)
                    {
                        if (subE->getType()->isAnyComplexType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("complex", 2);
                            AddInstruction(SetFrame, index + 1);//store imag
                            AddInstruction(Dup);//dup real
                            AddInstruction(SetFrame, index);//store real
                            AddInstruction(GetFrame, index + 1);//restore imag
                            AddInstruction(GetFrame, index);//push real
                            AddInstruction(GetFrame, index + 1);//push imag
                            LocalVariables.removeLevel();
                        }
                        else
                        {
                            AddInstruction(Dup);//ret value
                        }
                    }
                    parseExpression(subE, false, false, true, true);
                    return 1;
                }
            }
            else if (op->isPostfix())
            {
                if (op->isIncrementOp())
                {

                    if (!subE->getType()->isBooleanType())
                        parseExpression(subE, false, true);

                    if (isLtoRValue)
                    {
                        if (subE->getType()->isAnyComplexType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("complex", 2);
                            AddInstruction(SetFrame, index + 1);//store imag
                            AddInstruction(Dup);//dup real
                            AddInstruction(SetFrame, index);//store real
                            AddInstruction(GetFrame, index + 1);//restore imag
                            AddInstruction(GetFrame, index);//push real
                            AddInstruction(GetFrame, index + 1);//push imag
                            LocalVariables.removeLevel();
                        }
                        else if (subE->getType()->isBooleanType())
                        {
                            parseExpression(subE, false, true);
                        }
                        else
                        {
                            AddInstruction(Dup);
                        }
                    }

                    if (subE->getType()->isRealFloatingType())
                    {
                        AddInstruction(FAddImm, 1.0);
                    }
                    else if (subE->getType()->isBooleanType())
                    {
                        AddInstruction(PushInt, 1);//bool inc operation can only be 1
                    }
                    else if (subE->getType()->isComplexType())
                    {
                        LocalVariables.addLevel();
                        int index = LocalVariables.addDecl("complexTemp", 1);
                        AddInstruction(SetFrame, index);
                        AddInstruction(FAddImm, 1.0);
                        AddInstruction(GetFrame, index);
                        LocalVariables.removeLevel();
                    }
                    else if (subE->getType()->isComplexIntegerType())
                    {
                        LocalVariables.addLevel();
                        int index = LocalVariables.addDecl("complexTemp", 1);
                        AddInstruction(SetFrame, index);
                        AddInstruction(AddImm, 1);
                        AddInstruction(GetFrame, index);
                        LocalVariables.removeLevel();
                    }
                    else if (getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
                    {
                        Throw("Incriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split(), SCCL::printingPolicy) + "'", TheRewriter, subE->getSourceRange());
                    }
                    else
                    {
                        AddInstruction(AddImm, pMult);
                    }

                    parseExpression(subE, false, false, true, true);
                    return 1;
                }
                else if (op->isDecrementOp())
                {
                    parseExpression(subE, false, true);

                    if (isLtoRValue)
                    {
                        if (subE->getType()->isAnyComplexType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("complex", 2);
                            AddInstruction(SetFrame, index + 1);//store imag
                            AddInstruction(Dup);//dup real
                            AddInstruction(SetFrame, index);//store real
                            AddInstruction(GetFrame, index + 1);//restore imag
                            AddInstruction(GetFrame, index);//push real
                            AddInstruction(GetFrame, index + 1);//push imag
                            LocalVariables.removeLevel();
                        }
                        else
                        {
                            AddInstruction(Dup);
                        }
                    }

                    if (subE->getType()->isRealFloatingType())
                    {
                        AddInstruction(FAddImm, -1.0);
                    }
                    else if (subE->getType()->isBooleanType())
                    {
                        AddInstruction(AddImm, -pMult);
                        AddInstruction(IsNotZero);//bool dec operation can be 1 or 0
                    }
                    else if (subE->getType()->isComplexType())
                    {
                        LocalVariables.addLevel();
                        int index = LocalVariables.addDecl("complexTemp", 1);
                        AddInstruction(SetFrame, index);
                        AddInstruction(FAddImm, -1.0);
                        AddInstruction(GetFrame, index);
                        LocalVariables.removeLevel();
                    }
                    else if (subE->getType()->isComplexIntegerType())
                    {
                        LocalVariables.addLevel();
                        int index = LocalVariables.addDecl("complexTemp", 1);
                        AddInstruction(SetFrame, index);
                        AddInstruction(AddImm, -1);
                        AddInstruction(GetFrame, index);
                        LocalVariables.removeLevel();
                    }
                    else if (getSizeFromBytes(getSizeOfType(subE->getType().getTypePtr())) != 1)
                    {
                        Throw("Decriment operator used on unsupported type '" + QualType::getAsString(subE->getType().split(), SCCL::printingPolicy) + "'", TheRewriter, subE->getSourceRange());
                    }
                    else
                    {
                        AddInstruction(AddImm, -pMult);
                    }

                    parseExpression(subE, false, false, true, true);
                    return 1;
                }
            }
        }
        else if (isa<BinaryOperator>(e))
        {
            const BinaryOperator* bOp = cast<const BinaryOperator>(e);
            BinaryOperatorKind op = bOp->getOpcode();

            if (bOp->getOpcode() == BO_Assign)
            {

                parseExpression(bOp->getRHS(), isAddr, true, true);
                int bSize = getSizeFromBytes(getSizeOfType(bOp->getRHS()->getType().getTypePtr()));
                if (bSize > 1)
                {
                    AddInstruction(PushInt, bSize);
                    parseExpression(bOp->getLHS(), true, false, true, true);
                    AddInstruction(FromStack);
                    if (isLtoRValue)
                    {
                        parseExpression(bOp->getLHS(), false, true, true, false);
                    }
                }
                else
                {
                    if (isLtoRValue)
                    {
                        AddInstruction(Dup);
                    }
                    parseExpression(bOp->getLHS(), false, false, true, true);
                }

                return true;
            }
            if (bOp->getOpcode() == BO_Comma)
            {
                parseExpression(bOp->getLHS());
                parseExpression(bOp->getRHS(), isAddr, isLtoRValue);
                return true;
            }
            if (bOp->getOpcode() == BO_LAnd)
            {
                if (isLtoRValue)
                {
                    static int counter = 0;
                    string label = "__and_" + to_string(counter++);
                    parseCondition(bOp, label + "_true", label + "_false");
                    AddJumpInlineCheckStr(Label, label + "_true");
                    AddInstruction(PushInt, 1);
                    AddJumpInlineCheckStr(Jump, label + "_end");
                    AddJumpInlineCheckStr(Label, label + "_false");
                    AddInstruction(PushNullPtr);
                    AddJumpInlineCheckStr(Label, label + "_end");

                    /*parseExpression(bOp->getLHS(), false, true);
                    if (bOp->getLHS()->getType()->isAnyComplexType())
                    {
                    ComplexToBoolean(bOp->getLHS()->getType()->isComplexType());
                    }
                    else if (bOp->getLHS()->getType()->isRealFloatingType())
                    {
                    AddInstruction(PushFloat, 0.0);
                    AddInstruction(FCmpNe);
                    }
                    AddInstruction(Dup);
                    AddJumpInlineCheckStr(JumpFalse, label);
                    AddInstruction(Drop);
                    parseExpression(bOp->getRHS(), false, true);
                    if (bOp->getRHS()->getType()->isAnyComplexType())
                    {
                    ComplexToBoolean(bOp->getRHS()->getType()->isComplexType());
                    }
                    else if (bOp->getLHS()->getType()->isRealFloatingType())
                    {
                    AddInstruction(PushFloat, 0.0);
                    AddInstruction(FCmpNe);
                    }
                    AddJumpInlineCheckStr(Label, label);*/

                }
                else
                {
                    //parse LHS and RHS as not LtoR so the results get dropped, but any function calls etc still happen
                    parseExpression(bOp->getLHS());
                    parseExpression(bOp->getRHS());
                }
                return true;
            }
            if (bOp->getOpcode() == BO_LOr)
            {
                if (isLtoRValue)
                {
                    static int counter = 0;
                    string label = "__or_" + to_string(counter++);
                    parseCondition(bOp, label + "_true", label + "_false");
                    AddJumpInlineCheckStr(Label, label + "_true");
                    AddInstruction(PushInt, 1);
                    AddJumpInlineCheckStr(Jump, label + "_end");
                    AddJumpInlineCheckStr(Label, label + "_false");
                    AddInstruction(PushNullPtr);
                    AddJumpInlineCheckStr(Label, label + "_end");
                    /*parseExpression(bOp->getLHS(), false, true);
                    if (bOp->getLHS()->getType()->isAnyComplexType())
                    {
                    ComplexToBoolean(bOp->getLHS()->getType()->isComplexType());
                    }
                    else if (bOp->getLHS()->getType()->isRealFloatingType())
                    {
                    AddInstruction(PushFloat, 0.0);
                    AddInstruction(FCmpNe);
                    }
                    AddInstruction(Dup);
                    AddJumpInlineCheckStr(JumpTrue, label);
                    AddInstruction(Drop);
                    parseExpression(bOp->getRHS(), false, true);
                    if (bOp->getRHS()->getType()->isAnyComplexType())
                    {
                    ComplexToBoolean(bOp->getRHS()->getType()->isComplexType());
                    }
                    else if (bOp->getLHS()->getType()->isRealFloatingType())
                    {
                    AddInstruction(PushFloat, 0.0);
                    AddInstruction(FCmpNe);
                    }
                    AddJumpInlineCheckStr(Label, label);*/
                }
                else
                {
                    //parse LHS and RHS as not LtoR so the results get dropped, but any function calls etc still happen
                    parseExpression(bOp->getLHS());
                    parseExpression(bOp->getRHS());
                }
                return true;
            }

            if (bOp->getLHS()->getType()->isAnyComplexType() || bOp->getRHS()->getType()->isAnyComplexType())
            {
                if (!isLtoRValue)
                {
                    switch (bOp->getOpcode())
                    {
                    case BO_AddAssign:
                    case BO_AndAssign:
                    case BO_DivAssign:
                    case BO_MulAssign:
                    case BO_OrAssign:
                    case BO_RemAssign:
                    case BO_ShlAssign:
                    case BO_ShrAssign:
                    case BO_SubAssign:
                    case BO_XorAssign:
                        break;//these are ok if not LtoR, BO_Assign has already been handled
                    default:
                        parseExpression(bOp->getLHS());
                        parseExpression(bOp->getRHS());
                        Warn("Unused operator \"" + bOp->getOpcodeStr().str() + "\"", TheRewriter, bOp->getOperatorLoc());
                        return true;
                    }
                }
                if (currFunction)
                {
                    parseExpression(bOp->getLHS(), isAddr, true, true);
                    if (!bOp->getLHS()->getType()->isAnyComplexType())
                    {
                        if (bOp->getLHS()->getType()->isFloatingType())
                        {
                            AddInstruction(PushFloat, 0);
                        }
                        else
                        {
                            AddInstruction(PushInt, 0);
                        }
                    }
                    parseExpression(bOp->getRHS(), isAddr, true, true);
                    if (!bOp->getRHS()->getType()->isAnyComplexType())
                    {
                        if (bOp->getRHS()->getType()->isFloatingType())
                        {
                            AddInstruction(PushFloat, 0);
                        }
                        else
                        {
                            AddInstruction(PushInt, 0);
                        }
                    }
                    bool isFlt = bOp->getLHS()->getType()->isFloatingType();
                    if (!isFlt)
                    {
                        if (bOp->getRHS()->getType()->isFloatingType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("imagPart", 1);
                            AddInstruction(SetFrame, index);
                            AddInstruction(FtoI);
                            AddInstruction(GetFrame, index);
                            AddInstruction(FtoI);
                            LocalVariables.removeLevel();
                        }
                    }
                    else
                    {
                        if (!bOp->getRHS()->getType()->isFloatingType())
                        {
                            LocalVariables.addLevel();
                            int index = LocalVariables.addDecl("imagPart", 1);
                            AddInstruction(SetFrame, index);
                            AddInstruction(ItoF);
                            AddInstruction(GetFrame, index);
                            AddInstruction(ItoF);
                            LocalVariables.removeLevel();
                        }
                    }
                    LocalVariables.addLevel();
                    int startindex = LocalVariables.addDecl("complex", 4);
                    AddInstruction(PushInt, 4);
                    AddInstruction(GetFrameP, startindex);
                    AddInstruction(FromStack);
#define AddIns() AddInstructionCondition(isFlt, FAdd, Add)
#define SubIns() AddInstructionCondition(isFlt, FSub, Sub)
#define MultIns() AddInstructionCondition(isFlt, FMult, Mult)
#define DivIns() AddInstructionCondition(isFlt, FDiv, Div)
                    switch (bOp->getOpcode())
                    {
                    case BO_Add:
                    {
                        if (!isLtoRValue)
                        {
                            break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
                        }
                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 2);
                        AddIns();
                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 3);
                        AddIns();

                    }
                    break;
                    case BO_AddAssign:
                    {
                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 2);
                        AddIns();
                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 3);
                        AddIns();

                        AddInstruction(PushInt, 2);
                        parseExpression(bOp->getLHS(), true);
                        AddInstruction(FromStack);

                    }
                    goto CheckAssignL2R;

                    case BO_Sub:
                    {
                        if (!isLtoRValue)
                        {
                            break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
                        }

                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 2);
                        SubIns();
                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 3);
                        SubIns();
                    }
                    break;
                    case BO_SubAssign:
                    {
                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 2);
                        SubIns();
                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 3);
                        SubIns();

                        AddInstruction(PushInt, 2);
                        parseExpression(bOp->getLHS(), true);
                        AddInstruction(FromStack);
                    }
                    goto CheckAssignL2R;

                    case BO_Mul:
                    {
                        if (!isLtoRValue)
                        {
                            break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
                        }
                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 2);
                        MultIns();

                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 3);
                        MultIns();
                        SubIns();
                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 3);
                        MultIns();

                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 2);
                        MultIns();
                        AddIns();
                    }
                    break;
                    case BO_MulAssign:
                    {
                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 2);
                        MultIns();

                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 3);
                        MultIns();
                        SubIns();
                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 3);
                        MultIns();

                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 2);
                        MultIns();
                        AddIns();

                        AddInstruction(PushInt, 2);
                        parseExpression(bOp->getLHS(), true);
                        AddInstruction(FromStack);
                    }
                    goto CheckAssignL2R;

                    case BO_Div:
                    {
                        if (!isLtoRValue)
                        {
                            break;//just skip the calculations if its not a l to r, dont need to worry about operands on the stack as they have already been removed
                        }
                        int divide = LocalVariables.addDecl("divide", 1);

                        AddInstruction(GetFrame, startindex + 2);
                        AddInstruction(Dup);
                        MultIns();

                        AddInstruction(GetFrame, startindex + 3);
                        AddInstruction(Dup);
                        MultIns();

                        AddIns();
                        AddInstruction(SetFrame, divide);

                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 2);
                        MultIns();
                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 3);
                        MultIns();
                        AddIns();
                        AddInstruction(GetFrame, divide);
                        DivIns();

                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 2);
                        MultIns();
                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 3);

                        MultIns();
                        SubIns();
                        AddInstruction(GetFrame, divide);
                        DivIns();
                    }
                    break;
                    case BO_DivAssign:
                    {
                        int divide = LocalVariables.addDecl("divide", 1);
                        AddInstruction(GetFrame, startindex + 2);
                        AddInstruction(Dup);
                        MultIns();

                        AddInstruction(GetFrame, startindex + 3);
                        AddInstruction(Dup);
                        MultIns();

                        AddIns();
                        AddInstruction(SetFrame, divide);

                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 2);
                        MultIns();
                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 3);
                        MultIns();
                        AddIns();
                        AddInstruction(GetFrame, divide);
                        DivIns();

                        AddInstruction(GetFrame, startindex + 1);
                        AddInstruction(GetFrame, startindex + 2);
                        MultIns();
                        AddInstruction(GetFrame, startindex);
                        AddInstruction(GetFrame, startindex + 3);

                        MultIns();
                        SubIns();
                        AddInstruction(GetFrame, divide);
                        DivIns();

                        AddInstruction(PushInt, 2);
                        parseExpression(bOp->getLHS(), true);
                        AddInstruction(FromStack);
                    }
                    goto CheckAssignL2R;
                    default:
                        Throw("Unsupported binary operator \"" + bOp->getOpcodeStr().str() + "\" for Complex data type", TheRewriter, bOp->getOperatorLoc());
                        break;
                    CheckAssignL2R:
                        if (isLtoRValue)
                        {
                            AddInstruction(PushInt, 2);
                            parseExpression(bOp->getLHS(), true);
                            AddInstruction(ToStack);
                        }
                        break;
                    }
#undef AddIns
#undef SubIns
#undef MultIns
#undef DivIns
                    LocalVariables.removeLevel();
                    return true;
                }
                else
                {
                    Throw("Complex binary operations can only be done in functions");
                }

            }


            auto OpAssign = [&](OpcodeKind opcode, OpcodeKind floatVar = (OpcodeKind)-1)
            {
                if (bOp->getType()->isRealFloatingType() && floatVar == (OpcodeKind)-1)
                {
                    Throw("Unsuppored binary operation '" + bOp->getOpcodeStr().str() + "' on floating point data type.", TheRewriter, bOp->getSourceRange());
                }
                bool pointerSet = true;
                if (isa<DeclRefExpr>(bOp->getLHS()))
                {
                    const DeclRefExpr* dRef = cast<DeclRefExpr>(bOp->getLHS());
                    if (isa<VarDecl>(dRef->getFoundDecl()))
                    {
                        pointerSet = false;
                        parseExpression(bOp->getLHS(), false, true);
                    }
                }
                if (pointerSet)
                {
                    parseExpression(bOp->getLHS(), true, false);
                    AddInstruction(Dup);
                    AddInstruction(PGet);
                }
                clang::Expr::EvalResult intRes;
                if (bOp->getRHS()->EvaluateAsInt(intRes, context))
                {
                    int64_t val = intRes.Val.getInt().getSExtValue();
                    if (isa<clang::PointerType>(bOp->getLHS()->getType()))
                    {
                        const clang::Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();
                        AddInstruction(PushInt, val * getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr));
                        if (pointerSet)
                        {
                            AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
                            AddInstruction(PeekSet);
                            AddInstructionCondition(isLtoRValue, PGet, Drop);
                        }
                        else
                        {
                            AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
                            if (isLtoRValue)
                            {
                                AddInstruction(Dup);
                            }
                            parseExpression(bOp->getLHS(), false, false, false, true);
                        }
                    }
                    else
                    {
                        AddInstruction(PushInt, val);
                        if (pointerSet)
                        {
                            AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
                            AddInstruction(PeekSet);
                            AddInstructionCondition(isLtoRValue, PGet, Drop);
                        }
                        else
                        {
                            AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
                            if (bOp->getLHS()->getType()->isBooleanType())
                                AddInstruction(IsNotZero);
                            if (isLtoRValue)
                            {
                                AddInstruction(Dup);
                            }
                            parseExpression(bOp->getLHS(), false, false, false, true);
                        }
                    }
                }
                else
                {
                    parseExpression(bOp->getRHS(), false, true);
                    if (isa<clang::PointerType>(bOp->getLHS()->getType()))
                    {
                        const clang::Type* pTypePtr = bOp->getType().getTypePtr()->getPointeeType().getTypePtr();
                        AddInstruction(MultImm, getSizeFromBytes(getSizeOfType(pTypePtr)) * MultValue(pTypePtr));
                    }

                    if (pointerSet)
                    {
                        AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
                        AddInstruction(PeekSet);
                        AddInstructionCondition(isLtoRValue, PGet, Drop);
                    }
                    else
                    {
                        AddFloatingOpCheck(bOp->getType()->isFloatingType(), opcode, floatVar);
                        if (bOp->getLHS()->getType()->isBooleanType())
                            AddInstruction(IsNotZero);
                        if (isLtoRValue)
                        {
                            AddInstruction(Dup);
                        }
                        parseExpression(bOp->getLHS(), false, false, false, true);
                    }
                }

            };

            switch (op)
            {
            case BO_SubAssign: OpAssign(OK_Sub, OK_FSub); break;
            case BO_AddAssign: OpAssign(OK_Add, OK_FAdd); break;
            case BO_DivAssign:  OpAssign(OK_Div, OK_FDiv); break;
            case BO_MulAssign:  OpAssign(OK_Mult, OK_FMult); break;
            case BO_OrAssign:  OpAssign(OK_Or); break;
            case BO_AndAssign:  OpAssign(OK_And); break;
            case BO_RemAssign:  OpAssign(OK_Mod); break;
            case BO_XorAssign:  OpAssign(OK_Xor); break;
            case BO_ShlAssign:	OpAssign(OK_ShiftLeft); break;
            case BO_ShrAssign: OpAssign(OK_ShiftRight); break;
            default:
            {
                if (isLtoRValue)
                {
                    bool isLeftPtr = bOp->getLHS()->getType().getTypePtr()->isAnyPointerType();
                    bool isRightPtr = bOp->getRHS()->getType().getTypePtr()->isAnyPointerType();

                    //c allows same type pointer to pointer subtraction to obtain the logical difference. 
                    if (isLeftPtr && isRightPtr)
                    {
                        parseExpression(bOp->getLHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);
                        parseExpression(bOp->getRHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);

                        if (op == BO_Sub)
                        {
                            const clang::Type* pTypePtr = bOp->getLHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
                            int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
                            int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

                            AddInstructionCondition(bOp->getLHS()->getType()->isFloatingType(), FSub, Sub);

                            if (pSize > 1)
                            {
                                AddInstruction(PushInt, pSize);
                                AddInstruction(Div);
                            }
                            return -1;
                        }
                    }
                    else if (isLeftPtr)
                    {
                        //we need to parse left as an addr if its an array else its a pointer val
                        parseExpression(bOp->getLHS(), bOp->getLHS()->getType().getTypePtr()->isArrayType(), true);
                        parseExpression(bOp->getRHS(), false, true);

                        if (op == BO_Add || op == BO_Sub)
                        {
                            const clang::Type* pTypePtr = bOp->getLHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
                            int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
                            int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;
                            AddInstructionConditionally(pSize > 1, MultImm, pSize);
                        }
                    }
                    else if (isRightPtr)
                    {
                        //we need to parse right as an addr if its an array else its a pointer val
                        parseExpression(bOp->getLHS(), false, true);

                        if (op == BO_Add || op == BO_Sub)
                        {
                            const clang::Type* pTypePtr = bOp->getRHS()->getType().getTypePtr()->getPointeeType().getTypePtr();
                            int pMultValue = pTypePtr->isCharType() ? 1 : (pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || pTypePtr->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort)) ? 2 : stackWidth;
                            int pSize = getSizeFromBytes(getSizeOfType(pTypePtr)) * pMultValue;

                            AddInstructionConditionally(pSize > 1, MultImm, pSize);
                        }

                        parseExpression(bOp->getRHS(), bOp->getRHS()->getType().getTypePtr()->isArrayType(), true);
                    }
                    else
                    {
                        //no pointer operations
                        parseExpression(bOp->getLHS(), false, true);
                        parseExpression(bOp->getRHS(), false, true);
                    }

                    if (bOp->getLHS()->getType()->isFloatingType())
                    {
                        switch (op)
                        {
                        case BO_EQ: AddInstruction(FCmpEq); break;
                        case BO_Mul: AddInstruction(FMult); break;
                        case BO_Div:
                        {
                            bool isZeroDiv;
                            AddInstruction(FDiv, &isZeroDiv);
                            if (isZeroDiv)
                            {
                                Warn("Zero division error detected", TheRewriter, bOp->getRHS()->getSourceRange());//just warn the user of the undefined behaviour
                            }
                        }
                        break;
                        case BO_Sub:  AddInstruction(FSub); break;
                        case BO_LT: AddInstruction(FCmpLt); break;
                        case BO_GT: AddInstruction(FCmpGt); break;
                        case BO_GE: AddInstruction(FCmpGe); break;
                        case BO_LE: AddInstruction(FCmpLe); break;
                        case BO_NE: AddInstruction(FCmpNe); break;
                        case BO_Add: AddInstruction(FAdd); break;

                        default:
                            Throw("Unimplemented binary floating op " + bOp->getOpcodeStr().str(), TheRewriter, bOp->getExprLoc());
                        }
                    }
                    else
                    {
                        switch (op)
                        {
                        case BO_EQ: AddInstruction(CmpEq); break;
                        case BO_Mul: AddInstruction(Mult); break;
                        case BO_Div:
                        {
                            bool isZeroDiv;
                            AddInstruction(Div, &isZeroDiv);
                            if (isZeroDiv)
                            {
                                Warn("Zero division error detected", TheRewriter, bOp->getRHS()->getSourceRange());//just warn the user of the undefined behaviour
                            }
                        } break;
                        case BO_Rem: AddInstruction(Mod); break;
                        case BO_Sub: AddInstruction(Sub); break;
                        case BO_LT: AddInstruction(CmpLt); break;
                        case BO_GT: AddInstruction(CmpGt); break;
                        case BO_GE: AddInstruction(CmpGe); break;
                        case BO_LE: AddInstruction(CmpLe); break;
                        case BO_NE: AddInstruction(CmpNe); break;
                        case BO_And: AddInstruction(And); break;
                        case BO_Xor: AddInstruction(Xor); break;
                        case BO_Add: AddInstruction(Add); break;
                        case BO_Or: AddInstruction(Or); break;
                        case BO_Shl: AddInstruction(ShiftLeft); break;
                        case BO_Shr: AddInstruction(ShiftRight); break;
                        default:
                            Throw("Unimplemented binary op " + bOp->getOpcodeStr().str(), TheRewriter, bOp->getExprLoc());
                        }
                    }
                }
                else
                {
                    parseExpression(bOp->getLHS());
                    parseExpression(bOp->getRHS());
                    Warn("Unused operator \"" + bOp->getOpcodeStr().str() + "\"", TheRewriter, bOp->getOperatorLoc());
                }
            }

            }
        }
        else if (isa<MemberExpr>(e))
        {
            const MemberExpr* E = cast<const MemberExpr>(e);
            NamedDecl* ND = E->getMemberDecl();
            Expr* BaseExpr = E->getBase();
            const clang::Type* type = E->getType().getTypePtr();

            int typeSize = getSizeFromBytes(getSizeOfType(type));

            //AddComment(to_string(isLtoRValue) + to_string(isAddr) + to_string(typeSize) + to_string(isArrToPtrDecay));

            if ((isLtoRValue || !isAddr) && typeSize > 1 && !isArrToPtrDecay)
            {
                AddInstructionComment(PushInt, "Type Size (member expr) " +
                    to_string(isLtoRValue) + " " +
                    to_string(isAddr) + " " +
                    to_string(isArrToPtrDecay) + " " +
                    to_string(isAssign), typeSize);
            }

            if (E->isArrow())
                parseExpression(BaseExpr, false, true);
            else
                parseExpression(BaseExpr, true);

            int offset = 0;
            size_t currentBitFieldSize = 0;

            BitfieldData selectedBitField;

            if (auto* Field = dyn_cast<FieldDecl>(ND))
            {
                const RecordDecl* record = Field->getParent();
                if (record->isUnion())
                {
                    for (const FieldDecl* CS : record->fields())
                    {
                        if (CS == Field)
                        {
                            if (CS->isBitField())
                            {
                                selectedBitField.width = checkBitFieldWidth(CS);
                                selectedBitField.offset = 0;
                            }
                            break;
                        }
                    }
                }
                else
                {
                    auto IncCurrentBitSize = [&]() -> void
                    {
                        TEST(currentBitFieldSize <= 32, "Bit size too big", TheRewriter, record->getSourceRange());

                        offset += 4;
                        currentBitFieldSize = 0;
                    };

                    for (const FieldDecl* CS : record->fields())
                    {
                        if (CS == Field)
                        {
                            if (CS->isBitField())
                            {
                                selectedBitField.width = checkBitFieldWidth(CS);

                                if (currentBitFieldSize + selectedBitField.width <= 32)
                                {
                                    selectedBitField.offset = currentBitFieldSize;
                                    currentBitFieldSize += selectedBitField.width;
                                }
                                else
                                {
                                    IncCurrentBitSize();
                                    selectedBitField.offset = currentBitFieldSize;
                                }


                                currentBitFieldSize = 0;//clean up currentBitFieldSize for error detection
                            }
                            else if (currentBitFieldSize)
                                IncCurrentBitSize();

                            break;
                        }

                        if (CS->isBitField())
                        {
                            uint32_t bsize = checkBitFieldWidth(CS);
                            if (currentBitFieldSize + bsize <= 32)
                                currentBitFieldSize += bsize;
                            else
                            {
                                IncCurrentBitSize();
                                currentBitFieldSize += bsize;
                            }


                            continue;
                        }
                        else if (currentBitFieldSize)
                            IncCurrentBitSize();

                        const clang::Type* type = CS->getType().getTypePtr();
                        int temp = getSizeOfType(type);
                        offset += max(temp, stackWidth);
                    }

                    TEST(currentBitFieldSize == 0, "Bitfield data was not calculated", TheRewriter, record->getSourceRange());

                }
            }

            string comment = "." + ND->getName().str();

            if (selectedBitField.width)
                comment += " Bit Width: " + to_string(selectedBitField.width) + " Bit Index: " + to_string(selectedBitField.offset);

            AddInstructionComment(GetImmP, comment, getSizeFromBytes(offset));

            if (isArrToPtrDecay)
                return 1;
            else if (isLtoRValue)
            {
                if (selectedBitField.width == 1)
                {
                    TEST(typeSize == 1, "size larger then size for pget (IsBitSet)", TheRewriter, ND->getSourceRange());
                    AddInstruction(PGet);
                    AddInstruction(IsBitSet, (uint8_t)selectedBitField.offset);
                }
                else if (selectedBitField.width)
                {
                    TEST(typeSize == 1, "size larger then size for pget (GetBitField)", TheRewriter, ND->getSourceRange());
                    AddInstruction(PGet);
                    AddInstruction(GetBitField, selectedBitField.offset, selectedBitField.width, scriptData.getBuildType(), scriptData.getBuildPlatform());
                }
                else
                {
                    AddInstructionCondition(typeSize > 1, ToStack, PGet);
                }
            }
            else if (isAddr)
                return 1;
            else
            {
                if (selectedBitField.width == 1)
                {
                    LocalVariables.addLevel();
                    size_t index = LocalVariables.addDecl("__bitset_set_temp_ptr", 1);
                    AddInstruction(SetBitStack, (uint8_t)selectedBitField.offset, index);
                    LocalVariables.removeLevel();

                }
                else if (selectedBitField.width)
                {
                    LocalVariables.addLevel();
                    size_t index[2] = { LocalVariables.addDecl("__bitset_set_temp_ptr", 1), LocalVariables.addDecl("__bitset_set_temp_val", 1) };
                    AddInstruction(SetBitField, selectedBitField.offset, selectedBitField.width, index, scriptData.getBuildType(), scriptData.getBuildPlatform());
                    LocalVariables.removeLevel();

                }
                else
                {
                    AddInstructionCondition(typeSize > 1, FromStack, PSet);
                }
            }
            return 1;
        }
        else if (isa<InitListExpr>(e))
        {
            //{ 1, 3, 7 }; support
            if (isLtoRValue)
            {
                const InitListExpr* I = cast<const InitListExpr>(e);
                int typeSize = getSizeOfType(I->getType().getTypePtr());

                if (I->getType()->isArrayType())
                {
                    switch (getSizeOfType(I->getType()->getArrayElementTypeNoTypeQual()))
                    {
                    case 1:
                    {
                        int initCount = I->getNumInits();
                        int i;
                        for (i = 0; i < initCount; i += 4)
                        {
                            clang::Expr::EvalResult res;
                            int evaluated[4];
                            const Expr* inits[4];
                            bool allconst = true;
                            bool succ[4];
                            for (int j = 0; j < 4; j++)
                            {
                                if (i + j < initCount)
                                {
                                    inits[j] = I->getInit(i + j);
                                    if ((succ[j] = inits[j]->EvaluateAsInt(res, context)))
                                    {
                                        evaluated[j] = res.Val.getInt().getSExtValue() & 0xFF;
                                    }
                                    else
                                    {
                                        allconst = false;
                                    }
                                }
                                else
                                {
                                    succ[j] = true;
                                    evaluated[j] = 0;
                                }

                            }
                            if (allconst)
                            {
                                int val = (evaluated[0] << 24) | (evaluated[1] << 16) | (evaluated[2] << 8) | (evaluated[3]);
                                AddInstruction(PushInt, val);
                            }
                            else
                            {
                                if (succ[0])
                                {
                                    AddInstruction(PushInt, evaluated[0] << 24);

                                }
                                else
                                {
                                    parseExpression(I->getInit(i), false, true);
                                    AddInstruction(PushInt, 255);
                                    AddInstruction(And);
                                    AddInstruction(ShiftLeft, 24);

                                }
                                for (int j = 1; j < 4; j++)
                                {
                                    if (i + j >= initCount)
                                        break;
                                    if (succ[j])
                                    {
                                        AddInstruction(PushInt, evaluated[j] << ((3 - j) << 3));
                                        AddInstruction(Or);
                                    }
                                    else
                                    {
                                        parseExpression(I->getInit(i + j), false, true);
                                        AddInstruction(PushInt, 255);
                                        AddInstruction(And);
                                        AddInstructionConditionally(j != 3, ShiftLeft, (3 - j) << 3);
                                        AddInstruction(Or);
                                    }

                                }
                            }
                        }
                        int size = getSizeOfType(I->getType().getTypePtr());
                        while (i < size)
                        {
                            AddInstruction(PushInt, 0);
                            i += stackWidth;
                        }
                    }
                    return 1;
                    case 2:
                    {
                        int initCount = I->getNumInits();
                        int i;
                        for (i = 0; i < initCount; i += 2)
                        {
                            clang::Expr::EvalResult res;
                            int evaluated[2];
                            const Expr* inits[2];
                            bool allconst = true;
                            bool succ[2];
                            for (int j = 0; j < 2; j++)
                            {
                                if (i + j < initCount)
                                {
                                    inits[j] = I->getInit(i + j);
                                    if ((succ[j] = inits[j]->EvaluateAsInt(res, context)))
                                    {
                                        evaluated[j] = res.Val.getInt().getSExtValue() & 0xFFFF;
                                    }
                                    else
                                    {
                                        allconst = false;
                                    }
                                }
                                else
                                {
                                    succ[j] = true;
                                    evaluated[j] = 0;
                                }

                            }
                            if (allconst)
                            {
                                int val = (evaluated[0] << 16) | (evaluated[1]);
                                AddInstruction(PushInt, val);
                            }
                            else
                            {
                                if (succ[0])
                                {
                                    AddInstruction(PushInt, evaluated[0] << 16);

                                }
                                else
                                {
                                    parseExpression(I->getInit(i), false, true);
                                    AddInstruction(PushInt, 65535);
                                    AddInstruction(And);
                                    AddInstruction(ShiftLeft, 16);
                                }
                                if (i + 1 < initCount)
                                {
                                    if (succ[1])
                                    {
                                        AddInstruction(PushInt, evaluated[1]);
                                        AddInstruction(Or);
                                    }
                                    else
                                    {
                                        parseExpression(I->getInit(i + 1), false, true);
                                        AddInstruction(PushInt, 65535);
                                        AddInstruction(And);
                                        AddInstruction(Or);
                                    }
                                }
                            }
                        }
                        int size = getSizeOfType(I->getType().getTypePtr());
                        int curSize = getSizeFromBytes(i * 2) * stackWidth;
                        while (curSize < size)
                        {
                            AddInstruction(PushInt, 0);
                            curSize += stackWidth;
                        }
                    }
                    return 1;
                    }
                }

                else if (I->getType()->isStructureType())
                {
                    const RecordType* record = I->getType()->getAsStructureType();


                    if (RecordDecl* rd = record->getDecl())
                    {
                        queue<QueuedBF> QueuedBitfields;

                        uint32_t offset = 0;
                        uint32_t currentRes = 0;
                        uint32_t size = 0;
                        uint32_t currentBitFieldSize = 0;
                        auto IncCurrentBitSize = [&]() -> void
                        {
                            TEST(currentBitFieldSize <= 32, "Bit size too big", TheRewriter, rd->getSourceRange());
                            AddInstruction(PushInt, currentRes);
                            while (QueuedBitfields.size())
                            {
                                parseExpression(QueuedBitfields.front().Expr, false, true);
                                AddInstruction(AddBitField, QueuedBitfields.front().Data.offset, QueuedBitfields.front().Data.width);
                                QueuedBitfields.pop();
                            }
                            offset += 4;
                            currentBitFieldSize = 0;
                            currentRes = 0;
                        };

                        uint32_t i = 0;
                        for (const FieldDecl* CS : rd->fields())
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
                                const Expr* init = I->getInit(i);
                                parseExpression(init, false, true);

                                i++;
                            }
                            else
                                break;
                        }
                        if (currentBitFieldSize)
                            IncCurrentBitSize();
                        while (offset < size)
                        {
                            AddInstruction(PushInt, 0);
                            offset += stackWidth;
                        }
                        //assert(offset <= typeSize && "InitList bigger then storage size");
                        return 1;
                    }

                }
                else if (I->getType()->isUnionType())
                {
                }




                int curSize = 0;
                for (unsigned int i = 0; i < I->getNumInits(); i++)
                {

                    const Expr* init = I->getInit(i);
                    curSize += stackWidth * getSizeFromBytes(getSizeOfType(init->getType().getTypePtr()));
                    parseExpression(init, false, true);
                }
                while (curSize < typeSize)
                {
                    AddInstruction(PushInt, 0);
                    curSize += stackWidth;
                }
                //assert(curSize <= typeSize && "InitList bigger then storage size");
            }
            return 1;
        }
        else if (isa<ImplicitValueInitExpr>(e))
        {
            const ImplicitValueInitExpr* im = cast<const ImplicitValueInitExpr>(e);
            uint32_t size = getSizeFromBytes(getSizeOfType(im->getType().getTypePtr()));
            for (uint32_t i = 0; i < size; i++)
            {
                AddInstruction(PushInt, 0);
            }
            if (!isLtoRValue)
            {
                for (uint32_t i = 0; i < size; i++)
                {
                    AddInstructionComment(Drop, "Unused ImplicitValueInitExpr");
                }
            }
        }
        else if (isa<UnaryExprOrTypeTraitExpr>(e))
        {

            const UnaryExprOrTypeTraitExpr* ueTrait = cast<const UnaryExprOrTypeTraitExpr>(e);
            //out << ueTrait->getKind() << endl;
            switch (ueTrait->getKind())
            {
            case UnaryExprOrTypeTrait::UETT_SizeOf:
            {
                int size = 0;

                if (ueTrait->isArgumentType())
                    size = getSizeOfType(ueTrait->getArgumentType().getTypePtr());
                else//size = getSizeOfType(ueTrait->getArgumentExpr()->getType().getTypePtr());
                    size = getSizeOfType(ueTrait->getArgumentExpr()->getType().getTypePtr());
                //size = context->getTypeInfoDataSizeInChars(ueTrait->getArgumentExpr()->getType()).first.getQuantity();



                //Pause("SIZE: " + to_string(size) + "\r\n");
                AddInstructionConditionally(isLtoRValue, PushInt, size);

            }
            break;
            case UnaryExprOrTypeTrait::UETT_JenkinsHash:
            {
                if (const Expr* arg = ueTrait->getArgumentExpr()->IgnoreParens())
                {
                    if (isa<clang::StringLiteral>(arg))
                    {
                        string str = cast<clang::StringLiteral>(arg)->getString().str();
                        AddInstructionComment(PushInt, "Joaat(\"" + str + "\")", Utils::Hashing::Joaat(str.c_str()));
                        if (!isLtoRValue)
                        {
                            AddInstructionComment(Drop, "unused jenkins hash");
                        }
                        break;
                    }
                    Throw("Jenkins Method called with unsupported arg type, please use a StringLiteral argument", TheRewriter, arg->getBeginLoc());
                    break;
                }
            }
            Throw("Jenkins Method called without any argument, please use a StringLiteral argument", TheRewriter, ueTrait->getBeginLoc());
            break;
            default:
                Throw("Unsupported UnaryExprOrTypeTrait Type:" + to_string(ueTrait->getKind()), TheRewriter, ueTrait->getBeginLoc());
                break;
            }
        }
        else if (isa<ConditionalOperator>(e))
        {
            static int condCounter = 0;
            const string currentCounter = to_string(condCounter++);
            const ConditionalOperator* cond = cast<const ConditionalOperator>(e);
            auto condition = cond->getCond();
            Expr::EvalResult eResult;
            bool bValue = false, ignoreCondition = false;
            if (condition->EvaluateAsRValue(eResult, context) && eResult.Val.isInt())
            {
                bValue = eResult.Val.getInt().getBoolValue();
                if (!isa<IntegerLiteral>(condition->IgnoreParenCasts()))
                    Warn("Conditional operator always evaluates to " + (bValue ? string("true") : string("false")), TheRewriter, condition->getSourceRange());
                ignoreCondition = Option_OptimizationLevel > OptimisationLevel::OL_None && !condition->HasSideEffects(context, true);
            }
            if (ignoreCondition)
            {
                parseExpression(bValue ? cond->getLHS() : cond->getRHS(), isAddr, isLtoRValue);
            }
            else
            {
                parseCondition(condition, "__cond_true_" + currentCounter, "__cond_false_" + currentCounter);
                AddJumpInlineCheckStr(Label, "__cond_true_" + currentCounter);

                parseExpression(cond->getLHS(), isAddr, isLtoRValue);
                AddJumpInlineCheckStr(Jump, "__cond_end_" + currentCounter);

                AddJumpInlineCheckStr(Label, "__cond_false_" + currentCounter);
                parseExpression(cond->getRHS(), isAddr, isLtoRValue);
                AddJumpInlineCheckStr(Label, "__cond_end_" + currentCounter);
            }
        }
        else if (isa<ImaginaryLiteral>(e))
        {
            Warn("Imaginary literals aren't supported", TheRewriter, e->getExprLoc());
            /*const ImaginaryLiteral *literal = cast<ImaginaryLiteral>(e);
            const Expr* item = literal->getSubExpr();
            if (isa<FloatingLiteral>(item))
            {
            Warn("Temp");
            }
            else if (isa<IntegerLiteral>(item))
            {
            Warn("Temp");
            }
            out << "imaginary_literal_push" << endl;*/

        }
        else if (isa<GenericSelectionExpr>(e))
        {
            const GenericSelectionExpr* gse = cast<GenericSelectionExpr>(e);
            parseExpression(gse->getResultExpr(), isAddr, isLtoRValue);
        }
        else if (isa<BinaryConditionalOperator>(e))
        {
            static int binCondCounter = 0;
            const string currentCounter = to_string(binCondCounter++);
            const BinaryConditionalOperator* bco = cast<BinaryConditionalOperator>(e);

            //out << "COND:" << endl;
            parseExpression(bco->getCond(), false, true);
            AddInstruction(Dup);
            AddJumpInlineCheckStr(JumpFalse, "__bin_false_" + currentCounter);
            if (!isLtoRValue)
            {
                AddInstruction(Drop);//drop the value if not LtoR
            }
            AddJumpInlineCheckStr(Jump, "__bin_end_" + currentCounter);

            AddJumpInlineCheckStr(Label, "__bin_false_" + currentCounter);
            AddInstruction(Drop);
            parseExpression(bco->getFalseExpr(), false, isLtoRValue);//LtoR should handle the drop
            AddJumpInlineCheckStr(Label, "__bin_end_" + currentCounter);
        }
        else if (isa<OpaqueValueExpr>(e))
        {
            const OpaqueValueExpr* ov = cast<OpaqueValueExpr>(e);
            parseExpression(ov->getSourceExpr(), isAddr, isLtoRValue);
        }
        else if (isa<AddrLabelExpr>(e))
        {
            if (isLtoRValue)
            {
                auto addrOf = cast<AddrLabelExpr>(e);
                AddJumpInlineCheckStr(LabelLoc, addrOf->getLabel()->getNameAsString());
            }
        }
        else
            Throw("Unimplemented expression " + string(e->getStmtClassName()), TheRewriter, e->getExprLoc());

        return -1;
    }

    bool ASTVisitorLocal::parseArraySubscriptExpr(const Expr* e, bool addrOf, bool LValueToRValue, bool isArrToPtrDecay)
    {
        const ArraySubscriptExpr* arr = cast<const ArraySubscriptExpr>(e);
        const Expr* base = arr->getBase();
        const Expr* index = arr->getIdx();

        clang::Expr::EvalResult evalIndex;
        bool isCst = index->EvaluateAsInt(evalIndex, context);

        const DeclRefExpr* declRef = getDeclRefExpr(base);
        const clang::Type* type = base->getType().getTypePtr();//declRef->getType().getTypePtr()->getArrayElementTypeNoTypeQual();

        if (type == NULL)
        {
            type = declRef->getType().getTypePtr();
        }
        if (declRef)
        {
            declRef->getType();
        }
        if (type->isPointerType())
            type = type->getPointeeType().getTypePtr();


        if (!addrOf && !LValueToRValue && !isArrToPtrDecay)
        {
            //1 byte indexing
            if (type->isCharType())
            {
                //mod for narrowing conversion
                AddInstruction(SetConv, scriptData, 1);
                parseExpression(base, base->getType().getTypePtr()->isArrayType(), true);

                if (isCst)
                {
                    int iRes = evalIndex.Val.getInt().getSExtValue();
                    if (iRes != 0)
                    {
                        AddInstruction(AddImm, iRes);
                    }
                }
                else
                {
                    parseExpression(index, false, true);
                    AddInstruction(Add);
                }

                AddInstruction(PGet);
                AddInstruction(PushInt, 0xFFFFFF);
                AddInstruction(And);
                AddInstruction(Or);
            }
            //2 byte indexing
            else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
            {
                //mod for narrowing conversion

                AddInstruction(SetConv, scriptData, 2);
                parseExpression(base, base->getType().getTypePtr()->isArrayType(), true);
                if (isCst)
                {
                    int iRes = evalIndex.Val.getInt().getSExtValue();
                    if (iRes != 0)
                    {
                        AddInstruction(AddImm, iRes * 2);
                    }
                }
                else
                {
                    parseExpression(index, false, true);
                    AddInstruction(MultImm, 2);
                    AddInstruction(Add);
                }
                AddInstruction(PGet);
                AddInstruction(PushInt, 0xFFFF);
                AddInstruction(And);
                AddInstruction(Or);
            }
        }
        else if (LValueToRValue && !addrOf && !isArrToPtrDecay)
        {
            int bSize = getSizeFromBytes(getSizeOfType(type));
            if (bSize > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
            {
                AddInstructionComment(PushInt, "Type Size (array)", bSize);
            }
        }

        parseExpression(base, base->getType().getTypePtr()->isArrayType(), true);


        if (LValueToRValue && !addrOf && !isArrToPtrDecay)
        {
            if (isCst)
            {
                int iRes = evalIndex.Val.getInt().getSExtValue();
                if (iRes != 0)
                {
                    int size = getSizeOfType(type);
                    if (size % scriptData.getStackWidth() == 0)
                    {
                        int multVal = size / scriptData.getStackWidth();
                        int addval = iRes * multVal;
                        if (addval > 0 && addval <= 0xFFFF)
                        {
                            AddInstruction(GetImmP, addval);
                        }
                        else
                        {
                            AddInstruction(PushInt, addval);
                            AddInstruction(GetImmPStack);
                        }
                    }
                    else
                    {
                        AddInstruction(AddImm, iRes * size);
                    }
                }
            }
            else
            {
                parseExpression(index, false, true);
                int size = getSizeOfType(type);
                if (size % scriptData.getStackWidth() == 0)
                {
                    AddInstructionConditionally(size > 1, MultImm, size / scriptData.getStackWidth())
                        AddInstructionConditionally(size > 1, GetImmPStack);
                }
                else
                {
                    AddInstructionConditionally(size > 1, MultImm, size);
                    AddInstruction(Add);
                }
            }
            if (getSizeFromBytes(getSizeOfType(type)) > 1 && (type->isStructureType() || type->isUnionType() || type->isAnyComplexType()))
            {
                AddInstructionComment(ToStack, "GetArray");
            }
            else
            {
                AddInstruction(PGet);
                //1 byte indexing
                if (type->isCharType())
                {
                    AddInstruction(GetConv, scriptData, 1, e->getType()->isSignedIntegerType());
                }
                //2 byte indexing
                else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
                {
                    AddInstruction(GetConv, scriptData, 2, e->getType()->isSignedIntegerType());
                }

            }

        }
        else if (addrOf || isArrToPtrDecay)
        {
            int size = getSizeOfType(type);
            if (type->isArrayType())
                size = getSizeFromBytes(size) * stackWidth;
            if (isCst)
            {
                int iRes = evalIndex.Val.getInt().getSExtValue();
                if (iRes != 0)
                {
                    if (size % scriptData.getStackWidth() == 0)
                    {
                        int multVal = size / scriptData.getStackWidth();
                        int addval = iRes * multVal;
                        if (addval > 0 && addval <= 0xFFFF)
                        {
                            AddInstruction(GetImmP, addval);
                        }
                        else
                        {
                            AddInstruction(PushInt, addval);
                            AddInstruction(GetImmPStack);
                        }
                    }
                    else
                    {
                        AddInstruction(AddImm, iRes * size);
                    }
                }
            }
            else
            {
                parseExpression(index, false, true);
                int size = getSizeOfType(type);
                if (size % scriptData.getStackWidth() == 0)
                {
                    AddInstructionConditionally(size > 1, MultImm, size / scriptData.getStackWidth())
                        AddInstructionConditionallyComment(size > 1, GetImmPStack, "GetArrayP");
                }
                else
                {
                    AddInstructionConditionally(size > 1, MultImm, size);
                    AddInstructionComment(Add, "GetArrayP");
                }
            }
        }
        else
        {
            if (isCst)
            {
                int iRes = evalIndex.Val.getInt().getSExtValue();
                if (iRes != 0)
                {
                    int size = getSizeOfType(type);
                    if (size % scriptData.getStackWidth() == 0)
                    {
                        int multVal = size / scriptData.getStackWidth();
                        int addval = iRes * multVal;
                        if (addval > 0 && addval <= 0xFFFF)
                        {
                            AddInstruction(GetImmP, addval);
                        }
                        else
                        {
                            AddInstruction(PushInt, addval);
                            AddInstruction(GetImmPStack);
                        }
                    }
                    else
                    {
                        AddInstruction(AddImm, iRes * size);
                    }

                }
            }
            else
            {
                parseExpression(index, false, true);
                int size = getSizeOfType(type);
                if (size % scriptData.getStackWidth() == 0)
                {
                    AddInstructionConditionally(size > 1, MultImm, size / scriptData.getStackWidth())
                        AddInstructionConditionally(size > 1, GetImmPStack);
                }
                else
                {
                    AddInstructionConditionally(size > 1, MultImm, size);
                    AddInstruction(Add);
                }

            }
            AddInstructionComment(PSet, "SetArray");
        }


        return true;
    }

    bool ASTVisitorLocal::VisitFunctionDecl(FunctionDecl* f)
    {
        // Only function definitions (with bodies), not declarations.
        //int funcNum = 0;
        if (f->hasBody())
        {
            if (f->hasAttr<NativeFuncAttr>())
            {
                Throw("Native function attribute cannot be used on functions which have a body declared", TheRewriter, f->getAttr<NativeFuncAttr>()->getRange());
            }
            else if (f->hasAttr<IntrinsicFuncAttr>())
            {
                Throw("Intrinsic function attribute cannot be used on functions which have a body declared", TheRewriter, f->getAttr<IntrinsicFuncAttr>()->getRange());
            }


            if (isa<CXXConstructorDecl>(f))
                return true;

            Stmt* FuncBody = f->getBody();

            //if (f->getStorageClass() == SC_Static)


            int32_t paramSize = 0;
            for (uint32_t i = 0; i < f->getNumParams(); i++)
                paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));

            if (isa<CXXMethodDecl>(f))
                paramSize++;

            if (f->isVariadic())
                paramSize += 3;


            FunctionData* func = scriptData.createFunction(getNameForFunc(f), paramSize, getSizeFromBytes(getSizeOfType(f->getReturnType().getTypePtr())), true);
            if (f->hasAttr<MinSizeAttr>())
            {
                func->setDontObfuscate();
            }
            auto identifier = f->getIdentifier();
            if (identifier && identifier->isStr("main"))//cant use f->isMain as its now freestanding exe
            {
                if (f->isInlined())
                    func->setMainFuncInline();

                scriptData.setMainFunction(func);
            }
            if (f->hasAttr<UnsafeFuncAttr>())
            {
                func->setUnsafe();
            }

            currFunction = f;
            LocalVariables.reset();
            if (isa<CXXMethodDecl>(f))
                LocalVariables.addDecl("", 1);

            for (uint32_t i = 0; i < f->getNumParams(); i++)
                handleParmVarDecl(f->getParamDecl(i));

            if (f->isVariadic())
            {
                LocalVariables.addDecl("__builtin_va_list", 1);
                LocalVariables.addDecl("__builtin_va_pcount", 1);
                LocalVariables.addDecl("__builtin_va_scount", 1);
            }

            LocalVariables.addDecl("", 2);//base pointer and return address
            parseStatement(FuncBody, "", "");

            if (f->getReturnType().getTypePtr()->isVoidType() && !func->endsWithReturn())
            {
                AddInstruction(Return);
            }
            else if (f->hasImplicitReturnZero() && !func->endsWithReturn())
            {
                AddInstruction(PushInt, 0);
                AddInstruction(Return);
            }

            //Throw(f->getNameAsString() + ": not all control paths return a value", TheRewriter, f->getLocEnd());
            //uint32_t FunctionStackCount = LocalVariables.maxIndex - (isa<CXXMethodDecl>(f) ? 1 : 0) - paramSize;

            if (LocalVariables.getMaxIndex() > 65536)
                Throw("Function \"" + f->getNameAsString() + "\" has a stack size of " + to_string(LocalVariables.getMaxIndex()) + " when the max is 65536", TheRewriter, f->getBeginLoc());
            else
            {
                func->setStackSize(LocalVariables.getMaxIndex());
            }
            func->setProcessed();

            //	F1, //low: int maxBlockSize = 50, int minBlockSize = 30, bool keepEndReturn = true, bool makeJumpTable = false
            //	F2, //default: int maxBlockSize = 30, int minBlockSize = 15, bool keepEndReturn = false, bool makeJumpTable = false
            //	F3, //high:  int maxBlockSize = 30, int minBlockSize = 15, bool keepEndReturn = false, bool makeJumpTable = true
            //	F4, //very high: int maxBlockSize = 15, int minBlockSize = 5, bool keepEndReturn = false, bool makeJumpTable = true
            //  F5, //max: int maxBlockSize = 5, int minBlockSize = 1, bool keepEndReturn = false, bool makeJumpTable = true

            switch (Option_ObfuscationLevel)
            {
            case obf_none:
            case obf_string: break;
            case obf_low: func->codeLayoutRandomisation(scriptData, 50, 30, true, false); break;
            case obf_default: func->codeLayoutRandomisation(scriptData, 30, 15, false, false); break;
            case obf_high:func->codeLayoutRandomisation(scriptData, 30, 15, false, true); break;
            case obf_veryhigh: func->codeLayoutRandomisation(scriptData, 15, 5, false, true); break;
            case obf_max: func->codeLayoutRandomisation(scriptData, 5, 1, false, true); break;
            default: Throw("Unknown Obfuscation Level: " + to_string(Option_ObfuscationLevel));
            }

            scriptData.clearCurrentFunction();
        }
        else
        {
            if (f->hasAttrs())
            {
                if (f->hasAttr<NativeFuncAttr>() || f->hasAttr<IntrinsicFuncAttr>())
                {
                    return false;
                }

                //tests attributes
                //AttrVec vec = f->getAttrs();
                //for(uint32_t i = 0; i < vec.size(); i++)
                //	cout << vec[i]->getSpelling() << endl;
            }
            int32_t paramSize = 0;
            for (uint32_t i = 0; i < f->getNumParams(); i++)
                paramSize += getSizeFromBytes(getSizeOfType(f->getParamDecl(i)->getType().getTypePtr()));

            if (f->isVariadic())
                paramSize += 3;


            scriptData.createFunction(getNameForFunc(f), paramSize + (isa<CXXMethodDecl>(f) ? 1 : 0), getSizeFromBytes(getSizeOfType(f->getReturnType().getTypePtr())), false, true);


            //cout << "added prototype: " << f->getNameAsString() << endl;
        }

        return true;
    }
#pragma endregion

}