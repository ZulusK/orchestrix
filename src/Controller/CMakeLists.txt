cmake_minimum_required(VERSION 3.5.2)

include_directories(include)

set(CMAKE_CXX_STANDARD 11)
file(GLOB LIB_SOURCES "src/*.cpp")

project(controller)

include_directories(include)
add_executable(${CMAKE_PROJECT_NAME} "main.cpp" ${LIB_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase ssl)