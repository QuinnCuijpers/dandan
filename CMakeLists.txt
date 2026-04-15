cmake_minimum_required(VERSION 3.29)
project(dandan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Enable testing and build tests" ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(DANDAN_PROJECT_SOURCE="${CMAKE_SOURCE_DIR}")

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

add_subdirectory(external/json)
add_subdirectory(external/gtest)

add_subdirectory(src)
