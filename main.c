#include "bitmap.h"
#include <stdio.h>

int main()
{
    bitmap_t *bitmap = bitmap_init(13);
    printf("Created a bitmap with a size of 13\n");
    set_bit(bitmap, 0, 1);
    set_bit(bitmap, 8, 1);
    set_bit(bitmap, 10, 1);
    printf("Set the following bits to 1: 0, 8, 10\n");
    printf("Bits:\n"
           "0: %u\n"
           "5: %u\n"
           "8: %u\n"
           "10: %u\n",
           get_bit(bitmap, 0), get_bit(bitmap, 5), get_bit(bitmap, 8), get_bit(bitmap, 10));
    bitmap_destroy(bitmap);
    printf("Destroyed the bitmap\n");
}