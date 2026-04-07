add_executable(Main)

target_sources(Main PRIVATE main.cpp)

target_compile_definitions(Main
                           PRIVATE DANDAN_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

# TODO: remove the direct dependency on nlohmann_json here, and only link
# DandanLib to it. Main should only depend on DandanLib, and DandanLib should
# depend on nlohmann_json.
target_link_libraries(Main PRIVATE DandanLib nlohmann_json::nlohmann_json)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(Main PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(Main PRIVATE -Wall -Wextra -Wpedantic)

endif()

add_subdirectory(dandan)
