add_library(DandanEffects INTERFACE)

add_subdirectory(one_shot)
add_subdirectory(continuous)

target_sources(
  DandanEffects
  INTERFACE $<TARGET_OBJECTS:DandanOneShotEffects>
            $<TARGET_OBJECTS:DandanContinuousPreventionEffects>
            $<TARGET_OBJECTS:DandanContinuousReplacementEffects>)

if(DANDAN_ENABLE_LOGGING)
  target_link_libraries(DandanEffects INTERFACE plog::plog)
endif()
