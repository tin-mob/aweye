cmake_minimum_required(VERSION 2.8)
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

include_directories(${EW_BASE}/src/)
include_directories(${EW_BASE}/include/)
