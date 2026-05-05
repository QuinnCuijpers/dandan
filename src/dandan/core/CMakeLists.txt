add_library(DandanCore OBJECT)

target_sources(
  DandanCore
  PRIVATE Card.cpp
          Deck.cpp
          Battlefield.cpp
          EventManager.cpp
          Stack.cpp
          Game.cpp
          phases/BeginningPhase.cpp
          phases/MainPhase.cpp
          phases/EndingPhase.cpp
          PreventionManager.cpp)

target_sources(DandanCore PUBLIC FILE_SET HEADERS BASE_DIRS
                                 ${CMAKE_SOURCE_DIR}/include)

target_compile_features(DandanCore PRIVATE cxx_std_17)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))

  target_compile_options(DandanCore PRIVATE /W4)

elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES
                                                  "Clang"))

  target_compile_options(DandanCore PRIVATE -Wall -Wextra -Wpedantic)

endif()

target_include_directories(DandanCore PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(DANDAN_BUILD_SERIALIZE)
  target_compile_definitions(DandanCore PRIVATE DANDAN_BUILD_SERIALIZE)
  target_link_libraries(DandanCore PRIVATE nlohmann_json::nlohmann_json)
endif()
