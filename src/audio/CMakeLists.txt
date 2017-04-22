cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_BUILD_TYPE Release)

project(orchestrix)
include_directories(include)
include_directories(include/AudioManagement)
include_directories(usr/local/include)
#add path to bin source
#set(EXECUTABLE_OUTPUT_PATH "bin")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "bin")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

file(GLOB AUDIO_PLAYER_SOURCE "src/AudioManagement/*.cpp")
file(GLOB HEADERS "include/AudioManagement/*.h")

add_executable(a.out src/main.cpp ${HEADERS} ${AUDIO_PLAYER_SOURCE})

target_link_libraries(a.out sndfile)
target_link_libraries(a.out openal)
target_link_libraries(a.out alut)
target_link_libraries(a.out fftw3)
target_link_libraries(a.out progbase)
#gnome-terminal --tab -e "/bin/bash -c 'valgrind --leak-check=yes ./a.out; exec /bin/bash -i'"