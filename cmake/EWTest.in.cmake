cmake_minimum_required(VERSION 2.8)
project( TestEyesWatcher )
include(common.cmake)

file( GLOB EW_TEST_SOURCES ${EW_BASE}/src/ew/test/*.cpp )
file( GLOB EW_TEST_HEADERS ${EW_BASE}/include/ew/test/*.h )

add_executable( TestEyesWatcher ${EW_SOURCES} ${EW_TEST_SOURCES} ${EW_HEADERS} ${EW_TEST_HEADERS})
target_link_libraries(TestEyesWatcher UnitTest++)
