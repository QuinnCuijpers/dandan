# todo: Add tests for the Dandan library

add_executable(DandanLibTest DandanLib_test.cpp)

target_compile_features(DandanLibTest PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanLibTest PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanLibTest PRIVATE -Wall -Wextra -Wpedantic)

endif()

# TODO: decouple from nlohmann_json
target_link_libraries(
  DandanLibTest PRIVATE DandanLib nlohmann_json::nlohmann_json
                        GTest::gtest_main)

target_compile_definitions(DandanLibTest
                           PRIVATE DANDAN_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
include(GoogleTest)
gtest_discover_tests(DandanLibTest)
