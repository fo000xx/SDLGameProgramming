cmake_minimum_required(VERSION 3.25.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(optimizedloading)

find_package(SDL2 REQUIRED)
include_directories($SDL2_INCLUDE_DIRS)

add_executable(optimizedloading 05_optimized_loading.cpp)
target_link_libraries(optimizedloading ${SDL2_LIBRARIES})