cmake_minimum_required(VERSION 3.25.2)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(mouseEvents)
add_executable(mouseEvents main.cpp LWindow.cpp LTexture.cpp LButton.cpp)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(mouseEvents ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})