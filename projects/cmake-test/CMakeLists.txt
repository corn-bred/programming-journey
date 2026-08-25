cmake_minimum_required(VERSION 4.0)

project(CornJam)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/misc/glad.c 
    src/misc/shaders.cpp 
    src/game.cpp 
    src/scenes.cpp 
    src/misc/collision.cpp 
    src/misc/utility.cpp 
    src/globals.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE 
    include/${CMAKE_CURRENT_SOURCE_DIR})

    