########################################################################
#    Copyright: 2013, Robert Morin
#
#    This file is part of Eyes Watcher.
#
#    Eyes Watcher is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Eyes Watcher is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.
#
########################################################################

cmake_minimum_required(VERSION 2.8)
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

set(EW_BASE "@CMAKE_SOURCE_DIR@")

file(GLOB ISHERECMD_SOURCES "${EW_BASE}/src/ew/WebcamHandler.cpp" "${EW_BASE}/src/ew/main-IsHereCmd.cpp")
file(GLOB ISHERECMD_HEADERS "${EW_BASE}/include/ew/WebcamHandler.h" "${EW_BASE}/include/ew/IsHereCmd.h")

file(GLOB EW_SOURCES ${EW_BASE}/src/ew/*.cpp )
list(REMOVE_ITEM EW_SOURCES ${ISHERECMD_SOURCES})

file(GLOB EW_HEADERS ${EW_BASE}/include/ew/*.h )
list(REMOVE_ITEM EW_HEADERS "${EW_BASE}/include/ew/WebcamHandler.h")

include_directories(${EW_BASE}/src/)
include_directories(${EW_BASE}/include/)
