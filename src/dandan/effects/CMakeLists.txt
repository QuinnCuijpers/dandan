add_library(DandanEffects INTERFACE)

add_subdirectory(one_shot)
add_subdirectory(continuous)

target_sources(
  DandanEffects
  INTERFACE $<TARGET_OBJECTS:DandanOneShotEffects>
            $<TARGET_OBJECTS:DandanContinuousPreventionEffects>
            $<TARGET_OBJECTS:DandanContinuousReplacementEffects>)
