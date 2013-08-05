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

if(WIN32)
	set(DEST_RUNTIME_DIR ".")
else(WIN32)
	set(DEST_RUNTIME_DIR bin)
endif(WIN32)
set(CASCADE_DIR cascades)
set(ICONS_DIR icons)

file(GLOB DATA_CASCADE ${CMAKE_SOURCE_DIR}/data/${CASCADE_DIR}/*)
file(GLOB DATA_ICONS ${CMAKE_SOURCE_DIR}/data/${ICONS_DIR}/*)
set(DATA_SOUND ${CMAKE_SOURCE_DIR}/data/beep-1.wav)


install(TARGETS IsHereCmd RUNTIME DESTINATION ${DEST_RUNTIME_DIR})
install(TARGETS Aweye RUNTIME DESTINATION ${DEST_RUNTIME_DIR})

if(${DEST_DATA_DIR})
	install(FILES ${DATA_CASCADE} DESTINATION ${DEST_DATA_DIR}/${CASCADE_DIR}/)
	install(FILES ${DATA_ICONS} DESTINATION ${DEST_DATA_DIR}/${ICONS_DIR}/)
	install(FILES ${DATA_SOUND} DESTINATION ${DEST_DATA_DIR}/)
else(${DEST_DATA_DIR})
	install(FILES ${DATA_CASCADE} DESTINATION ${CASCADE_DIR}/)
	install(FILES ${DATA_ICONS} DESTINATION ${ICONS_DIR}/)
	install(FILES ${DATA_SOUND} DESTINATION ".")
endif(${DEST_DATA_DIR})

# @todo install readme
# @todo install install_manifest.txt so that it could be uninstalled ?

########################################################################
# uninstall
########################################################################

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.in.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake)

########################################################################
# CPack Configuration
########################################################################
# (http://www.cmake.org/Wiki/CMake:Packaging_With_CPack#Using_CPack_with_CMake)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Aweye")
set(CPACK_PACKAGE_DESCRIPTION "Watches your eyes and reminds you to take a break.")
set(CPACK_PACKAGE_CONTACT "Robert Morin tin.mob.error@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/license.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "Aweye")
IF(WIN32 AND NOT UNIX)
	# @todo this
	set(CPACK_GENERATOR "ZIP;NSIS")
	file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}\\\\data/icons/webcam.ico" ICON_PATH)
	
	# There is a bug in NSI that does not handle full unix paths properly. Make
	# sure there is at least one set of four (4) backlasshes.
	
	set(CPACK_PACKAGE_ICON ${ICON_PATH})
	set(CPACK_NSIS_INSTALLED_ICON_NAME "Aweye.exe")
	set(CPACK_NSIS_DISPLAY_NAME "Aweye")
	set(CPACK_NSIS_HELP_LINK "https://github.com/tin-mob/aweye")
	set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/tin-mob/aweye")
	set(CPACK_NSIS_CONTACT "tin.mob.error@gmail.com")
	set(CPACK_NSIS_MUI_ICON ${ICON_PATH})
	set(CPACK_NSIS_MUI_UNIICON ${ICON_PATH})
	set(CPACK_NSIS_MENU_LINKS "programs\\\\Aweye" "Aweye")
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
