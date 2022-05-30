# Zip module CMake file

# Add source code to IO library and link with zlib
add_library (zip STATIC "include/IZip.h" "include/GZip.h" "src/GZip.cpp")
target_link_libraries (zip PUBLIC zlib)

# Include location of zlib binary
target_include_directories (zip PUBLIC "${PROJECT_BINARY_DIR}/External/zlib")

# if (BUILD_SHARED_LIBS)

# Add testing if necessary
if (BUILD_TESTING)

	enable_testing ()

	# Add executable for unit tests
	add_executable (zip-tests "test/test_gzip.cpp" "../Common/test_utils.h" "../Common/test_utils.cpp")

	# Link library
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		target_link_libraries (zip-tests PUBLIC zip ${GTEST} ${GTEST_MAIN})
	else()
		target_link_libraries (zip-tests PUBLIC zip GTest::gtest GTest::gtest_main)
	endif()

	# Add GoogleTest so that Visual Studio can add tests to Test Explorer
	gtest_discover_tests (zip-tests)

endif()