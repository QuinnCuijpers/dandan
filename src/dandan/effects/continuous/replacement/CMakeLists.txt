add_library(DandanContinuousReplacementEffects OBJECT)

target_sources(DandanContinuousReplacementEffects
               PRIVATE EntersTappedEffect.cpp)

target_sources(DandanContinuousReplacementEffects
               PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanContinuousReplacementEffects PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanContinuousReplacementEffects PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanContinuousReplacementEffects
                         PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_include_directories(DandanContinuousReplacementEffects
                           PUBLIC ${CMAKE_SOURCE_DIR}/include)
