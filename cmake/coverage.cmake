option(ENABLE_CLANG_COVERAGE "Enable Clang source-based coverage" OFF)

if(ENABLE_CLANG_COVERAGE)
  message(STATUS "Clang source-based coverage enabled")

  if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "ENABLE_CLANG_COVERAGE requires Clang")
  endif()

  add_compile_options(-fprofile-instr-generate -fcoverage-mapping -O0 -g)

  add_link_options(-fprofile-instr-generate -fcoverage-mapping)
endif()
