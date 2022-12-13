cmake_minimum_required(VERSION 3.23)
project(other)
set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)
file(GLOB_RECURSE C_FILE_LIST *.c)

message("Build other...")
foreach (CURRENT_FILE ${C_FILE_LIST})
    get_filename_component(TARGET_NAME ${CURRENT_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${CURRENT_FILE})
    message("${TARGET_NAME}")
endforeach ()
message("Build other success\n")
