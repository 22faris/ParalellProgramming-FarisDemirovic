cmake_minimum_required(VERSION 4.3)
project(lab04 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab04 main.c
        fragmented_matrix.c
        contiguous_matrix.c
        example_3/aosoa_measurement.cpp)
