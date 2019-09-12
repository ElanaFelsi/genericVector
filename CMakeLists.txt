cmake_minimum_required(VERSION 3.14)
project(c_generic_vector_ElanaFelsi C)

set(CMAKE_C_STANDARD 90)

add_executable(c_generic_vector_ElanaFelsi main.c genericVec.h genericVec.c testing.h testing.c)