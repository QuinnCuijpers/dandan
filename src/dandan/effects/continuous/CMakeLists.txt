add_library(DandanContinuousEffects INTERFACE)

add_subdirectory(prevention)
add_subdirectory(replacement)

target_sources(
  DandanContinuousEffects
  INTERFACE $<TARGET_OBJECTS:DandanContinuousPreventionEffects>
            $<TARGET_OBJECTS:DandanContinuousReplacementEffects>)

if(DANDAN_ENABLE_LOGGING)
  target_link_libraries(DandanContinuousEffects INTERFACE plog::plog)
endif()
