cmake_minimum_required(VERSION 3.23)
project(apue)
set(CMAKE_C_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/lib/lib.out)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./chapter8)
add_executable(test chapter8/test.c)
add_executable(fork_ch8_1 chapter8/fork_ch8_1.c)
