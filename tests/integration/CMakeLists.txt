add_executable(DandanLibTest)

target_sources(DandanLibTest PRIVATE DandanLibTest.cpp)

target_sources(DandanLibTest PRIVATE FILE_SET HEADERS BASE_DIRS
                                     ${CMAKE_SOURCE_DIR}/tests)

if(DANDAN_BUILD_SERIALIZE)
  target_sources(DandanLibTest PRIVATE AbilityDisplayTest.cpp)
  target_compile_definitions(DandanLibTest PRIVATE DANDAN_SERIALIZE)
  target_link_libraries(DandanLibTest PRIVATE nlohmann_json::nlohmann_json)
endif()

target_compile_features(DandanLibTest PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanLibTest PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanLibTest PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_link_libraries(DandanLibTest PRIVATE DandanLib GTest::gtest_main)

if(DANDAN_ENABLE_LOGGING)
  target_link_libraries(DandanLibTest PRIVATE plog::plog)
endif()

if(CODE_COVERAGE)
  target_code_coverage(DandanLibTest AUTO ALL)
endif()

include(GoogleTest)
gtest_discover_tests(DandanLibTest)
