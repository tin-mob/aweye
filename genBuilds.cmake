set(BUILD_DIR bin)
set(EW_DIR ${BUILD_DIR}/ew)
set(EW_TEST_DIR ${BUILD_DIR}/ew-test)

file(MAKE_DIRECTORY ${BUILD_DIR})
file(MAKE_DIRECTORY ${EW_DIR})
file(MAKE_DIRECTORY ${EW_TEST_DIR})

file(COPY CMakeLists.txt DESTINATION ${EW_DIR})
configure_file(CMakeTest.txt ${EW_TEST_DIR}/CMakeLists.txt COPYONLY)
