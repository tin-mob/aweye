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

set(MAKE_TESTS "0" CACHE BOOL "Make tests target.")

if(MAKE_TESTS)
	include(cmake/FindUnitTest++.cmake)
	
	project( TestAweye )
	
	include_directories(${UNITTEST++_INCLUDE_DIR})

	file( GLOB AWEYE_TEST_SOURCES ${CMAKE_SOURCE_DIR}/src/aweye/test/*.cpp )
	file( GLOB AWEYE_TEST_HEADERS ${CMAKE_SOURCE_DIR}/include/aweye/test/*.h )

	if(WIN32)
		add_executable( TestAweye EXCLUDE_FROM_ALL ${AWEYE_SOURCES} ${AWEYE_TEST_SOURCES} ${AWEYE_HEADERS}
			${AWEYE_TEST_HEADERS} ${AWEYE_RC})
	else(WIN32)
		add_executable( TestAweye EXCLUDE_FROM_ALL ${AWEYE_SOURCES} ${AWEYE_TEST_SOURCES} ${AWEYE_HEADERS} ${AWEYE_TEST_HEADERS})
	endif(WIN32)
	target_link_libraries(TestAweye ${UNITTEST++_LIBRARY} ${Boost_LIBRARIES})
endif()
