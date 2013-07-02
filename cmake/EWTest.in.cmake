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
project( TestEyesWatcher )
include(common.cmake)

file( GLOB EW_TEST_SOURCES ${EW_BASE}/src/ew/test/*.cpp )
file( GLOB EW_TEST_HEADERS ${EW_BASE}/include/ew/test/*.h )

add_executable( TestEyesWatcher ${EW_SOURCES} ${EW_TEST_SOURCES} ${EW_HEADERS} ${EW_TEST_HEADERS})
target_link_libraries(TestEyesWatcher UnitTest++)
