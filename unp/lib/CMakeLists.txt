cmake_minimum_required(VERSION 3.23)

project(unpLib)

aux_source_directory(. DIR_LIB_SRCS)
add_library(UnpLib ${DIR_LIB_SRCS})