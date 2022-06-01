# IO module CMake file

# Add source code to IO library and link with zlib
add_library (IO STATIC "src/BaseReader.cpp" "src/NRRDReader.cpp" "include/IO_utils.h" "src/IO_utils.cpp" "include/NIfTIReader.h")

# Add libraries
#find_library (TF NAMES tensorflow_cc PATHS "${TF_LIB_DIR}/src")

#target_link_libraries (train json utils ${TF} ${PROTOBUF})

# if (BUILD_SHARED_LIBS)

# Add testing if necessary
if (BUILD_TESTING)

	enable_testing ()

	# Add executable for unit tests
	add_executable (IO-tests "test/test_NRRD.cpp" "test/test_IO_utils.cpp" "include/IO_utils.h" "src/IO_utils.cpp" "include/NIfTIReader.h")

	# Link library
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		target_link_libraries (IO-tests PUBLIC IO ${GTEST} ${GTEST_MAIN})
	else()
		target_link_libraries (IO-tests PUBLIC IO GTest::gtest GTest::gtest_main)
	endif()

	# Add GoogleTest so that Visual Studio can add tests to Test Explorer
	gtest_discover_tests (IO-tests)

endif()