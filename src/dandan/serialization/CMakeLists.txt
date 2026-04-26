add_library(DandanSerialize OBJECT)

target_sources(
  DandanSerialize
  PRIVATE JsonFactory.cpp
          JsonAbilityFactory.cpp
          JsonCardFactory.cpp
          JsonCostFactory.cpp
          JsonEventFactory.cpp
          JsonEffectOneShotFactory.cpp
          JsonManaFactory.cpp
          JsonEffectContinuousFactory.cpp)

target_sources(DandanSerialize PUBLIC FILE_SET HEADERS BASE_DIRS
                                      ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanSerialize PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanSerialize PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanSerialize PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_compile_definitions(DandanSerialize PRIVATE DANDAN_BUILD_SERIALIZE)

target_link_libraries(DandanSerialize PRIVATE nlohmann_json::nlohmann_json)
