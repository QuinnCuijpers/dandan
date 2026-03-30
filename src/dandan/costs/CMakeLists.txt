add_library(DandanCosts OBJECT)

target_sources(DandanCosts 
PRIVATE
    CyclingCost.cpp
    GenericManaCost.cpp
)

    target_sources(DandanCosts PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(DandanCosts PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(DandanCosts PUBLIC ${CMAKE_SOURCE_DIR}/include)