cmake_minimum_required(VERSION 3.29)
project(dandan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Enable testing and build tests" ON)
option(DANDAN_ENABLE_LOGGING "Enable logging" ON)
option(DANDAN_BUILD_SERIALIZE "Enable building and testing the serialization"
       OFF)
option(CODE_COVERAGE "Enable code coverage" OFF)

add_compile_definitions(DANDAN_PROJECT_SOURCE="${CMAKE_SOURCE_DIR}")

include(cmake/DoxyGen.cmake)
if(CODE_COVERAGE)
  include(cmake/code-coverage.cmake)
  add_code_coverage_all_targets(
    LCOV_OPTIONS
    --ignore-errors
    mismatch
    --rc
    branch_coverage=1
    --exclude
    "*/external/*"
    --exclude
    "*/usr/*"
    --exclude
    "*/tests/*"
    GENHTML_OPTIONS
    --branch-coverage
    --ignore-errors
    inconsistent)
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(external/gtest)
  add_subdirectory(tests)
endif()

if(DANDAN_BUILD_SERIALIZE)
  add_subdirectory(external/json)
endif()

if(DANDAN_ENABLE_LOGGING)
  add_subdirectory(external/plog)
  add_compile_definitions(DANDAN_ENABLE_LOGGING)
endif()

add_subdirectory(src)
