cmake_minimum_required(VERSION 3.6)
project(Console-fx)

set(CMAKE_CXX_STANDARD 98)

file(GLOB_RECURSE CONSOLE_SOURCES "Console/Sources/*.cpp")
file(GLOB_RECURSE CONSOLE_HEADERS "Console/Headers/*.h")

file(GLOB_RECURSE EIGENMATH_HEADERS "Eigenmath/Headers/*.h")
file(GLOB_RECURSE EIGENMATH_SOURCES "Eigenmath/Sources/*.cpp")

set(SOURCE_FILES main.cpp graphics.h ${CONSOLE_HEADERS} ${CONSOLE_SOURCES} ${EIGENMATH_HEADERS} ${EIGENMATH_SOURCES})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)
