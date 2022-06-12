# Top-level CMake file

cmake_minimum_required (VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

project (DLIO VERSION 0.0.0)

# Build options
option (BUILD_SHARED_LIBS "Build shared libraries" OFF)
option (BUILD_TESTING "Build unit tests" ON)
option (USE_EIGEN "Build with Eigen library" OFF)

# Configuration file
configure_file ("Config.h.in" "Config.h")

# Add testing if necessary
if (BUILD_TESTING)

	enable_testing ()

	# Include and library directories
	set (GTEST_INCLUDE_DIR "C:/include")
	set (GTEST_LIB_DIR "C:/lib")
	include_directories (${GTEST_INCLUDE_DIR})

	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		# Add libraries for tests
		find_library (GTEST NAMES gtestd PATHS ${GTEST_LIB_DIR})
		find_library (GTEST_MAIN NAMES gtest_maind PATHS ${GTEST_LIB_DIR})

	else()
		set (GTEST_ROOT "C:/Users/roybo/Cpp/googletest/build/lib/RelWithDebInfo")
		find_package (GTest REQUIRED)

	endif()

	# Add GoogleTest so that Visual Studio can add tests to Test Explorer
	include (GoogleTest)

endif()

# Include modules
add_subdirectory ("Image")
add_subdirectory ("IO")
add_subdirectory ("Zip")

# Include third party libraries
add_subdirectory ("External")

add_executable (io-main "main.cpp" "Common/types.h" "Common/constants.h" "Common/test_utils.h" "Common/test_utils.cpp" "Common/ArrayUtils.h" "Image/include/NIfTIHeader.h")
target_link_libraries (io-main PUBLIC IO image zip)
#target_link_libraries (io-main PUBLIC EXTERNAL_LIBS)
target_include_directories (io-main PUBLIC ${PROJECT_BINARY_DIR} ${EXTRA_INCLUDES})

add_executable (cv-test opencv-test.cpp)
find_library (OPENCV NAMES "opencv_world455d" PATHS "C:/Users/roybo/Cpp/opencv/build/x64/vc15/lib")
target_link_libraries (cv-test IO image zip ${OPENCV})
