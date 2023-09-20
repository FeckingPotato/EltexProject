cmake_minimum_required(VERSION 3.0)
project(bitmap C)

set(CMAKE_C_STANDARD 11)

include_directories(SYSTEM lib/logger lib/bitmap)

add_subdirectory(lib/bitmap)
add_subdirectory(lib/logger)
add_subdirectory(demo)
add_subdirectory(test)

add_dependencies(bitmap_demo bitmap_shared logger_shared)
add_dependencies(bitmap_test bitmap_static)
