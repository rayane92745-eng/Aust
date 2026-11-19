cmake_minimum_required(VERSION 3.10)
project(AustLanguage VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(aust main.cpp)
