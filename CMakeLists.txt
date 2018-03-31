cmake_minimum_required(VERSION 2.8.10)

set(LLVM_LINK_COMPONENTS support)
set(LLVM_USED_LIBS clangTooling clangBasic clangAST)

set(source_list
	"Include/ClangParsing/ASTConsumer.cpp"
	"Include/ClangParsing/ASTFrontendAction.cpp"
	"Include/ClangParsing/ASTVisitorGlobal.cpp"
	"Include/ClangParsing/ASTVisitorLocal.cpp"
	"Include/ClangParsing/CommandLineOptions.cpp"
	"Include/ClangParsing/GlobalDecls.cpp"
	"Include/ClangParsing/Helpers/FunctionData.cpp"
	"Include/ClangParsing/Helpers/Script.cpp"
	"Include/ClangParsing/Helpers/StaticData.cpp"
	"Include/Utils/Utils.cpp"
	"Include/Utils/ClangUtils.cpp"
	"Include/Compiler/Compiler.cpp"
	"Include/Compiler/Opcode.cpp"
	"Include/Crypto/aes256.c"
)

set(header_list
	"Include/ClangParsing/ASTConsumer.h"
	"Include/ClangParsing/ASTFrontendAction.h"
	"Include/ClangParsing/ASTVisitorGlobal.h"
	"Include/ClangParsing/ASTVisitorLocal.h"
	"Include/ClangParsing/CommandLineOptions.h"
	"Include/ClangParsing/GlobalDecls.h"
	"Include/ClangParsing/Helpers/FunctionData.h"
	"Include/ClangParsing/Helpers/Script.h"
	"Include/ClangParsing/Helpers/StaticData.h"
	"Include/Compiler/BuildTarget.h"
	"Include/Compiler/Compiler.h"
	"Include/Compiler/Opcode.h"
	"Include/Compiler/OpcodeConsts.h"
	"Include/Compression/zconf.h"
	"Include/Compression/zlib.h"
	"Include/Crypto/aes256.h"
	"Include/Utils/ClangUtils.h"
	"Include/Utils/ConsoleColor.h"
	"Include/Utils/ConstExpr.h"
	"Include/Utils/Utils.h"
	"Include/Utils/rapidxml/rapidxml.hpp"
	"Include/Utils/rapidxml/rapidxml_iterators.hpp"
	"Include/Utils/rapidxml/rapidxml_print.hpp"
	"Include/Utils/rapidxml/rapidxml_utils.hpp"
)

set(resource_list
	"CMakeLists.txt"
	".gitignore"
	"contributors.txt"
)

link_directories(Include)

add_clang_executable(SC-CL
	SC-CL.cpp
	${source_list}
	${header_list}
)


include_directories(Include)
target_link_libraries(SC-CL
	PUBLIC clangTooling
	PUBLIC clangBasic
	PUBLIC clangASTMatchers
	PUBLIC Compression/zlib
)

foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "Include" "Source Files" source_path_temp "${source_path}")
    string(REPLACE "/" "\\" source_path_msvc "${source_path_temp}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

foreach(header IN LISTS header_list)
    get_filename_component(header_path "${header}" PATH)
    string(REPLACE "Include" "Header Files" header_path_temp "${header_path}")
    string(REPLACE "/" "\\" header_path_msvc "${header_path_temp}")
    source_group("${header_path_msvc}" FILES "${header}")
endforeach()

foreach(resource IN LISTS resource_list)
    get_filename_component(resource_path "${resource}" PATH)
    source_group("Resource Files\\${resource_path}" FILES "${resource}")
endforeach()

add_custom_command(
	TARGET SC-CL
	PRE_BUILD
	CMAKE_CURRENT_SOURCE_DIR "Include/Version/"
	COMMAND "SC-CL_Version_Selector.exe"
	COMMENT "Updating Version Number"
)