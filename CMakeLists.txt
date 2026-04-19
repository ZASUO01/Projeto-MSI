cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "arcana_digitalis")
project(${PROJECT_NAME})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_library(Engine STATIC
        Engine/Game.cpp
        Engine/Game.h
        Engine/Utils/Math.cpp
        Engine/Utils/Math.h
        Engine/Utils/Random.cpp
        Engine/Utils/Random.h
        Engine/Renderer/Shader.cpp
        Engine/Renderer/Shader.h
)

target_link_libraries(Engine PUBLIC
        GLEW::GLEW
        OpenGL::GL
        SDL2::SDL2
        SDL2_image::SDL2_image
)

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderer
        ${CMAKE_CURRENT_SOURCE_DIR}/External
)

add_executable(${PROJECT_NAME}
        Main.cpp
        Source/GameMain.cpp
        Source/GameMain.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)