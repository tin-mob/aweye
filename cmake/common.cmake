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
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

file(GLOB ISHERECMD_SOURCES "${CMAKE_SOURCE_DIR}/src/aweye/WebcamHandler.cpp" "${CMAKE_SOURCE_DIR}/src/aweye/main-IsHereCmd.cpp")
file(GLOB ISHERECMD_HEADERS "${CMAKE_SOURCE_DIR}/include/aweye/WebcamHandler.h" "${CMAKE_SOURCE_DIR}/include/aweye/IsHereCmd.h")

file(GLOB AWEYE_SOURCES ${CMAKE_SOURCE_DIR}/src/aweye/*.cpp )
list(REMOVE_ITEM AWEYE_SOURCES ${ISHERECMD_SOURCES})

file(GLOB AWEYE_HEADERS ${CMAKE_SOURCE_DIR}/include/aweye/*.h )
list(REMOVE_ITEM AWEYE_HEADERS "${CMAKE_SOURCE_DIR}/include/aweye/WebcamHandler.h")

include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/include/)
