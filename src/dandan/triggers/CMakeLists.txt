add_library(DandanTriggers OBJECT)

target_sources(DandanTriggers PRIVATE SelfETBTrigger.cpp)

target_sources(DandanTriggers PUBLIC FILE_SET HEADERS BASE_DIRS
                                     ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanTriggers PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanTriggers PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanTriggers PRIVATE -Wall -Wextra -Wpedantic)

endif()

if(DANDAN_ENABLE_LOGGING)
  target_link_libraries(DandanTriggers PRIVATE plog::plog)
endif()

target_include_directories(DandanTriggers PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(DandanTriggers PRIVATE ${CMAKE_SOURCE_DIR}/src)

if(CODE_COVERAGE)
  target_code_coverage(DandanTriggers)
endif()
