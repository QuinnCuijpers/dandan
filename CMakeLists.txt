cmake_minimum_required(VERSION 3.29)
project(dandan)

option(BUILD_TESTING "Enable testing and build tests" ON)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

add_subdirectory(external/json)
add_subdirectory(external/gtest)

add_subdirectory(src)