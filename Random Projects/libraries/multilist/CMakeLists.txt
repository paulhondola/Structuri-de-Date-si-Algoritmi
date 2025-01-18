cmake_minimum_required(VERSION 3.30)
project(multilist C)

set(CMAKE_C_STANDARD 23)

add_library(multilist multilist.c multilist.h)
add_executable(main main.c)

target_link_libraries(main multilist)