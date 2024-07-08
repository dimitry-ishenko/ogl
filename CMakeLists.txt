cmake_minimum_required(VERSION 3.16) # focal
project(ogl VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(HEADERS
    ogl/color.hpp
    ogl/core.hpp
    ogl/error.hpp
    ogl/extern.hpp
    ogl/types.hpp
    ogl/vec.hpp
    ogl/window.hpp
)
set(MAIN_HEADER ogl.hpp)

set(SOURCES
    src/common.ipp
    src/core.cpp
    src/error.cpp
    src/window.cpp
)

add_library(ogl SHARED ${HEADERS} ${SOURCES})
target_link_libraries(ogl PUBLIC glfw OpenGL::GL GLEW::glew)
