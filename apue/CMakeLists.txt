#cmake_minimum_required(VERSION 3.23)
#project(apue)
#set(CMAKE_C_STANDARD 11)
#
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/lib/lib.out)
#
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./chapter8)
#add_executable(test chapter8/test.c)
#add_executable(fork_ch8_1 chapter8/fork_ch8_1.c)
#target_link_libraries(fork_ch8_1 apueLib)
#
#add_executable(fork_ch8_8 chapter8/fork_ch8_8.c)
#target_link_libraries(fork_ch8_8 apueLib)
#
#add_executable(echo_all_ch8_17 chapter8/echo_all_ch8_17.c)
#target_link_libraries(echo_all_ch8_17 apueLib)
#
#add_executable(ex8_6 chapter8/ex8_6.c)
#target_link_libraries(ex8_6 apueLib)
#
#add_executable(exec_ch8_16 chapter8/exec_ch8_16.c)
#target_link_libraries(exec_ch8_16 apueLib)

cmake_minimum_required(VERSION 3.23)
project(apud)
set(CMAKE_C_STANDARD 11)

#添加子目录
ADD_SUBDIRECTORY(chapter8)
