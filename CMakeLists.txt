cmake_minimum_required(VERSION 3.10)
project(opengl_practice)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS} ${GLUT_LIBRARY_DIRS})
add_definitions(${OPENGL_DEFINITIONS} ${GLUT_DEFINITIONS})

add_executable(opengl_practice main.cpp)
target_link_libraries(opengl_practice ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})