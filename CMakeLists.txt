cmake_minimum_required(VERSION 3.10)

project(AustLanguage VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)
include_directories(src)

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

# Create executable
add_executable(aust ${SOURCES})
