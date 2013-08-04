# Source : https://github.com/erwincoumans/rbdl/blob/master/CMake/FindUnitTest%2B%2B.cmake
# Modded because I prefer cache variables and to work in windows

# - Try to find UnitTest++
#
#

SET(UNITTESTXX_PATH "" CACHE PATH "UnitTest root path.")
SET (UNITTEST++_FOUND FALSE)

FIND_PATH (UNITTEST++_INCLUDE_DIR UnitTest++.h ${UNITTESTXX_PATH} PATH_SUFFIXES
	"" unittest++ src include/unittest++ DOC "UnitTest++ header location.")
FIND_LIBRARY (UNITTEST++_LIBRARY UnitTest++ ${UNITTESTXX_PATH} PATH_SUFFIXES
	"" Release lib DOC "UnitTest++ library location.")

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
