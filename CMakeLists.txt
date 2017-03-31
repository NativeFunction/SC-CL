set(LLVM_LINK_COMPONENTS support)
set(LLVM_USED_LIBS clangTooling clangBasic clangAST)

add_clang_executable(loop-convert
  SC-CL.cpp
  Include/Utils/Utils.cpp
  Include/Utils/ClangUtils.cpp
  Include/Compiler/Compiler.cpp
  Include/Compiler/Opcode.cpp
  Include/ClangParsing/FunctionData.cpp
  Include/ClangParsing/Script.cpp
  Include/ClangParsing/StaticData.cpp
  )
target_link_libraries(loop-convert
  clangTooling
  clangBasic
  clangASTMatchers
  )
