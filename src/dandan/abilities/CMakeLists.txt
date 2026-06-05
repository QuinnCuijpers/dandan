add_library(DandanAbilities OBJECT)

target_sources(
  DandanAbilities
  PRIVATE ActivatedAbility.cpp ManaAbility.cpp WithDamage.cpp StaticAbility.cpp
          TriggeredAbility.cpp SpellAbility.cpp)

target_sources(DandanAbilities PUBLIC FILE_SET HEADERS BASE_DIRS
                                      ${CMAKE_SOURCE_DIR}/include)

target_sources(DandanAbilities PRIVATE FILE_SET internal TYPE HEADERS BASE_DIRS
                                       ${CMAKE_SOURCE_DIR}/src)

target_compile_features(DandanAbilities PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanAbilities PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanAbilities PRIVATE -Wall -Wextra -Wpedantic)

endif()

if(DANDAN_ENABLE_LOGGING)
  target_link_libraries(DandanAbilities PRIVATE plog::plog)
endif()

if(CODE_COVERAGE)
  target_code_coverage(DandanAbilities)
endif()
