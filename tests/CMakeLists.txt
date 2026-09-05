add_subdirectory(unit)
add_subdirectory(integration)
add_subdirectory(common)

if (MSVC)
  target_compile_options(DandanLibTest PRIVATE /bigobj)
  target_compile_options(DandanUnitTest PRIVATE /bigobj)
  target_compile_options(DandanCommonTest PRIVATE /bigobj)
endif()
