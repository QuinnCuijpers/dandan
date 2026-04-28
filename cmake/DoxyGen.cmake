set(DOXYGEN_EXECUTABLE "doxygen")

add_custom_target(
  docs
  COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Generating documentation with Doxygen")
