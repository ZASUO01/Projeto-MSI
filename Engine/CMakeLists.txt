cmake_minimum_required(VERSION 4.2)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "Game-Engine")
project(${PROJECT_NAME})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE ENGINE_SOURCES "*.cpp" "*.h" "*.hpp")

add_library(Engine STATIC ${ENGINE_SOURCES})

target_include_directories(Engine SYSTEM PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../External
)

target_link_libraries(Engine PUBLIC
        GLEW::GLEW
        OpenGL::GL
        SDL2::SDL2
        SDL2_image::SDL2_image
)