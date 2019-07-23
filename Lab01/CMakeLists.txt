cmake_minimum_required(VERSION 3.14)
project(PiDP C)
include_directories(/usr/lib/x86_64-linux-gnu/openmpi/lib)

set(CMAKE_C_STANDARD 11)

add_executable(Lab01 L01.1.c)
#add_executable(Lab01 L01.2.c)
#add_executable(Lab01 L01.3.c)
#add_executable(Lab01 L01.4.c)