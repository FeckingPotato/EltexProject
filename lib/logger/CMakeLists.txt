cmake_minimum_required(VERSION 3.0)
project(bitmap C)

set(CMAKE_C_STANDARD 11)

add_library(logger_static STATIC
        logger.c
        logger.h
)

add_library(logger_shared SHARED
        logger.c
        logger.h
)

set_target_properties(logger_static logger_shared
        PROPERTIES PUBLIC_HEADER "logger.h")

install(TARGETS logger_static logger_shared)
