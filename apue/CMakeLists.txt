cmake_minimum_required(VERSION 3.23)
project(apue)
set(CMAKE_C_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/lib/lib.out)

#添加子目录
ADD_SUBDIRECTORY(chapter8)
ADD_SUBDIRECTORY(chapter10)
ADD_SUBDIRECTORY(chapter11)