add_library(DandanLib)

target_sources(DandanLib PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(core)
add_subdirectory(abilities)
add_subdirectory(effects)
add_subdirectory(events)
add_subdirectory(costs)

target_link_libraries(DandanLib PRIVATE 
    DandanCore 
    DandanAbilities 
    DandanEffects 
    DandanEvents 
    DandanCosts 
    nlohmann_json::nlohmann_json)

target_include_directories(DandanLib PUBLIC ${CMAKE_SOURCE_DIR}/include)