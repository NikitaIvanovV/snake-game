project(Snake)
cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wall -g -Linclude")

include_directories(AFTER include)

add_executable(main src/main.c)
add_library(core src/core.c)
add_library(utils src/utils.c)
add_library(map src/map.c)
add_library(render src/render.c)
add_library(vector src/vector.c)

target_link_libraries(main core)
target_link_libraries(main utils)
target_link_libraries(main map)
target_link_libraries(main render)
target_link_libraries(main SDL2)

target_link_libraries(map utils)
target_link_libraries(map vector)
