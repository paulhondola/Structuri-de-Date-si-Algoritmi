cmake_minimum_required(VERSION 3.29)
project(hashmap C)

set(CMAKE_C_STANDARD 23)

add_library(hashmap hashmap.c hashmap.h)
add_executable(main main.c)

target_link_libraries(main hashmap)