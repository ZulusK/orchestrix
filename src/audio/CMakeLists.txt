cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


include_directories(include)
include_directories(include/AudioManagement)
include_directories(/usr/local/include)
install(
        DIRECTORY include/AudioManagement DESTINATION /usr/local/include/
        FILES_MATCHING PATTERN "*.h"
)
install(
        DIRECTORY include/SpectrumManagement DESTINATION /usr/local/include/
        FILES_MATCHING PATTERN "*.h"
)

file(GLOB AUDIO_PLAYER_SOURCE "src/AudioManagement/*.cpp" "include/AudioManagement/*.h")
file(GLOB SPECTRUM_SOURCE "src/SpectrumManagement/*.cpp" "include/SpectrumManagement/*.h")
project(aut)
add_library(${CMAKE_PROJECT_NAME} STATIC ${AUDIO_PLAYER_SOURCE} ${SPECTRUM_SOURCE} ${HEADERS})
target_link_libraries(${CMAKE_PROJECT_NAME} sndfile)
target_link_libraries(${CMAKE_PROJECT_NAME} /usr/local/lib/libbass.so)
target_link_libraries(${CMAKE_PROJECT_NAME} openal)
target_link_libraries(${CMAKE_PROJECT_NAME} alut)
target_link_libraries(${CMAKE_PROJECT_NAME} fftw3)
target_link_libraries(${CMAKE_PROJECT_NAME} pthread)
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/lib)

project(orchestrix)
add_executable(a.out src/main.cpp ${HEADERS})
target_link_libraries(a.out aut)
#target_link_libraries(a.out sndfile)
#target_link_libraries(a.out openal)
#target_link_libraries(a.out alut)
#target_link_libraries(a.out fftw3)
target_link_libraries(a.out progbase)
#target_link_libraries(a.out pthread)
#gnome-terminal --tab -e "/bin/bash -c 'valgrind --leak-check=yes ./a.out; exec /bin/bash -i'"
#add path to bin source
#set(EXECUTABLE_OUTPUT_PATH "bin")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "bin")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
