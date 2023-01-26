# Define the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.19)

# Define the project name
project(sma VERSION 1.0)

# Define the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Define the include directories
target_include_directories(${PROJECT_NAME} PUBLIC includes)