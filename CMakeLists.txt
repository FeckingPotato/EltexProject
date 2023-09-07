cmake_minimum_required(VERSION 3.0)
project(bitmap C)

set(CMAKE_C_STANDARD 11)

add_executable(bitmap main.c
        bitmap.c
        bitmap.h
        bitmap_struct.h)
