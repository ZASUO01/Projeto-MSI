cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "arcana_digitalis")
project(${PROJECT_NAME})

add_subdirectory("Engine" "${CMAKE_CURRENT_BINARY_DIR}/Engine")

add_executable(${PROJECT_NAME}
        Main.cpp
        Source/GameMain.h
        Source/GameMain.cpp

)

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)
