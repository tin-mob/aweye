# Sources : https://github.com/erwincoumans/rbdl/blob/master/CMake/FindUnitTest%2B%2B.cmake
# and https://github.com/libamqp/libamqp/blob/develop/FindUnitTest%2B%2B.cmake

# - Try to find UnitTest++
#
#

SET(UNITTESTXX_PATH "" CACHE PATH "UnitTest root path.")
SET (UNITTEST++_FOUND FALSE)

FIND_PATH (UNITTEST++_INCLUDE_DIR UnitTest++.h ${UNITTESTXX_PATH} PATH_SUFFIXES
	"" unittest++ src include/unittest++ DOC "UnitTest++ header location.")
FIND_LIBRARY (UNITTEST++_RELEASE_LIBRARY
	NAMES UnitTest++ UnitTest++.vsnet2005 UnitTest++.vsnet2008
	PATHS ${UNITTESTXX_PATH} PATH_SUFFIXES
	"" Release lib DOC "UnitTest++ library location.")
	
# Windows is harder (hopefully if finds the debug version, since both have the same name)
IF (WIN32)
	FIND_LIBRARY (UNITTEST++_DEBUG_LIBRARY
		NAMES UnitTest++ UnitTest++.vsnet2005 UnitTest++.vsnet2008
		PATHS ${UNITTESTXX_PATH} PATH_SUFFIXES
		"" Debug lib DOC "UnitTest++ library location.")
ENDIF (WIN32)

IF (WIN32)
	SET(UNITTEST++_LIBRARY optimized ${UNITTEST++_RELEASE_LIBRARY} debug ${UNITTEST++_DEBUG_LIBRARY})
ELSE (WIN32)
	SET(UNITTEST++_LIBRARY ${UNITTEST++_RELEASE_LIBRARY})
ENDIF (WIN32)

IF (UNITTEST++_INCLUDE_DIR AND UNITTEST++_LIBRARY)
	SET (UNITTEST++_FOUND TRUE)
ENDIF (UNITTEST++_INCLUDE_DIR AND UNITTEST++_LIBRARY)

IF (UNITTEST++_FOUND)
   IF (NOT UnitTest++_FIND_QUIETLY)
      MESSAGE(STATUS "Found UnitTest++: ${UNITTEST++_LIBRARY}")
   ENDIF (NOT UnitTest++_FIND_QUIETLY)
ELSE (UNITTEST++_FOUND)
   IF (UnitTest++_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find UnitTest++. Try to set UNITTESTXX_PATH.")
   ENDIF (UnitTest++_FIND_REQUIRED)
ENDIF (UNITTEST++_FOUND)

MARK_AS_ADVANCED (
	UNITTEST++_INCLUDE_DIR
	UNITTEST++_LIBRARY
	)
