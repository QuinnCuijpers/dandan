cmake_minimum_required(VERSION 3.29)
project(dandan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(external/json)

add_subdirectory(src)