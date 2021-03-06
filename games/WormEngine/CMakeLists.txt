cmake_minimum_required(VERSION 3.2)
project(WormEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(WormEngine ${SOURCE_FILES})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif(CMAKE_BUILD_TYPE)

find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(FreeImage REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glfw ${GLM_INCLUDE_DIR} ${FREE_IMAGE_INCLUDE_DIR})
target_link_libraries(WormEngine ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} glfw ${FREE_LIBRARIES})

file(COPY res DESTINATION ./)
