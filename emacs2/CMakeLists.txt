cmake_minimum_required(VERSION 3.30)
project(emacs2 C)

set(CMAKE_C_STANDARD 23)

add_library(list src/lib/list/list.c src/lib/list/list.h)
add_library(file_op src/lib/file_op/file_op.c src/lib/file_op/file_op.h)
add_library(io_op src/lib/io_op/io_op.c src/lib/io_op/io_op.h)
add_library(emacs2 src/lib/emacs2/emacs2.c src/lib/emacs2/emacs2.h)
add_executable(emacs2.exe src/main.c)

target_link_libraries(emacs2.exe emacs2 io_op file_op list)