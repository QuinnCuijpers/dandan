add_library(DandanMana OBJECT)

target_sources(DandanMana PRIVATE AndMana.cpp ManaList.cpp)

target_sources(DandanMana PUBLIC FILE_SET HEADERS BASE_DIRS
  ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanMana PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  OR(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanMana PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanMana PRIVATE -Wall -Wextra -Wpedantic)

endif()

if(DANDAN_ENABLE_LOGGING)
  target_link_libraries(DandanMana PRIVATE plog::plog)
endif()

target_include_directories(DandanMana PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(CODE_COVERAGE)
  target_code_coverage(DandanMana)
endif()
