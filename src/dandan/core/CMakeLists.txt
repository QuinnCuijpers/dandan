add_library(DandanCore OBJECT)

target_sources(DandanCore PRIVATE Card.cpp)

target_sources(DandanCore PUBLIC FILE_SET HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(DandanCore PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(DandanCore PUBLIC ${CMAKE_SOURCE_DIR}/include)