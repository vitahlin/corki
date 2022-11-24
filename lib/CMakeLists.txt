cmake_minimum_required(VERSION 3.23)

project(lib)
# 指定生成链接库
add_library(apueLib apue.h log_err.c system.c tellwait.c)