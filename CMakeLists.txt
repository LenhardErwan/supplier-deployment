cmake_minimum_required(VERSION 3.0.0)

# Project
project(SupplierDeployment VERSION 0.1.0)
set(CMAKE_PROJECT_NAME ${PROJECT_NAME})
set(CMAKE_PROJECT_VERSION ${PROJECT_VERSION})

# Output dir
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin CACHE
	PATH "Directory where .exe and .dll files are dumped." FORCE)

# All app files
file(
		GLOB_RECURSE
		source_files
	src/*
	include/SupplierDeployment/*
)

add_executable(SupplierDeployment ${source_files})

# Include app directory
include_directories(include/SupplierDeployment)

# Include GLPK
if (NOT GLPK_FOUND)

	# first look in user defined locations
	find_path(GLPK_INCLUDE_DIR
		NAMES glpk.h
		PATHS /usr/include/
		ENV GLPK_INC_DIR
	)

	find_library(GLPK_LIBRARIES
		NAMES libglpk glpk
		PATHS ENV LD_LIBRARY_PATH
				ENV LIBRARY_PATH
				/usr/lib/x86_64-linux-gnu
				${GLPK_INCLUDE_DIR}/../lib
			ENV GLPK_LIB_DIR
	)

	if(GLPK_LIBRARIES AND GLPK_INCLUDE_DIR)
		set(GLPK_FOUND TRUE)
	endif()

endif()
include_directories(${GLPK_INCLUDE_DIR})
link_directories(${GLPK_LIB})
target_link_libraries(${PROJECT_NAME} ${GLPK_LIBRARIES})
