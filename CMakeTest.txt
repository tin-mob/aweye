cmake_minimum_required(VERSION 2.8)
project( TestEyesWatcher )
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

set(EW_BASE "../..")

file(GLOB ISHERECMD_SOURCES "${EW_BASE}/src/ew/WebcamHandler.cpp" "${EW_BASE}/src/ew/main-IsHereCmd.cpp")
file(GLOB ISHERECMD_HEADERS "${EW_BASE}/include/ew/WebcamHandler.h" "${EW_BASE}/include/ew/IsHereCmd.h")

file(GLOB EW_SOURCES ${EW_BASE}/src/ew/*.cpp )
list(REMOVE_ITEM EW_SOURCES ${ISHERECMD_SOURCES})

file(GLOB EW_HEADERS ${EW_BASE}/include/ew/*.h )
list(REMOVE_ITEM EW_HEADERS "${EW_BASE}/include/ew/WebcamHandler.h")

file( GLOB EW_TEST_SOURCES ${EW_BASE}/src/ew/test/*.cpp )
file( GLOB EW_TEST_HEADERS ${EW_BASE}/include/ew/test/*.h )

include_directories(${EW_BASE}/src/)
include_directories(${EW_BASE}/include/)

add_executable( TestEyesWatcher ${EW_SOURCES} ${EW_TEST_SOURCES} ${EW_HEADERS} ${EW_TEST_HEADERS})
target_link_libraries(TestEyesWatcher UnitTest++)
