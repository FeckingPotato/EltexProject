cmake_minimum_required(VERSION 3.0)
project(bitmap C)

set(CMAKE_C_STANDARD 11)

add_library(bitmap_static STATIC
        bitmap.c
        bitmap.h
        bitmap_struct.h
        bmp/bmp.c
        bitwise/bitwise.c
        comp/comp.c
        copy_clone/copy_clone.c
        print/print.c
        concat/concat.c
        reset/reset.c
        save_load/save_load.c
)

add_library(bitmap_shared SHARED
        bitmap.c
        bitmap.h
        bitmap_struct.h
        bmp/bmp.c
        bitwise/bitwise.c
        comp/comp.c
        copy_clone/copy_clone.c
        print/print.c
        concat/concat.c
        reset/reset.c
        save_load/save_load.c
)

set_target_properties(bitmap_static bitmap_shared
        PROPERTIES PUBLIC_HEADER "bitmap.h")

install(TARGETS bitmap_static bitmap_shared)
