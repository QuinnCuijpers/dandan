add_subdirectory(unit)
add_subdirectory(integration)
add_subdirectory(common)

#fix for too many sections
if(WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options(-Wa,-mbig-obj)
endif()

