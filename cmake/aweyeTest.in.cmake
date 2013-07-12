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
project( TestAweye )
include(common.cmake)

file( GLOB AWEYE_TEST_SOURCES ${AWEYE_BASE}/src/aweye/test/*.cpp )
file( GLOB AWEYE_TEST_HEADERS ${AWEYE_BASE}/include/aweye/test/*.h )

add_executable( TestAweye ${AWEYE_SOURCES} ${AWEYE_TEST_SOURCES} ${AWEYE_HEADERS} ${AWEYE_TEST_HEADERS})
target_link_libraries(TestAweye UnitTest++)
