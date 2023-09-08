#include "comp_test.h"
#include "../bitmap.h"
#include "comp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 13
#define SIZE_TEST 16

int comp_test()
{
    bitmap_t *first_bitmap = bitmap_init(SIZE);
    bitmap_t *second_bitmap = bitmap_init(SIZE_TEST);
    if (first_bitmap == NULL || second_bitmap == NULL)
    {
        return -1;
    }
    int result[5];
    result[0] = bitmap_equal(first_bitmap, second_bitmap);
    printf("Deterministic comparison tests:\n"
           "Comparing null pointers: %d (should be -1)\n"
           "Comparing empty bitmaps of size %d and %d: %d (should be -2)\n"
           "Setting the second bitmap's size to %d\n",
           bitmap_equal(NULL, NULL), SIZE, SIZE_TEST, result[0], SIZE);
    bitmap_destroy(second_bitmap);
    second_bitmap = bitmap_init(SIZE);
    if (second_bitmap == NULL)
    {
        return -1;
    }
    result[0] = bitmap_equal(first_bitmap, second_bitmap);
    result[1] = bitmap_more(first_bitmap, second_bitmap);
    result[2] = bitmap_less(first_bitmap, second_bitmap);
    result[3] = bitmap_more_or_equal(first_bitmap, second_bitmap);
    result[4] = bitmap_less_or_equal(first_bitmap, second_bitmap);
    printf("Comparing empty bitmaps of size %d:\n"
           "A == B: %d (should be 1)\n"
           "A > B: %d (should be 0)\n"
           "A < B: %d (should be 0)\n"
           "A >= B: %d (should be 1)\n"
           "A <= B: %d (should be 1)\n",
           SIZE, result[0], result[1], result[2], result[3], result[4]);
    srand(time(NULL));
    size_t set_bit_a = rand() % SIZE;
    size_t set_bit_b = rand() % SIZE;
    set_bit(first_bitmap, set_bit_a, 1);
    set_bit(second_bitmap, set_bit_b, 1);
    result[0] = bitmap_equal(first_bitmap, second_bitmap);
    result[1] = bitmap_more(first_bitmap, second_bitmap);
    result[2] = bitmap_less(first_bitmap, second_bitmap);
    result[3] = bitmap_more_or_equal(first_bitmap, second_bitmap);
    result[4] = bitmap_less_or_equal(first_bitmap, second_bitmap);
    printf("\n"
           "Random comparison tests:\n"
           "Set the following bit in the first bitmap: %zu\n"
           "Set the following bit in the second bitmap: %zu\n"
           "A == B: %d (should be %d)\n"
           "A > B: %d (should be %d)\n"
           "A < B: %d (should be %d)\n"
           "A >= B: %d (should be %d)\n"
           "A <= B: %d (should be %d)\n",
           set_bit_a, set_bit_b,
           result[0], set_bit_a == set_bit_b,
           result[1], set_bit_a < set_bit_b,
           result[2], set_bit_a > set_bit_b,
           result[3], set_bit_a <= set_bit_b,
           result[4], set_bit_a >= set_bit_b);
    bitmap_destroy(first_bitmap);
    bitmap_destroy(second_bitmap);
    return 0;
}