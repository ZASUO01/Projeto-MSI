cmake_minimum_required(VERSION 4.2)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "arcana_digitalis")
project(${PROJECT_NAME})

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
        Source/Main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        include
        External
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        GLEW::GLEW
        OpenGL::GL
        SDL2::SDL2
)