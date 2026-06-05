add_library(DandanOneShotEffects OBJECT)

target_sources(
  DandanOneShotEffects
  PRIVATE DrawEffect.cpp
          ETBEffect.cpp
          PeekEffect.cpp
          ScryEffect.cpp
          BounceLandEffect.cpp
          UntapEffect.cpp
          AddManaEffect.cpp
          AttackEffect.cpp
          DestroyEffect.cpp
          IOneShotEffect.cpp
          PutCardOnTopEffect.cpp)

target_sources(DandanOneShotEffects PUBLIC FILE_SET HEADERS BASE_DIRS
                                           ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanOneShotEffects PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanOneShotEffects PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanOneShotEffects PRIVATE -Wall -Wextra -Wpedantic)

endif()

if(DANDAN_ENABLE_LOGGING)
  target_link_libraries(DandanOneShotEffects PRIVATE plog::plog)
endif()

target_include_directories(DandanOneShotEffects
                           PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(DandanOneShotEffects PRIVATE ${CMAKE_SOURCE_DIR}/src)

if(CODE_COVERAGE)
  target_code_coverage(DandanOneShotEffects)
endif()
