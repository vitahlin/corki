cmake_minimum_required(VERSION 3.23)
project(unp)
set(CMAKE_C_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/lib/lib.out)

#添加子目录
ADD_SUBDIRECTORY(chapter1)
ADD_SUBDIRECTORY(chapter3)
ADD_SUBDIRECTORY(chapter4)
ADD_SUBDIRECTORY(chapter5)
ADD_SUBDIRECTORY(chapter6)
