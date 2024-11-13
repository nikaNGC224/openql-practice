cmake_minimum_required(VERSION 3.10)
project(graphic_program)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS} ${GLUT_LIBRARY_DIRS})
add_definitions(${OPENGL_DEFINITIONS} ${GLUT_DEFINITIONS})

add_executable(graphic_program
    src/main.cpp
    src/graphic_program.cpp
)
target_link_libraries(graphic_program ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
