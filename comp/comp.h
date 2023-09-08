#pragma once
#include "../bitmap.h"

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