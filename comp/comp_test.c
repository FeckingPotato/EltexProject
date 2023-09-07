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
    bitmap_t *a = bitmap_init(SIZE);
    bitmap_t *b = bitmap_init(SIZE_TEST);
    if (a == NULL || b == NULL)
    {
        return -1;
    }
    int result[5];
    result[0] = bitmap_equal(a, b);
    printf("Deterministic comparison tests:\n"
           "Comparing null pointers: %d (should be -1)\n"
           "Comparing empty bitmaps of size %d and %d: %d (should be -2)\n"
           "Setting the second bitmap's size to %d\n",
           bitmap_equal(NULL, NULL), SIZE, SIZE_TEST, result[0], SIZE);
    bitmap_destroy(b);
    b = bitmap_init(SIZE);
    if (b == NULL)
    {
        return -1;
    }
    result[0] = bitmap_equal(a, b);
    result[1] = bitmap_more(a, b);
    result[2] = bitmap_less(a, b);
    result[3] = bitmap_more_or_equal(a, b);
    result[4] = bitmap_less_or_equal(a, b);
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
    set_bit(a, set_bit_a, 1);
    set_bit(b, set_bit_b, 1);
    result[0] = bitmap_equal(a, b);
    result[1] = bitmap_more(a, b);
    result[2] = bitmap_less(a, b);
    result[3] = bitmap_more_or_equal(a, b);
    result[4] = bitmap_less_or_equal(a, b);
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
    bitmap_destroy(a);
    bitmap_destroy(b);
    return 0;
}