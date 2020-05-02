cmake_minimum_required(VERSION 3.0)
project(raylib_template C)

set(CMAKE_C_STANDARD 99)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)

add_executable(raylib_template 
    src/main.c
    src/shapes.c
    src/draw_trolley.c
    src/leftside_logic.c
    src/leftside_graphics.c
    src/trolley_state.c
    src/trolley_logic.c
    src/draw_cache.c
    src/audio.c
    src/timer.c
)
target_link_libraries(raylib_template PRIVATE raylib)