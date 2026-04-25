add_library(DandanConditions OBJECT)

target_sources(DandanConditions PRIVATE ControlsIslandCondition.cpp)

target_sources(DandanConditions PUBLIC FILE_SET HEADERS BASE_DIRS
                                       ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanConditions PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanConditions PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanConditions PRIVATE -Wall -Wextra -Wpedantic)

endif()
