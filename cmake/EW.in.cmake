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
project(EyesWatcher)
include(common.cmake)

# @todo should this change for windows? 
set(DEST_DATA_DIR share/${CMAKE_PROJECT_NAME})

########################################################################
# Import Packages
########################################################################

# @todo umph. seems to work without it... (is it because it is used to build opencv?)
#find_package( OpenCV REQUIRED )

# use only what is needed (some are not necessarily installed)
set(OpenCV_LIBS opencv_core opencv_objdetect opencv_imgproc opencv_highgui)

find_package(wxWidgets COMPONENTS core base adv REQUIRED)
include(${wxWidgets_USE_FILE})

########################################################################
# Executables
########################################################################

file(GLOB EW_WX_SOURCES ${EW_BASE}/src/ew/wx/*.cpp)
file(GLOB EW_WX_HEADERS ${EW_BASE}/include/ew/wx/*.h)

add_executable( IsHereCmd ${ISHERECMD_SOURCES} ${ISHERECMD_HEADERS})
target_link_libraries( IsHereCmd ${OpenCV_LIBS} )

set(EW_DATA_DIR ${CMAKE_INSTALL_PREFIX}/${DEST_DATA_DIR})
configure_file(Defines.in.h CMakeDefines.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable( EyesWatcher ${EW_SOURCES} ${EW_WX_SOURCES} ${EW_HEADERS} ${EW_WX_HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeDefines.h)
target_link_libraries( EyesWatcher ${wxWidgets_LIBRARIES})
add_dependencies(EyesWatcher IsHereCmd)

########################################################################
# Install
########################################################################

set(DEST_RUNTIME_DIR bin)

set(CASCADE_DIR cascades)
set(ICONS_DIR icons)

file(GLOB DATA_CASCADE ${EW_BASE}/data/${CASCADE_DIR}/*)
file(GLOB DATA_ICONS ${EW_BASE}/data/${ICONS_DIR}/*)
set(DATA_SOUND ${EW_BASE}/data/beep-1.wav)


install(TARGETS IsHereCmd RUNTIME DESTINATION ${DEST_RUNTIME_DIR})
install(TARGETS EyesWatcher RUNTIME DESTINATION ${DEST_RUNTIME_DIR})

install(FILES ${DATA_CASCADE} DESTINATION ${DEST_DATA_DIR}/${CASCADE_DIR}/)
install(FILES ${DATA_ICONS} DESTINATION ${DEST_DATA_DIR}/${ICONS_DIR}/)
install(FILES ${DATA_SOUND} DESTINATION ${DEST_DATA_DIR}/)

# @todo install readme
# @todo install install_manifest.txt so that it could be uninstalled ?

########################################################################
# CPack Configuration
########################################################################
# (http://www.cmake.org/Wiki/CMake:Packaging_With_CPack#Using_CPack_with_CMake)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Eyes Watcher")
set(CPACK_PACKAGE_VENDOR "Robert Morin")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${EW_BASE}/readme.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${EW_BASE}/license.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

# @todo ?
set(CPACK_PACKAGE_INSTALL_DIRECTORY "EyesWatcher")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  set(CPACK_PACKAGE_ICON "${EW_BASE}/Data/icons\\\\webcam.ico")
  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\EyesWatcher.exe")
  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Eyes Watcher")
  #set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
  #set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  #set(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
  set(CPACK_NSIS_MUI_ICON "${EW_BASE}/Data/icons\\\\webcam.ico")
  set(CPACK_NSIS_MUI_UNIICON "${EW_BASE}/Data/icons\\\\webcam.ico")
  set(CPACK_NSIS_MENU_LINKS "programs\\EyesWatcher" "EyesWatcher")
  set(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  set(CPACK_STRIP_FILES "bin/EyesWatcher")
  set(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
set(CPACK_PACKAGE_EXECUTABLES "EyesWatcher" "Eyes Watcher")

include(CPack)
