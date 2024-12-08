cmake_minimum_required(VERSION 3.30)
project(lab10 C)

set(CMAKE_C_STANDARD 23)

add_library(operations src/operations.c src/operations.h)
add_library(list src/list.c src/list.h)
add_executable(lab10 src/main.c)

target_link_libraries(lab10 list operations)