cmake_minimum_required(VERSION 2.8)
project( EyesWatcher )
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

set(EW_BASE "../..")

# umph. seems to work without it... (is it because it is used to build opencv?)
#find_package( OpenCV REQUIRED )
# use only what is needed (some are not necessarily installed)
set(OpenCV_LIBS opencv_core opencv_objdetect opencv_imgproc opencv_highgui)

find_package(wxWidgets COMPONENTS core base adv REQUIRED)
include(${wxWidgets_USE_FILE})

file(GLOB ISHERECMD_SOURCES "${EW_BASE}/src/ew/WebcamHandler.cpp" "${EW_BASE}/src/ew/main-IsHereCmd.cpp")
file(GLOB ISHERECMD_HEADERS "${EW_BASE}/include/ew/WebcamHandler.h" "${EW_BASE}/include/ew/IsHereCmd.h")

file(GLOB EW_SOURCES ${EW_BASE}/src/ew/*.cpp )
list(REMOVE_ITEM EW_SOURCES ${ISHERECMD_SOURCES})

file(GLOB EW_HEADERS ${EW_BASE}/include/ew/*.h )
list(REMOVE_ITEM EW_HEADERS "${EW_BASE}/include/ew/WebcamHandler.h")

file( GLOB EW_WX_SOURCES ${EW_BASE}/src/ew/wx/*.cpp )
file( GLOB EW_WX_HEADERS ${EW_BASE}/include/ew/wx/*.h )

include_directories(${EW_BASE}/src/)
include_directories(${EW_BASE}/include/)

add_executable( IsHereCmd ${ISHERECMD_SOURCES} ${ISHERECMD_HEADERS})
target_link_libraries( IsHereCmd ${OpenCV_LIBS} )

add_executable( EyesWatcher ${EW_SOURCES} ${EW_WX_SOURCES} ${EW_HEADERS} ${EW_WX_HEADERS})
target_link_libraries( EyesWatcher ${wxWidgets_LIBRARIES})
add_dependencies(EyesWatcher IsHereCmd)

