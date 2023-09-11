cmake_minimum_required(VERSION 3.0)
project(bitmap C)

set(CMAKE_C_STANDARD 11)

add_executable(bitmap main.c
        bitmap.c
        bitmap.h
        bitmap_struct.h
        comp/comp.c
        comp/comp.h
        print/print.c
        print/print.h
        comp/comp_test.c
        comp/comp_test.h
        copy_clone/copy_clone.c
        copy_clone/copy_clone.h
        copy_clone/copy_clone_test.c
        copy_clone/copy_clone_test.h)
