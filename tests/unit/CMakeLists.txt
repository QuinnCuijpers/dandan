add_executable(DandanUnitTests)

target_sources(DandanUnitTests PRIVATE core/CardDataTest.cpp)

target_compile_features(DandanUnitTests PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanUnitTests PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanUnitTests PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_link_libraries(DandanUnitTests PRIVATE DandanLib GTest::gtest_main)

if(DANDAN_ENABLE_LOGGING)
  target_link_libraries(DandanUnitTests PRIVATE plog::plog)
endif()

if(DANDAN_BUILD_SERIALIZE)
  target_compile_definitions(DandanUnitTests PRIVATE DANDAN_SERIALIZE)
  target_link_libraries(DandanUnitTests PRIVATE nlohmann_json::nlohmann_json)
endif()

if(CODE_COVERAGE)
  target_code_coverage(DandanUnitTests AUTO ALL)
endif()

include(GoogleTest)
gtest_discover_tests(DandanUnitTests)

if(DANDAN_BUILD_SERIALIZE)
  add_subdirectory(serialization)
endif()
