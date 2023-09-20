#pragma once
#include <bitmap.h>

int demo_init(bitmap_t *bitmaps[2]);

int demo_print(
    bitmap_t *bitmaps[2],
    const char *option);

int demo_set_bit(bitmap_t *bitmaps[2]);

int demo_get_bit(bitmap_t *bitmaps[2]);

int demo_compare(bitmap_t *bitmaps[2]);

int demo_bin_bitwise(bitmap_t *bitmaps[2]);

int demo_not_bitwise(bitmap_t *bitmaps[2]);

int demo_concat(bitmap_t *bitmaps[2]);

int demo_copy(bitmap_t *bitmaps[2]);

int demo_clone(bitmap_t *bitmaps[2]);

int demo_new(bitmap_t *bitmaps[2]);

int demo_reset(bitmap_t *bitmaps[2]);

int demo_bmp(bitmap_t *bitmaps[2]);

int demo_save(bitmap_t *bitmaps[2]);

int demo_load(bitmap_t *bitmaps[2]);

int demo_auto(bitmap_t *bitmaps[2]);
