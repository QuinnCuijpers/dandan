add_executable(Main)

target_sources(Main PRIVATE main.cpp)

target_link_libraries(Main PRIVATE DandanLib)

target_compile_features(Main PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(Main PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(Main PRIVATE -Wall -Wextra -Wpedantic)

endif()

add_subdirectory(dandan)
