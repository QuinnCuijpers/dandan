
add_library(DandanTestCommon)

target_sources(DandanTestCommon PRIVATE
  CreatureDefinitions.cpp
  LandDefinitions.cpp
  SpellDefinitions.cpp)

target_sources(DandanTestCommon PRIVATE FILE_SET HEADERS BASE_DIRS
  ${CMAKE_SOURCE_DIR}/tests/common)

target_link_libraries(DandanTestCommon PRIVATE DandanLib)
