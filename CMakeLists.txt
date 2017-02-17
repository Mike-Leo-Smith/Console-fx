cmake_minimum_required(VERSION 3.6)
project(Console-fx)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -v")

file(GLOB_RECURSE CONSOLE_SOURCES "Console/Sources/*.cpp")
file(GLOB_RECURSE CONSOLE_HEADERS "Console/Headers/*.h")

set(SOURCE_FILES main.cpp ${CONSOLE_HEADERS} ${CONSOLE_SOURCES})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} glfw)