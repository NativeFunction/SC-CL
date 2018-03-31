#include "ClangParsing/GlobalDecls.h"
#include "Utils\Utils.h"

using namespace std;
using namespace clang;
using namespace Utils::System;
using namespace Utils::DataConversion;

namespace SCCL
{
	local_scope LocalVariables;

	string globalDirectory;
	unique_ptr<Script> scriptData = nullptr;
	uint32_t CurrentFileId = 0;
	uint8_t stackWidth = 4;
	Rewriter* rewriter;
    const clang::LangOptions langOptions;
    clang::PrintingPolicy printingPolicy(langOptions);


	#pragma region Global_Size_Functions
	uint32_t checkBitFieldWidth(const FieldDecl* bitField)
	{
		uint32_t width = bitField->getBitWidthValue(bitField->getASTContext());
		if (width > (uint32_t)(stackWidth * 8) - 1)
			Throw("Bitfield width too large", *rewriter, bitField->getSourceRange());
		else if (width == 0)
			Throw("Bitfield width too small", *rewriter, bitField->getSourceRange());
		return width;
	}

	uint32_t getSizeOfType(const Type* type);

	uint32_t getSizeFromBytes(uint64_t bytes)
	{
		uint32_t size = (bytes / stackWidth) + ((bytes % stackWidth) ? 1 : 0);
		return size;
	}

	uint32_t getLiteralSizeOfType(const Type* type)
	{
		if (isa<ConstantArrayType>(type))
		{
			const ConstantArrayType *arrType = cast<const ConstantArrayType>(type);
			return getSizeOfType(type->getArrayElementTypeNoTypeQual()) * (arrType->getSize()).getSExtValue();
		}
		//else if (type->isRecordType() && type->getAsCXXRecordDecl()) {
		//	CXXRecordDecl *recordDecl = type->getAsCXXRecordDecl();
		//	return getSizeOfCXXDecl(recordDecl, true, false);
		//}
		else if (type->isStructureType())
		{
			const RecordType *record = type->getAsStructureType();

			if (RecordDecl *rd = record->getDecl())
			{

				uint32_t size = 0;
				uint32_t currentBitSize = 0;
				for (const auto *CS : rd->fields())
				{
					if (CS->isBitField())
					{
						currentBitSize += checkBitFieldWidth(CS);
						continue;
					}
					else if (currentBitSize)
					{
						size += Utils::Math::CeilDivInt(currentBitSize, 32) * 4;
						currentBitSize = 0;
					}

					const Type* type = CS->getType().getTypePtr();

					size += getSizeOfType(type);
				}
				if (currentBitSize)
				{
					size += Utils::Math::CeilDivInt(currentBitSize, 32) * 4;
					currentBitSize = 0;
				}
				//cout << "struct: " << size << " : " << to_string(getSizeFromBytes((uint64_t)size)) << '\n';

				return size;
			}

		}
		else if (type->isUnionType())
		{
			const RecordType *record = type->getAsUnionType();

			if (RecordDecl *rd = record->getDecl())
			{

				uint32_t size = 0;
				uint32_t currentBitSize = 0;
				for (const auto *CS : rd->fields())
				{
					if (CS->isBitField())
					{
						currentBitSize += checkBitFieldWidth(CS);
						continue;
					}
					else if (currentBitSize)
					{
						uint32_t bitByteSize = Utils::Math::CeilDivInt(currentBitSize, 32) * 4;

						if (bitByteSize > size)
							size = bitByteSize;
						currentBitSize = 0;
					}
					const Type* type = CS->getType().getTypePtr();

					uint32_t sz = getSizeOfType(type);
					if (sz > size)
						size = sz;
				}
				if (currentBitSize)
				{
					uint32_t bitByteSize = Utils::Math::CeilDivInt(currentBitSize, 32) * 4;

					if (bitByteSize > size)
						size = bitByteSize;
					currentBitSize = 0;
				}
				//cout << "union: " << size << " : " << to_string(getSizeFromBytes((uint64_t)size)) << '\n';

				return size;
			}

		}
		else if (type->isAnyComplexType())
			return 2 * stackWidth;
		else if (type->isCharType())
			return 1;
		else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
			return 2;
		else if (type->isIntegerType() || type->isBooleanType() || type->isRealFloatingType() || type->isPointerType())
			return stackWidth;
		else if (type->isVoidType())
			return 0;

		return 0;
	}

