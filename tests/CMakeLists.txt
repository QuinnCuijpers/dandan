add_subdirectory(unit)
add_subdirectory(integration)
add_subdirectory(common)

#fix for too many sections
if(MINGW)
  add_compile_options(-Wa,-mbig-obj)
endif()

