cmake_minimum_required(VERSION 3.23)
project(unp)
set(CMAKE_C_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/lib/lib.out)

#添加子目录
ADD_SUBDIRECTORY(chapter01)
ADD_SUBDIRECTORY(chapter04)
ADD_SUBDIRECTORY(chapter05)
ADD_SUBDIRECTORY(chapter06)
