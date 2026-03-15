add_library(DandanLib)

target_sources(
    DandanLib PRIVATE Card.cpp
)

target_link_libraries(DandanLib PRIVATE nlohmann_json::nlohmann_json)