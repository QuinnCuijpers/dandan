cmake_minimum_required(VERSION 3.29)
project(dandan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Enable testing and build tests" ON)
option(DANDAN_BUILD_SERIALIZE "Enable building and testing the serialization"
       OFF)

add_compile_definitions(DANDAN_PROJECT_SOURCE="${CMAKE_SOURCE_DIR}")

include(cmake/DoxyGen.cmake)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(external/gtest)
  add_subdirectory(tests)
endif()

if(DANDAN_BUILD_SERIALIZE)
  add_subdirectory(external/json)
endif()

add_subdirectory(src)
