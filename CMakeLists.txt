cmake_minimum_required(VERSION 3.22.1)

project(OpenGlProject)

set(CMAKE_CXX_STANDARD 17)

#OPENGL
find_package(OpenGL REQUIRED)

# GLEW
find_path(GLEW_INCLUDE_DIR /lib/glew/include/GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew32s PATH_SUFFIXES lib64)
find_package(GLEW REQUIRED)

set(CMAKE_PREFIX_PATH "lib/glew")
set(CMAKE_LIBRARY_PATH "lib/")

#GLFW
add_subdirectory(
                lib/glfw/ 
                lib/glfw/src
)

#Source files
set(SOURCES 
    #Source
    ${CMAKE_SOURCE_DIR}/src/Source.cpp
    ${CMAKE_SOURCE_DIR}/src/Camera/Camera.cpp
    ${CMAKE_SOURCE_DIR}/src/Camera/Camera.hpp
    ${CMAKE_SOURCE_DIR}/src/Planets/Planets.cpp
    ${CMAKE_SOURCE_DIR}/src/Planets/Planets.hpp
    ${CMAKE_SOURCE_DIR}/src/Shaders/Shaders.cpp
    ${CMAKE_SOURCE_DIR}/src/Shaders/Shaders.hpp
)

#Exec
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

#Targets
target_link_libraries(${CMAKE_PROJECT_NAME} glfw GLEW)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL)