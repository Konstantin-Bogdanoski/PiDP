cmake_minimum_required(VERSION 3.14)
project(Lab01 C)
include_directories(/usr/lib/x86_64-linux-gnu/openmpi/lib)

set(CMAKE_C_STANDARD 11)

add_executable(Lab01 main.c)