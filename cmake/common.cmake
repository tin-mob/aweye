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

#todo other compilers
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
	
	if(WIN32)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")
	endif()
endif()

set(BOOST_ROOT_CACHE "" CACHE PATH "Boost directory.")
if(NOT BOOST_ROOT_CACHE EQUAL "")
	set(BOOST_ROOT ${BOOST_ROOT_CACHE})
endif()

set (BOOST_LIBRARYDIR_CACHE "" CACHE PATH "Boost library directory")
if(NOT BOOST_LIBRARYDIR_CACHE EQUAL "")
	set(BOOST_LIBRARYDIR ${BOOST_LIBRARYDIR_CACHE})
endif()

#set(Boost_USE_STATIC_LIBS ON) 
# set(Boost_USE_MULTITHREADED ON)  
# set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.54.0 REQUIRED date_time) 
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB ISHERECMD_SOURCES "${CMAKE_SOURCE_DIR}/src/aweye/core/WebcamHandler.cpp" "${CMAKE_SOURCE_DIR}/src/aweye/core/main-IsHereCmd.cpp")
file(GLOB ISHERECMD_HEADERS "${CMAKE_SOURCE_DIR}/include/aweye/core/WebcamHandler.h" "${CMAKE_SOURCE_DIR}/include/aweye/core/IsHereCmd.h")

file(GLOB AWEYE_SOURCES ${CMAKE_SOURCE_DIR}/src/aweye/core/*.cpp )
list(REMOVE_ITEM AWEYE_SOURCES ${ISHERECMD_SOURCES})

file(GLOB AWEYE_HEADERS ${CMAKE_SOURCE_DIR}/include/aweye/core/*.h )
list(REMOVE_ITEM AWEYE_HEADERS "${CMAKE_SOURCE_DIR}/include/aweye/core/WebcamHandler.h")

include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/include/)
