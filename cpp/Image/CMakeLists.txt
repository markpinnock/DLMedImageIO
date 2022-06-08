# Image module CMake file

# Add source code to image library
add_library (image STATIC "src/Image.cpp" "include/BaseHeader.h")

# Add libraries
#find_library (TF NAMES tensorflow_cc PATHS "${TF_LIB_DIR}/src")

#target_link_libraries (train json utils ${TF} ${PROTOBUF})

# if (BUILD_SHARED_LIBS)

# Add testing if necessary
if (BUILD_TESTING)

	enable_testing ()

	# Add executable for unit tests
	add_executable (image-tests "test/test_Image.cpp" "include/BaseHeader.h")

	# Link library
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		target_link_libraries (image-tests PUBLIC image ${GTEST} ${GTEST_MAIN})
	else()
		target_link_libraries (image-tests PUBLIC image GTest::gtest GTest::gtest_main)
	endif()

	# Add GoogleTest so that Visual Studio can add tests to Test Explorer
	gtest_discover_tests (image-tests)

endif()