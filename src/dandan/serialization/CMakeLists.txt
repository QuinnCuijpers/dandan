add_library(DandanSerialize OBJECT)

target_sources(DandanSerialize
    PRIVATE
        JsonAbilityFactory.cpp
        JsonCostFactory.cpp
)

target_sources(
    DandanSerialize 
    PUBLIC
    FILE_SET HEADERS     
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(DandanSerialize PRIVATE nlohmann_json::nlohmann_json)