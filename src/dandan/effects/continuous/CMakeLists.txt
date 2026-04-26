add_library(DandanContinuousEffects INTERFACE)

add_subdirectory(prevention)
add_subdirectory(replacement)

target_sources(
  DandanContinuousEffects
  INTERFACE $<TARGET_OBJECTS:DandanContinuousPreventionEffects>
            $<TARGET_OBJECTS:DandanContinuousReplacementEffects>)
