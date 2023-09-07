#pragma once
#include "../bitmap.h"

int bitmap_equal(
    bitmap_t *a,
    bitmap_t *b);

int bitmap_more(
    bitmap_t *a,
    bitmap_t *b);

int bitmap_less(
    bitmap_t *a,
    bitmap_t *b);

int bitmap_more_or_equal(
    bitmap_t *a,
    bitmap_t *b);

int bitmap_less_or_equal(
    bitmap_t *a,
    bitmap_t *b);