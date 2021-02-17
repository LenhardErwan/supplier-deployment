cmake_minimum_required(VERSION 3.0.0)
project(SupplierDeployment VERSION 0.1.0)

# Project
project(ShapEditor VERSION 0.1.0)
set(CMAKE_PROJECT_NAME  ${PROJECT_NAME})
set(CMAKE_PROJECT_VERSION  ${PROJECT_VERSION})

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