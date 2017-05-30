cmake_minimum_required(VERSION 2.8.9)

include_directories(.)
file(GLOB LIB_SOURCES "*.cpp")

project(controller)
# to build executable target with name a.out
add_executable(${CMAKE_PROJECT_NAME} "main.cpp" ${LIB_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} pthread)