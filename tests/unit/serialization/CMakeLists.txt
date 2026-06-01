if(DANDAN_BUILD_SERIALIZE)
  add_executable(DandanLibSerializationTest)

  target_sources(
    DandanLibSerializationTest
    PRIVATE DeserializeTest.cpp DandanLandsSerializationTest.cpp
            DandanCreatureSerializationTest.cpp)

  target_sources(DandanLibSerializationTest PRIVATE FILE_SET HEADERS BASE_DIRS
                                                    ${CMAKE_SOURCE_DIR}/tests)

  target_compile_features(DandanLibSerializationTest PRIVATE cxx_std_17)
  target_compile_definitions(DandanLibSerializationTest
                             PRIVATE DANDAN_SERIALIZE)

  if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
     OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

    target_compile_options(DandanLibSerializationTest PRIVATE /W4)

  elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID
                                                    MATCHES "Clang"))

    target_compile_options(DandanLibSerializationTest PRIVATE -Wall -Wextra
                                                              -Wpedantic)

  endif()

  target_link_libraries(
    DandanLibSerializationTest PRIVATE DandanLib nlohmann_json::nlohmann_json
                                       GTest::gtest_main)

  if(CODE_COVERAGE)
    target_code_coverage(DandanLibSerializationTest AUTO ALL)
  endif()

  include(GoogleTest)
  gtest_discover_tests(DandanLibSerializationTest)
endif()
