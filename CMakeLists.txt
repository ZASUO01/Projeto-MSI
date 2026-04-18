cmake_minimum_required(VERSION 4.2)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "arcana_digitalis")
project(${PROJECT_NAME})

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
        Source/Main.cpp
        Source/Game.cpp
        Source/Game.h
        Source/Utils/Math.cpp
        Source/Utils/Math.h
        Source/Utils/Random.cpp
        Source/Utils/Random.h
        Source/Utils/ObjectLoader.cpp
        Source/Utils/ObjectLoader.h
        External/tinyobjloader/tiny_obj_loader.h
        Source/Renderer/Shader.cpp
        Source/Renderer/Shader.h
        Source/Renderer/VertexArray.cpp
        Source/Renderer/VertexArray.h
        Source/Renderer/Renderer.cpp
        Source/Renderer/Renderer.h)

target_include_directories(${PROJECT_NAME} PUBLIC
        include
        External
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        GLEW::GLEW
        OpenGL::GL
        SDL2::SDL2
)