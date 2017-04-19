cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_BUILD_TYPE Release)

#file(GLOB SOURCE_FILES "src/main1.c" "src/wavProcess.c")
#
#set(CMAKE_C_STANDARD 99)
#project(orchestrix)
#include_directories(src/include)
#
#add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} src/include/wave.h src/wavProcess.c src/test.cpp)
#target_link_libraries(${CMAKE_PROJECT_NAME} openal alut progbase)

project(orchestrix)
include_directories(include)
include_directories(usr/local/include)

file(GLOB AUDIO_WORK_SOURCE "src/equalizer.cpp" "src/audio/audioSpectrum.cpp" "src/audio/player.cpp" "src/audio/wavFile.cpp")
file(GLOB EQ_SOURCE "src/equalizer.cpp" "include/equalizer.h")

add_executable(a.out src/main.cpp ${AUDIO_WORK_SOURCE} ${EQ_SOURCE} src/audioPlayer/AudioPlayer.cpp src/audioPlayer/AudioPlayer.h src/audioPlayer/AudioFile.cpp src/audioPlayer/AudioFile.h)
target_link_libraries(a.out sndfile)
target_link_libraries(a.out openal)
target_link_libraries(a.out alut)
target_link_libraries(a.out fftw3)
target_link_libraries(a.out progbase)