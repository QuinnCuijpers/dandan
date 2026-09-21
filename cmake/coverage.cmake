# Minimal code coverage: GCC/Clang instrumentation with lcov + genhtml.
#
# Enable with -DCODE_COVERAGE=ON (e.g. the "coverage" preset), then:
#   cmake --build build --target ccov-all
# produces build/ccov/ccov-all.info and build/ccov/all-merged/index.html
# (paths kept identical to the previous module so CI needs no changes).

if(NOT CODE_COVERAGE)
  return()
endif()

find_program(LCOV_PATH lcov REQUIRED)
find_program(GENHTML_PATH genhtml REQUIRED)

set(COVERAGE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/ccov)
set(COVERAGE_INFO ${COVERAGE_OUTPUT_DIR}/ccov-all.info)

function(target_code_coverage target)
  target_compile_options(${target} PRIVATE --coverage -O0 -g)
  target_link_libraries(${target} PRIVATE gcov)
endfunction()

# Runs every registered test, then captures and renders coverage.
add_custom_target(
  ccov-all
  COMMAND ${CMAKE_COMMAND} -E make_directory ${COVERAGE_OUTPUT_DIR}
  COMMAND ${LCOV_PATH} --zerocounters --directory ${CMAKE_BINARY_DIR}
  COMMAND ${CMAKE_CTEST_COMMAND}
  COMMAND
    ${LCOV_PATH} --capture --directory ${CMAKE_BINARY_DIR} --base-directory
    ${CMAKE_SOURCE_DIR} --no-external --rc branch_coverage=1
    --rc check_data_consistency=0 --ignore-errors mismatch --ignore-errors
    inconsistent --output-file ${COVERAGE_INFO}
  COMMAND
    ${LCOV_PATH} --remove ${COVERAGE_INFO} */tests/* */external/*
    --rc branch_coverage=1 --rc check_data_consistency=0 --output-file
    ${COVERAGE_INFO}
  COMMAND
    ${GENHTML_PATH} ${COVERAGE_INFO}
    --output-directory ${COVERAGE_OUTPUT_DIR}/all-merged --branch-coverage
    --ignore-errors inconsistent --rc check_data_consistency=0
  COMMAND ${CMAKE_COMMAND} -E echo
          "Coverage report: ${COVERAGE_OUTPUT_DIR}/all-merged/index.html"
  VERBATIM)