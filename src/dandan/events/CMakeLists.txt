add_library(DandanEvents OBJECT)

target_sources(DandanEvents PRIVATE EntersBattlefieldEvent.cpp)

target_sources(DandanEvents PUBLIC FILE_SET HEADERS BASE_DIRS
                                   ${CMAKE_SOURCE_DIR}/include)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanEvents PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanEvents PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_link_libraries(DandanEvents PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(DandanEvents PUBLIC ${CMAKE_SOURCE_DIR}/include)
