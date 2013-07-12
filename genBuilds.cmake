########################################################################
#    Copyright: 2013, Robert Morin
#
#    This file is part of Aweye.
#
#    Aweye is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Aweye is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.
#
########################################################################
#
# variables to specify default debug behaviour in scripts
# use -D to use them.
#
# GENERATOR :	Generator to use by cmake. Defaults to nothing.
# CONFIG_PATH :	Location of the config file to use by Aweye.
#				Defaults to Aweye.cfg in current folder.
# DATA_DIR :	Location of the data files. Defaults to [Base]/data/ .
########################################################################

if(NOT GENERATOR)
	set(GENERATOR "")
endif(NOT GENERATOR)
if(NOT CONFIG_PATH)
	set(CONFIG_PATH "Aweye.cfg")
endif(NOT CONFIG_PATH)
if(NOT DATA_DIR)
	set(DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data/)
endif(NOT DATA_DIR)

########################################################################
# Make bin Directories
########################################################################

set(BUILD_DIR bin)
set(AWEYE_DIR ${BUILD_DIR}/aweye)
set(AWEYE_TEST_DIR ${BUILD_DIR}/test-aweye)

file(MAKE_DIRECTORY ${BUILD_DIR})
file(MAKE_DIRECTORY ${AWEYE_DIR})
file(MAKE_DIRECTORY ${AWEYE_TEST_DIR})

########################################################################
# Copy Files
########################################################################

configure_file(cmake/aweye.in.cmake ${AWEYE_DIR}/CMakeLists.txt @ONLY)
configure_file(cmake/common.cmake ${AWEYE_DIR}/common.cmake @ONLY)

configure_file(cmake/aweyeTest.in.cmake ${AWEYE_TEST_DIR}/CMakeLists.txt @ONLY)
configure_file(cmake/common.cmake ${AWEYE_TEST_DIR}/common.cmake @ONLY)

configure_file(cmake/CMakeCmd.in.py ${AWEYE_DIR}/cmake-deb.py)
configure_file(cmake/CMakeCmd.in.py ${AWEYE_TEST_DIR}/cmake-deb.py)

configure_file(cmake/aweyeCmd.in.py ${AWEYE_DIR}/aweye-deb.py)
configure_file(cmake/Defines.in.h ${AWEYE_DIR}/Defines.in.h COPYONLY)
