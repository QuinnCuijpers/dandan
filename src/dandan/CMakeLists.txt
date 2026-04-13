add_library(DandanLib)

target_sources(DandanLib PUBLIC FILE_SET HEADERS BASE_DIRS
                                ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanLib PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanLib PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanLib PRIVATE -Wall -Wextra -Wpedantic)

endif()

add_subdirectory(core)
add_subdirectory(abilities)
add_subdirectory(effects)
add_subdirectory(events)
add_subdirectory(costs)
add_subdirectory(serialization)
add_subdirectory(replacement_effects)

target_link_libraries(
  DandanLib
  PRIVATE DandanCore
          DandanAbilities
          DandanEffects
          DandanEvents
          DandanCosts
          DandanSerialize
          DandanReplacement
          nlohmann_json::nlohmann_json)

target_include_directories(DandanLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
