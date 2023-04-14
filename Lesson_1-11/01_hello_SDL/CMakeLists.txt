cmake_minimum_required(VERSION 3.25.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(hellosdl)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(hellosdl 01_hello_SDL.cpp)
target_link_libraries(hellosdl ${SDL2_LIBRARIES})