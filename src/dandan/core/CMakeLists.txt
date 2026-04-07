add_library(DandanCore OBJECT)

target_sources(DandanCore PRIVATE Card.cpp)

target_sources(DandanCore PUBLIC FILE_SET HEADERS BASE_DIRS
                                 ${CMAKE_SOURCE_DIR}/include)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanCore PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanCore PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_link_libraries(DandanCore PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(DandanCore PUBLIC ${CMAKE_SOURCE_DIR}/include)
