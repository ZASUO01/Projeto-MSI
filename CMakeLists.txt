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
        Engine/Renderer/VertexArray.cpp
        Engine/Renderer/VertexArray.h
        Engine/Renderer/Mesh.cpp
        Engine/Renderer/Mesh.h
        Engine/Utils/ObjectLoader.cpp
        Engine/Utils/ObjectLoader.h
        Engine/Renderer/Texture.cpp
        Engine/Renderer/Texture.h
        Engine/Renderer/Renderer.cpp
        Engine/Renderer/Renderer.h
        Engine/Actors/Actor.cpp
        Engine/Actors/Actor.h
        Engine/Utils/JsonUtil.cpp
        Engine/Utils/JsonUtil.h
        Engine/Renderer/Model.cpp
        Engine/Renderer/Model.h
)

target_link_libraries(Engine PUBLIC
        GLEW::GLEW
        OpenGL::GL
        SDL2::SDL2
        SDL2_image::SDL2_image
)

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/External
)

add_executable(${PROJECT_NAME}
        Main.cpp
        Source/GameMain.cpp
        Source/GameMain.h
        Source/Actors/Cube.cpp
        Source/Actors/Cube.h
        Engine/Components/Component.cpp
        Engine/Components/Component.h
        Engine/Components/Drawing/ModelComponent.cpp
        Engine/Components/Drawing/ModelComponent.h
        External/nlohmann/json.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)