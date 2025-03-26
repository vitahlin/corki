cmake_minimum_required(VERSION 3.23)
project(rds)
set(CMAKE_C_STANDARD 11)

#添加子目录
add_executable(rds_srv
    ae.h ae.c ae_queue.c
    log.h log.c
    zmalloc.h zmalloc.c
    server.h server.c
)
