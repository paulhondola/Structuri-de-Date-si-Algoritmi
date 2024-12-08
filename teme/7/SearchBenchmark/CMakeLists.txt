cmake_minimum_required(VERSION 3.29)
project(SearchBenchmark C)

# Set the C standard to C23
set(CMAKE_C_STANDARD 23)

# Add library targets
add_library(datatype datatype.c)
add_library(search search.c)
add_library(array_generator array_generator.c)
add_library(timer timer.c)

# Add the main executable
add_executable(main main.c)

# Link libraries to the main executable
target_link_libraries(main search array_generator timer datatype)