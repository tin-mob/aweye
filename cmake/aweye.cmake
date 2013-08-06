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

if(WIN32)
	set(DEST_DATA_DIR "")
else(WIN32)
	set(DEST_DATA_DIR share/${CMAKE_PROJECT_NAME})
endif(WIN32)

########################################################################
# Import Packages
########################################################################

find_package( OpenCV REQUIRED )

# use static?
#set_property(GLOBAL PROPERTY wxWidgets_USE_STATIC)
find_package(wxWidgets COMPONENTS core base adv REQUIRED)
include(${wxWidgets_USE_FILE})

# wxwidgets makes a bunch of warnings in msvc. silence them.
if(MSVC OR MSVC_IDE)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

########################################################################
# Executables
########################################################################

file(GLOB AWEYE_WX_SOURCES ${CMAKE_SOURCE_DIR}/src/aweye/wx/*.cpp)
file(GLOB AWEYE_WX_HEADERS ${CMAKE_SOURCE_DIR}/include/aweye/wx/*.h)

if(WIN32)
	add_executable( IsHereCmd ${ISHERECMD_SOURCES} ${ISHERECMD_HEADERS} ${AWEYE_RC})
	add_executable( Aweye WIN32 ${AWEYE_SOURCES} ${AWEYE_WX_SOURCES} ${AWEYE_HEADERS} ${AWEYE_WX_HEADERS}
		${CMAKE_BINARY_DIR}/CMakeDefines.h ${AWEYE_RC})
else(WIN32)
	add_executable( IsHereCmd ${ISHERECMD_SOURCES} ${ISHERECMD_HEADERS})
	add_executable( Aweye ${AWEYE_SOURCES} ${AWEYE_WX_SOURCES} ${AWEYE_HEADERS} ${AWEYE_WX_HEADERS} ${CMAKE_BINARY_DIR}/CMakeDefines.h)
endif(WIN32)

target_link_libraries( IsHereCmd ${OpenCV_LIBS} )

get_target_property( ISHERECMD_FULL_NAME IsHereCmd LOCATION_CONFIG)
get_filename_component(ISHERECMD_NAME ${ISHERECMD_FULL_NAME} NAME)

if(${DEST_DATA_DIR})
	set(AWEYE_DATA_DIR ${CMAKE_INSTALL_PREFIX}/${DEST_DATA_DIR})
else(${DEST_DATA_DIR})
	set(AWEYE_DATA_DIR ${CMAKE_INSTALL_PREFIX})
endif(${DEST_DATA_DIR})

configure_file(${CMAKE_SOURCE_DIR}/cmake/Defines.in.h ${CMAKE_BINARY_DIR}/CMakeDefines.h)
include_directories(${CMAKE_BINARY_DIR})

target_link_libraries( Aweye ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(Aweye IsHereCmd)
