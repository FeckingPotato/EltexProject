cmake_minimum_required(VERSION 3.0)
project(bitmap C)

set(CMAKE_C_STANDARD 11)

add_executable(bitmap main.c
        bitmap.c
        bitmap.h
        bitmap_struct.h
        comp/comp.c
        comp/comp.h
        comp/comp_test.c
        comp/comp_test.h)
