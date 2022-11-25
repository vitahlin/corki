cmake_minimum_required(VERSION 3.23)

project(lib)
# 指定生成链接库
add_library(apueLib ../apue/lib/apue.h ../apue/lib/log_err.c ../apue/lib/system.c ../apue/lib/tellwait.c)