cmake_minimum_required(VERSION 3.29)
project(lab8 C)

set(CMAKE_C_STANDARD 23)

add_library(hashmap hashmap.c hashmap.h)
add_executable(lab8 main.c)
target_link_libraries(lab8 hashmap)