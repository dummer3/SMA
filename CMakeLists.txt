# Define the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.19)

# Define the project name
project(sma VERSION 1.0)

# Define the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g)

# Add the sources
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")
list(REMOVE_ITEM LIB_SOURCES "src/main.cpp" "src/test.cpp")

file(GLOB_RECURSE LIB_HEADERS "includes/*.hpp")

add_library(smalib ${LIB_SOURCES} ${LIB_HEADERS})

# Define the executable
add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME}_test src/test.cpp)

# Define the include directories
target_link_libraries(${PROJECT_NAME} smalib)
target_link_libraries(${PROJECT_NAME}_test smalib)
