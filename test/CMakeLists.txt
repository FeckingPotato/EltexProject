cmake_minimum_required(VERSION 3.0)
project(bitmap C)

set(CMAKE_C_STANDARD 11)

add_executable(bitmap_test
        main.c
        ../lib/bitmap/comp/comp_test.c
        ../lib/bitmap/comp/comp_test.h
        ../lib/bitmap/copy_clone/copy_clone_test.c
        ../lib/bitmap/copy_clone/copy_clone_test.h
        ../lib/bitmap/bmp/bmp_test.c
        ../lib/bitmap/bitwise/bitwise_test.c
        ../lib/bitmap/concat/concat_test.c
        ../lib/logger/logger_test.c
        ../lib/bitmap/save_load/save_load_test.c
        ../lib/bitmap/reset/reset_test.c
)

configure_file(sample.bmp sample.bmp COPYONLY)

target_link_libraries(bitmap_test PRIVATE bitmap_static)
target_link_libraries(bitmap_test PRIVATE logger_static)
