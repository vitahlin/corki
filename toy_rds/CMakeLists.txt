cmake_minimum_required(VERSION 3.23)
project(toy_rds)
set(CMAKE_C_STANDARD 11)

#添加子目录
add_executable(toy_rds_srv toy_rds_srv.c)
