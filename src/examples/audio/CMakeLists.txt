cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
include_directories(include)

file(GLOB AUDIO_SOURCE "src/audio/*.cpp" "include/audio/*.h")
file(GLOB EQ_SOURCE "src/graphic/*.cpp" "include/graphic/*.h")

project(a.out)
add_executable(${CMAKE_PROJECT_NAME} main.cpp ${AUDIO_SOURCE} ${EQ_SOURCE})
target_link_libraries(${CMAKE_PROJECT_NAME} sndfile)
target_link_libraries(${CMAKE_PROJECT_NAME} /usr/local/lib/libbass.so)
target_link_libraries(${CMAKE_PROJECT_NAME} openal)
target_link_libraries(${CMAKE_PROJECT_NAME} alut)
target_link_libraries(${CMAKE_PROJECT_NAME} fftw3)
target_link_libraries(${CMAKE_PROJECT_NAME} pthread)
target_link_libraries(${CMAKE_PROJECT_NAME} progbase-cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} progbase)
#gnome-terminal --tab -e "/bin/bash -c 'valgrind --leak-check=yes ./a.out; exec /bin/bash -i'"
#add path to bin source
