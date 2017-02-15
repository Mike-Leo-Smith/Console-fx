cmake_minimum_required(VERSION 3.6)
project(Console_fx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -v")
set(CMAKE_CXX_STANDARD 98)

file(GLOB_RECURSE CONSOLE_SOURCES "Console/Sources/*.cpp")
file(GLOB_RECURSE CONSOLE_HEADERS "Console/Headers/*.h")

set(SOURCE_FILES main.cpp ${CONSOLE_HEADERS} ${CONSOLE_SOURCES})
add_executable(Console_fx ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} glfw)