add_subdirectory(unit)
add_subdirectory(integration)
add_subdirectory(common)

#fix for too many sections
if(MINGW)
  target_compile_options(DandanLibTest PRIVATE -Wa,-mbig-obj)
  target_compile_options(DandanLibSerializationTest PRIVATE -Wa,-mbig-obj)
endif()

