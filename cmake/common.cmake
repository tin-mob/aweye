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

# see http://binglongx.wordpress.com/2013/06/28/set-non-default-platform-toolset-in-cmake/

if(MSVC OR MSVC_IDE)
  if( MSVC_VERSION LESS 1700 )       # VC10-/VS2010-
    message(FATAL_ERROR "The project requires C++11 features. "
      "You need at least Visual Studio 11 (Microsoft Visual Studio 2012), "
      "with Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012).")
  elseif( MSVC_VERSION EQUAL 1700 )  # VC11/VS2012
    message( "VC11: use Microsoft Visual Studio 2012 "
      "with Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)" )
    set(CMAKE_GENERATOR_TOOLSET "v120_CTP_Nov2012" CACHE STRING "Platform Toolset" FORCE)
  else() # VC12+, assuming C++11 supported.
  endif()
endif()

#todo other compilers
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -lstdc++")
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
find_package(Boost 1.45.0 REQUIRED date_time) 
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})

file(GLOB ISHERECMD_SOURCES "${CMAKE_SOURCE_DIR}/src/aweye/core/WebcamHandler.cpp" "${CMAKE_SOURCE_DIR}/src/aweye/core/main-IsHereCmd.cpp")
file(GLOB ISHERECMD_HEADERS "${CMAKE_SOURCE_DIR}/include/aweye/core/WebcamHandler.h" "${CMAKE_SOURCE_DIR}/include/aweye/core/IsHereCmd.h")

file(GLOB AWEYE_SOURCES ${CMAKE_SOURCE_DIR}/src/aweye/core/*.cpp )
list(REMOVE_ITEM AWEYE_SOURCES ${ISHERECMD_SOURCES})

file(GLOB AWEYE_HEADERS ${CMAKE_SOURCE_DIR}/include/aweye/core/*.h )
list(REMOVE_ITEM AWEYE_HEADERS "${CMAKE_SOURCE_DIR}/include/aweye/core/WebcamHandler.h")

include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/include/)
