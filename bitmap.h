#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef struct bitmap bitmap_t;

typedef _Bool bit_t;

bitmap_t *bitmap_init(size_t size);

void bitmap_destroy(bitmap_t *bitmap);

bit_t get_bit(
    bitmap_t *bitmap,
    size_t index);

int set_bit(
    bitmap_t *bitmap,
    size_t index,
    bit_t bit);

size_t bitmap_size(bitmap_t *bitmap);

size_t bitmap_size_bytes(bitmap_t *bitmap);
