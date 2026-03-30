add_library(DandanEvents OBJECT)

target_sources(DandanEvents 
PRIVATE
    EntersBattlefieldEvent.cpp
)

target_sources(DandanEvents PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(DandanEvents PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(DandanEvents PUBLIC ${CMAKE_SOURCE_DIR}/include)