# IO module CMake file

# Add source to this project's executable
add_library (Readers STATIC "src/BaseReader.cpp" "src/NRRDReader.cpp")

# Add libraries
#find_library (TF NAMES tensorflow_cc PATHS "${TF_LIB_DIR}/src")

#target_link_libraries (train json utils ${TF} ${PROTOBUF})

# if (BUILD_SHARED_LIBS)

# Add testing if necessary
if (BUILD_TESTING)
	add_subdirectory ("test")
endif()