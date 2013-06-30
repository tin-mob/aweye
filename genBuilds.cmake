# variables to specify default debug behaviour in scripts
# use -D to use them.
#
# GENERATOR :	Generator to use by cmake. Defaults to nothing.
# CONFIG_PATH :	Location of the config file to use by EyeWatcher.
#				Defaults to EyesWatcher.cfg in current folder.
# DATA_DIR :	Location of the data files. Defaults to [Base]/data/ .

if(NOT GENERATOR)
	set(GENERATOR "")
endif(NOT GENERATOR)
if(NOT CONFIG_PATH)
	set(CONFIG_PATH "EyesWatcher.cfg")
endif(NOT CONFIG_PATH)
if(NOT DATA_DIR)
	set(DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data/)
endif(NOT DATA_DIR)

set(BUILD_DIR bin)
set(EW_DIR ${BUILD_DIR}/ew)
set(EW_TEST_DIR ${BUILD_DIR}/ew-test)

file(MAKE_DIRECTORY ${BUILD_DIR})
file(MAKE_DIRECTORY ${EW_DIR})
file(MAKE_DIRECTORY ${EW_TEST_DIR})

configure_file(cmake/EW.in.cmake ${EW_DIR}/CMakeLists.txt COPYONLY)
configure_file(cmake/EWTest.in.cmake ${EW_TEST_DIR}/CMakeLists.txt COPYONLY)

configure_file(cmake/CMakeCmd.in.py ${EW_DIR}/cmake-deb.py)
configure_file(cmake/CMakeCmd.in.py ${EW_TEST_DIR}/cmake-deb.py)

configure_file(cmake/EWCmd.in.py ${EW_DIR}/ew-deb.py)
