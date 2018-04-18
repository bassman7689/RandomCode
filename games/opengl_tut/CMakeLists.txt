cmake_minimum_required(VERSION 3.2)
project(OpenGLTut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES "*.cpp")
add_executable(OpenGLTut ${SOURCE_FILES})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(soil REQUIRED)
find_package(glm REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glfw ${SOIL_INCLUDE_DIR})
target_link_libraries(OpenGLTut ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} glfw ${SOIL_LIBRARIES})
