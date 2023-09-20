#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef struct bitmap bitmap_t;

typedef uint8_t bit_t;

// bitmap.c
bitmap_t *bitmap_init(size_t size);

int bitmap_destroy(bitmap_t *bitmap);

bit_t bitmap_get_bit(
    bitmap_t *bitmap,
    size_t index);

int bitmap_set_bit(
    bitmap_t *bitmap,
    size_t index,
    bit_t bit);

size_t bitmap_size(bitmap_t *bitmap);

size_t bitmap_size_bytes(bitmap_t *bitmap);

// comp
int bitmap_equal(
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap);

int bitmap_more(
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap);

int bitmap_less(
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap);

int bitmap_more_or_equal(
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap);

int bitmap_less_or_equal(
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap);

// copy_clone
bitmap_t *bitmap_copy(bitmap_t *bitmap);

bitmap_t *bitmap_clone(bitmap_t *bitmap);

//print
int bitmap_print_bin(const bitmap_t *bitmap);

int bitmap_print_hex(const bitmap_t *bitmap);

// bitwise
bitmap_t *bitmap_and(
    bitmap_t *first,
    bitmap_t *second);

bitmap_t *bitmap_or(
    bitmap_t *first,
    bitmap_t *second);

bitmap_t *bitmap_xor(
    bitmap_t *first,
    bitmap_t *second);

bitmap_t *bitmap_not(bitmap_t *input);

// bmp
int bitmap_write_bmp(
    char *fileName,
    bitmap_t *my_bitmap,
    int32_t width,
    int32_t height);

// concat
bitmap_t *bitmap_concat(
    bitmap_t *dest,
    bitmap_t *source);

// reset
int bitmap_reset(const bitmap_t *bitmap);

// save_load
int bitmap_save(
    const bitmap_t *bitmap,
    const char *file_name);

int bitmap_load(
    const bitmap_t *bitmap,
    const char *file_name);