	uint32_t getSizeOfType(const Type* type)
	{
		if (isa<ConstantArrayType>(type))
		{
			const ConstantArrayType *arrType = cast<const ConstantArrayType>(type);
			return ((getSizeOfType(type->getArrayElementTypeNoTypeQual()) * (arrType->getSize()).getSExtValue()) + stackWidth - 1) & ~(stackWidth - 1);
		}
		else if (type->isStructureType())
		{
			const RecordType *record = type->getAsStructureType();

			if (RecordDecl *rd = record->getDecl())
			{

				uint32_t size = 0;
				uint32_t currentBitSize = 0;
				auto IncCurrentBitSize = [&] () -> void
				{
					assert(currentBitSize <= 32 && "currentBitSize too big");
					size += 4;
					currentBitSize = 0;
				};

				for (const auto *CS : rd->fields())
				{
					if (CS->isBitField())
					{
						uint32_t bsize = checkBitFieldWidth(CS);
						if (currentBitSize + bsize <= 32)
							currentBitSize += bsize;
						else
						{
							IncCurrentBitSize();
							currentBitSize += bsize;
						}

						continue;
					}
					else if (currentBitSize)
						IncCurrentBitSize();

					const Type* type = CS->getType().getTypePtr();

					size += (getSizeOfType(type) + stackWidth - 1) & ~(stackWidth - 1);
				}
				if (currentBitSize)
					IncCurrentBitSize();


				//cout << "struct: " << size << " : " << to_string(getSizeFromBytes((uint64_t)size)) << '\n';

				return size;
			}

		}
		else if (type->isUnionType())
		{
			const RecordType *record = type->getAsUnionType();

			if (RecordDecl *rd = record->getDecl())
			{

				uint32_t size = 0;
				uint32_t currentBitSize = 0;
				auto IncCurrentBitSize = [&] () -> void
				{
					assert(currentBitSize <= 32 && "currentBitSize too big");
					if (4 > size)
						size = 4;
					currentBitSize = 0;
				};

				for (const auto *CS : rd->fields())
				{
					if (CS->isBitField())
					{
						uint32_t bsize = checkBitFieldWidth(CS);
						if (currentBitSize + bsize <= 32)
							currentBitSize += bsize;
						else
						{
							IncCurrentBitSize();
							currentBitSize += bsize;
						}

						continue;
					}
					else if (currentBitSize)
						IncCurrentBitSize();


					const Type* type = CS->getType().getTypePtr();

					uint32_t sz = (getSizeOfType(type) + stackWidth - 1) & ~(stackWidth - 1);
					if (sz > size)
						size = sz;
				}
				if (currentBitSize)
					IncCurrentBitSize();

				//cout << "union: " << size << " : " << to_string(getSizeFromBytes((uint64_t)size)) << '\n';

				return size;
			}

		}
		else if (type->isCharType())
			return 1;
		else if (type->isSpecificBuiltinType(clang::BuiltinType::Kind::Short) || type->isSpecificBuiltinType(clang::BuiltinType::Kind::UShort))
			return 2;
		else if (type->isIntegerType() || type->isBooleanType() || type->isRealFloatingType() || type->isPointerType())
			return stackWidth;
		else if (type->isVoidType())
			return 0;
		else if (type->isAnyComplexType())
			return 2 * stackWidth;


		return 0;
	}

	bool CheckExprForSizeOf(const Expr* expr, int *outSize)
	{
		if (isa<UnaryExprOrTypeTraitExpr>(expr->IgnoreParens()->IgnoreCasts()))
		{
			const UnaryExprOrTypeTraitExpr *ueTrait = cast<UnaryExprOrTypeTraitExpr>(expr->IgnoreParens()->IgnoreCasts());
			if (ueTrait->getKind() == UETT_SizeOf)
			{
				if (ueTrait->isArgumentType())
					*outSize = getSizeOfType(ueTrait->getArgumentType().getTypePtr());
				else//size = getSizeOfType(ueTrait->getArgumentExpr()->getType().getTypePtr());
					*outSize = getSizeOfType(ueTrait->getArgumentExpr()->getType().getTypePtr());
				return true;
			}
		}
		return false;
	}

	#pragma endregion

	const DeclRefExpr* getDeclRefExpr(const Expr *e)
	{
		if (isa<DeclRefExpr>(e))
		{
			return cast<const DeclRefExpr>(e);
		}
		else
		{
			for (auto *CS : e->clang::Stmt::children())
			{
				if (isa<Expr>(CS))
				{
					return getDeclRefExpr(cast<const Expr>(CS));
				}
			}
		}
		return NULL;
	}
}