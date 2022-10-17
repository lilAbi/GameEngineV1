cmake_minimum_required(VERSION 3.22)

#project name and version
project(blockRPG VERSION 0.0.1)

#C++ standard needed
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=c++20 -fno-omit-frame-pointer")

#include paths
include_directories(src)
include_directories(include)

#find library on local machine |TODO: download library?
find_package(glfw3 3.3 REQUIRED)

#search for all source files and add them to target
file(GLOB SRC_FILES CONFIGURE_DEPENDS
        "src/ECS/*.cpp"
        "src/ECS/Component/*.cpp"
        "src/ECS/Entity/*.cpp"
        "src/ECS/Managers/*.cpp"
        "src/ECS/System/*.cpp"

        "src/GameEngine/*.cpp"
        "src/GameEngine/Component/*.cpp"
        "src/GameEngine/Core/*.cpp"
        "src/GameEngine/Core/Window/*.cpp"
        "src/GameEngine/System/*.cpp"

        "src/RenderEngine/*.cpp"
        "src/RenderEngine/Component/*.cpp"
        "src/RenderEngine/Core/*.cpp"
        "src/RenderEngine/System/*.cpp"

        "src/Utility/*.cpp"
        )


#adds an executable target
add_executable(blockRPG src/main.cpp src/glad.c ${SRC_FILES})
target_link_libraries(blockRPG glfw)
