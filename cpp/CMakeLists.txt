# Top-level CMake file

cmake_minimum_required (VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)

project (io-main)

# Build options
option (BUILD_SHARED_LIBS "Build shared libraries" OFF)
option (BUILD_TESTING "Build unit tests" OFF)

# Include sub-projects
add_subdirectory ("IO")

# Add testing if necessary
if (BUILD_TESTING)
	enable_testing ()
endif()

add_executable (io-main main.cpp "Common/types.h" "Common/constants.h")
target_link_libraries (io-main PUBLIC Readers)