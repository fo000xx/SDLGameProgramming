cmake_minimum_required(VERSION 3.25.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(displayimage)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(displayimage 02_display_image.cpp)
target_link_libraries(displayimage ${SDL2_LIBRARIES})