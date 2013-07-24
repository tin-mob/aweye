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

cmake_minimum_required(VERSION 2.8)
project(Aweye)

# @todo should this change for windows? 
set(DEST_DATA_DIR share/${CMAKE_PROJECT_NAME})

########################################################################
# Import Packages
########################################################################

# @todo umph. seems to work without it... (is it because it is used to build opencv?)
#find_package( OpenCV REQUIRED )

# use only what is needed (some are not necessarily installed)
set(OpenCV_LIBS opencv_core opencv_objdetect opencv_imgproc opencv_highgui)

# use static because we use 2.9 = compile from source...
#set_property(GLOBAL PROPERTY wxWidgets_USE_STATIC)
find_package(wxWidgets COMPONENTS core base adv REQUIRED)
include(${wxWidgets_USE_FILE})

########################################################################
# Executables
########################################################################

file(GLOB AWEYE_WX_SOURCES ${CMAKE_SOURCE_DIR}/src/aweye/wx/*.cpp)
file(GLOB AWEYE_WX_HEADERS ${CMAKE_SOURCE_DIR}/include/aweye/wx/*.h)

add_executable( IsHereCmd ${ISHERECMD_SOURCES} ${ISHERECMD_HEADERS})
target_link_libraries( IsHereCmd ${OpenCV_LIBS} )

set(AWEYE_DATA_DIR ${CMAKE_INSTALL_PREFIX}/${DEST_DATA_DIR})
configure_file(${CMAKE_SOURCE_DIR}/cmake/Defines.in.h ${CMAKE_BINARY_DIR}/CMakeDefines.h)
include_directories(${CMAKE_BINARY_DIR})

add_executable( Aweye ${AWEYE_SOURCES} ${AWEYE_WX_SOURCES} ${AWEYE_HEADERS} ${AWEYE_WX_HEADERS} ${CMAKE_BINARY_DIR}/CMakeDefines.h)
target_link_libraries( Aweye ${wxWidgets_LIBRARIES})
add_dependencies(Aweye IsHereCmd)

