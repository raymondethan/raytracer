SET (CMAKE_CXX_COMPILER "/usr/local/bin/g++-7")
cmake_minimum_required(VERSION 3.6.2)
project (raytracer)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(raytracer ${SOURCES})

set(CMAKE_CXX_FLAGS "-v")
## Compiler flags
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-std=c++1z")
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Ofast")
endif()
