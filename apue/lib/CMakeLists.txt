cmake_minimum_required(VERSION 3.23)

project(apueLib)

aux_source_directory(. DIR_LIB_SRCS)
add_library(apueLib ${DIR_LIB_SRCS})