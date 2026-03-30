add_library(DandanEffects OBJECT)

target_sources(DandanEffects 
PRIVATE
    EntersTappedEffect.cpp
    PeekEffect.cpp
    ScryEffect.cpp
)

target_sources(DandanEffects PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(DandanEffects PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(DandanEffects PUBLIC ${CMAKE_SOURCE_DIR}/include)