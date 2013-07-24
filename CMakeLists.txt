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

include(cmake/common.cmake)
include(cmake/aweyeTest.cmake)
include(cmake/aweye.cmake)

########################################################################
# Install
########################################################################

set(DEST_RUNTIME_DIR bin)
set(CASCADE_DIR cascades)
set(ICONS_DIR icons)

file(GLOB DATA_CASCADE ${CMAKE_SOURCE_DIR}/data/${CASCADE_DIR}/*)
file(GLOB DATA_ICONS ${CMAKE_SOURCE_DIR}/data/${ICONS_DIR}/*)
set(DATA_SOUND ${CMAKE_SOURCE_DIR}/data/beep-1.wav)


install(TARGETS IsHereCmd RUNTIME DESTINATION ${DEST_RUNTIME_DIR})
install(TARGETS Aweye RUNTIME DESTINATION ${DEST_RUNTIME_DIR})

install(FILES ${DATA_CASCADE} DESTINATION ${DEST_DATA_DIR}/${CASCADE_DIR}/)
install(FILES ${DATA_ICONS} DESTINATION ${DEST_DATA_DIR}/${ICONS_DIR}/)
install(FILES ${DATA_SOUND} DESTINATION ${DEST_DATA_DIR}/)

# @todo install readme
# @todo install install_manifest.txt so that it could be uninstalled ?

########################################################################
# CPack Configuration
########################################################################
# (http://www.cmake.org/Wiki/CMake:Packaging_With_CPack#Using_CPack_with_CMake)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Aweye")
set(CPACK_PACKAGE_DESCRIPTION "Looks if you spend some time away from the computer.")
set(CPACK_PACKAGE_CONTACT "Robert Morin tin.mob.error@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/license.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "Aweye")
IF(WIN32 AND NOT UNIX)
	# @todo this
	set(CPACK_GENERATOR "${CPACK_GENERATOR};NSIS")
	# There is a bug in NSI that does not handle full unix paths properly. Make
	# sure there is at least one set of four (4) backlasshes.
	set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/Data/icons\\\\webcam.ico")
	set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\Aweye.exe")
	set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Aweye")
	#set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
	#set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
	#set(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
	set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/Data/icons\\\\webcam.ico")
	set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/Data/icons\\\\webcam.ico")
	set(CPACK_NSIS_MENU_LINKS "programs\\Aweye" "Aweye")
	set(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
	set(CPACK_SET_DESTDIR ON)
	set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local" CACHE FILEPATH "Package install prefix.")
	set(CPACK_GENERATOR "TGZ;TBZ2;TZ;DEB")
	
	set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION})
	# nothing for now - wxwidgets (2.9) is compiled from source
	# (maybe static link it?)
	# and opencv lib has version in name...
	#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libwxgtk2.8-0,")

	#@todo add rpm
	
ENDIF(WIN32 AND NOT UNIX)
include(CPack)
