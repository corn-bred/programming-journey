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

set_target_properties( ${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_include_directories( ${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_directories( ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries( ${PROJECT_NAME} PRIVATE 
    glfw3 
    opengl32 
    gdi32 
    OpenAL32
)

option(STATIC_BUILD "Statically build the executable" OFF)

if (STATIC_BUILD)
    target_link_options ( ${PROJECT_NAME} PRIVATE 
        -static
        -static-libgcc 
        -static-libstdc++
    )
    set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    message(STATUS "Building statically-linked executable")
else()
    message(STATUS "Building dynamically-linked executable")
endif()