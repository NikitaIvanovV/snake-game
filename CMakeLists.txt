project(Snake)
cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wall -g -Linclude")

include_directories(AFTER include)

add_library(core OBJECT src/core.c)
add_library(utils OBJECT src/utils.c)
add_library(map OBJECT src/map.c)
add_library(render OBJECT src/render.c)
add_library(vector OBJECT src/vector.c)

add_library(snake STATIC)

target_link_libraries(snake core)
target_link_libraries(snake utils)
target_link_libraries(snake map)
target_link_libraries(snake render)
target_link_libraries(snake SDL2)
target_link_libraries(snake vector)

add_executable(main src/main.c)

target_link_libraries(main snake)
