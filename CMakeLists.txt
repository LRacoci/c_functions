cmake_minimum_required(VERSION 3.15)
project(c_functions C)

set(CMAKE_C_STANDARD 90)

add_executable(c_functions main.c macros.h)