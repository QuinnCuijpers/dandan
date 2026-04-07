# todo: Add tests for the Dandan library

add_executable(DandanLib_test DandanLib_test.cpp)

# TODO: decouple from nlohmann_json
target_link_libraries(
  DandanLib_test PRIVATE DandanLib nlohmann_json::nlohmann_json
                         GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(DandanLib_test)
