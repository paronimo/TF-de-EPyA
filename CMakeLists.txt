cmake_minimum_required(VERSION 4.0)
project(EPYA C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(EPYA
        main.c
        Tarea.c)
