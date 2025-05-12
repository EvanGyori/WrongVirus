cmake_minimum_required(VERSION 3.20)
project(WrongVirus LANGUAGES CXX)

find_package(glfw NAMES GLFW glfw3 REQUIRED)


add_executable(blackOps2 main.cpp)
target_link_libraries(blackOps2 PRIVATE glfw "${CMAKE_SOURCE_DIR}/glew32s.lib" "${CMAKE_SOURCE_DIR}/OpenGL32.Lib")
