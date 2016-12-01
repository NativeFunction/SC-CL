set(LLVM_LINK_COMPONENTS support)
set(LLVM_USED_LIBS clangTooling clangBasic clangAST)

add_clang_executable(loop-convert
  LoopConvert.cpp
  Utils.cpp
  ClangUtils.cpp
  Compiler.cpp
  FunctionData.cpp
  Script.cpp
  Opcode.cpp
  StaticData.cpp
  )
target_link_libraries(loop-convert
  clangTooling
  clangBasic
  clangASTMatchers
  )
