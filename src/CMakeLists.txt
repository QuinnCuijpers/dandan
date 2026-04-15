add_executable(Main)

target_sources(Main PRIVATE main.cpp)

# TODO: remove the direct dependency on nlohmann_json here, and only link
# DandanLib to it. Main should only depend on DandanLib, and DandanLib should
# depend on nlohmann_json.
target_link_libraries(Main PRIVATE DandanLib nlohmann_json::nlohmann_json)

target_compile_features(Main PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(Main PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(Main PRIVATE -Wall -Wextra -Wpedantic)

endif()

add_subdirectory(dandan)
