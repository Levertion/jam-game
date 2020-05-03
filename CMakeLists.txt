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
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ERROR_ON_UNDEFINED_SYMBOLS=0 --shell-file C:/Users/Levertion/Documents/game-dev-club/jam-game/src/shell.html")
set(CMAKE_EXECUTABLE_SUFFIX ".html")
target_link_libraries(raylib_template PRIVATE raylib)
set_target_properties(raylib_template PROPERTIES LINK_FLAGS "--preload-file C:/Users/Levertion/Documents/game-dev-club/jam-game/assets@assets")
