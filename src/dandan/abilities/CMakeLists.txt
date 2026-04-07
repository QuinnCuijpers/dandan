add_library(DandanAbilities OBJECT)

target_sources(DandanAbilities 
PRIVATE
    ActivatedAbility.cpp
    ManaAbility.cpp
    WithDamage.cpp
    ReplacementAbility.cpp
    TriggeredAbility.cpp
)

target_sources(DandanAbilities PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
)

if(
  (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR
  (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
)

  target_compile_options(DandanAbilities PRIVATE /W4)

elseif(
  (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
  (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
)

  target_compile_options(DandanAbilities PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_link_libraries(DandanAbilities PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(DandanAbilities PUBLIC ${CMAKE_SOURCE_DIR}/include)