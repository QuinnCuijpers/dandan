add_library(DandanContinuousPreventionEffects OBJECT)

target_sources(DandanContinuousPreventionEffects
               PRIVATE AttackPreventionEffect.cpp)

target_sources(DandanContinuousPreventionEffects
               PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanContinuousPreventionEffects PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanContinuousPreventionEffects PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanContinuousPreventionEffects
                         PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_include_directories(DandanContinuousPreventionEffects
                           PUBLIC ${CMAKE_SOURCE_DIR}/include)
