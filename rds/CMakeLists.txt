cmake_minimum_required(VERSION 3.23)
project(rds)
set(CMAKE_C_STANDARD 11)

#添加子目录
add_executable(rds_srv
    ae.h ae.c
    server.h server.c
)
