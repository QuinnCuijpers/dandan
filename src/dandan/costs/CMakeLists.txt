add_library(DandanCosts OBJECT)

target_sources(DandanCosts PRIVATE CyclingCost.cpp GenericManaCost.cpp)

target_sources(DandanCosts PUBLIC FILE_SET HEADERS BASE_DIRS
                                  ${CMAKE_SOURCE_DIR}/include)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanCosts PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanCosts PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_link_libraries(DandanCosts PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(DandanCosts PUBLIC ${CMAKE_SOURCE_DIR}/include)
