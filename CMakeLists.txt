cmake_minimum_required(VERSION 3.29)
project(dandan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING "Enable testing and build tests" ON)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()


add_subdirectory(external/json)
add_subdirectory(external/gtest)

add_subdirectory(src)