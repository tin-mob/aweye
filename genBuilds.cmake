# specify GENERATOR variable with -D to be used with default cmake scripts
if(NOT GENERATOR)
	set(GENERATOR "")
endif(NOT GENERATOR)

set(BUILD_DIR bin)
set(EW_DIR ${BUILD_DIR}/ew)
set(EW_TEST_DIR ${BUILD_DIR}/ew-test)

file(MAKE_DIRECTORY ${BUILD_DIR})
file(MAKE_DIRECTORY ${EW_DIR})
file(MAKE_DIRECTORY ${EW_TEST_DIR})

configure_file(cmake/EW.in.cmake ${EW_DIR}/CMakeLists.txt COPYONLY)
configure_file(cmake/EWTest.in.cmake ${EW_TEST_DIR}/CMakeLists.txt COPYONLY)

configure_file(cmake/CMakeCmd.in.py ${EW_DIR}/def-cmake.py)
configure_file(cmake/CMakeCmd.in.py ${EW_TEST_DIR}/def-cmake.py)
