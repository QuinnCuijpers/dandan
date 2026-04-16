add_library(DandanReplacement OBJECT)

target_sources(DandanReplacement PRIVATE EntersTappedEffect.cpp)

target_sources(DandanReplacement PUBLIC FILE_SET HEADERS BASE_DIRS
                                        ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanReplacement PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanReplacement PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanReplacement PRIVATE -Wall -Wextra -Wpedantic)

endif()
