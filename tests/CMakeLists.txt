if (NOT ${NANOSPECTRUM_BUILD_TESTS})
  return()
endif()

macro(add_project_test test_name test_executable)
  add_test(NAME ${test_name} COMMAND ${test_executable})
endmacro(add_project_test)
