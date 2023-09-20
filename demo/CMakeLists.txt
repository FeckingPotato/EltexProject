cmake_minimum_required(VERSION 3.0)
project(bitmap C)

set(CMAKE_C_STANDARD 11)

add_executable(bitmap_demo main.c
        ui.c
        ui.h
        utils.c
        utils.h err.h)
target_link_libraries(bitmap_demo PRIVATE bitmap_shared)
target_link_libraries(bitmap_demo PRIVATE logger_shared)
configure_file(read_example.bitmap read_example.bitmap COPYONLY)
