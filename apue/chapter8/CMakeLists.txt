cmake_minimum_required(VERSION 3.23)
project(apue_ch8)
set(CMAKE_C_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib ${CMAKE_CURRENT_SOURCE_DIR}/../lib/lib.out)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)
file(GLOB_RECURSE C_FILE_LIST *.c)

foreach (CURRENT_FILE ${C_FILE_LIST})
    get_filename_component(TARGET_NAME ${CURRENT_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${CURRENT_FILE})
    target_link_libraries(${TARGET_NAME} apueLib)
    message("Build ${TARGET_NAME}")
endforeach ()