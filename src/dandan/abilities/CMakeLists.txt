add_library(DandanAbilities OBJECT)

target_sources(DandanAbilities 
PRIVATE
    ManaAbility.cpp
    WithDamage.cpp
    ReplacementAbility.cpp
    TriggeredAbility.cpp
)

target_sources(DandanAbilities PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(DandanAbilities PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(DandanAbilities PUBLIC ${CMAKE_SOURCE_DIR}/include)