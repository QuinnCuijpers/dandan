add_executable(DandanLibTest DandanLibTest.cpp)

if(DANDAN_BUILD_SERIALIZE)
  add_subdirectory(serialization)
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

include(GoogleTest)
gtest_discover_tests(DandanLibTest)
