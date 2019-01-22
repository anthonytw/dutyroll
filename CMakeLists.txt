cmake_minimum_required(VERSION 3.10)
project(dutyroll)

# Do not allow in-source builds:
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find packages.
include(FindThreads REQUIRED)
find_package(OpenMP 3.1)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_subdirectory(external/eigen-3.3.7)
message(STATUS "Eigen at ${Eigen3_SOURCE_DIR}")
add_subdirectory(external/pybind11-2.2.4)

#find_package(PythonExtensions REQUIRED)

pybind11_add_module(_dutyroll MODULE src/rollduty.cpp src/python_wrappers.cpp)
target_include_directories(_dutyroll PRIVATE ${Eigen3_SOURCE_DIR})
install(TARGETS _dutyroll LIBRARY DESTINATION dutyroll)
