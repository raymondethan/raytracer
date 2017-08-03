cmake_minimum_required(VERSION 3.6.2)
project (raytracer)
set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 11)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(raytracer ${SOURCES})

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3")        ## Optimize
endif()
