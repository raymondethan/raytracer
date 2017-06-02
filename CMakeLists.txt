cmake_minimum_required(VERSION 3.6.2)
project (raytracer)
set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 11)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(raytracer ${SOURCES})
