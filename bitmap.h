#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint8_t *data;
    size_t size;
    size_t size_bytes;
} bitmap_t;

typedef uint8_t bit_t;

bitmap_t *bitmap_init(size_t size);

void bitmap_destroy(bitmap_t *bitmap);

bit_t get_bit(
    bitmap_t *bitmap,
    size_t index);

int set_bit(
    bitmap_t *bitmap,
    size_t index,
    bit_t bit);