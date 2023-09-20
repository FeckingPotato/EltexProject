#include "../bitmap_struct.h"
#include "../bitmap.h"
#include <stdio.h>
#include <stdlib.h>

int reset_test()
{
    int size = rand() % 100;
    bitmap_t *bitmap = bitmap_init(size);
    bitmap_t *zero_bitmap = bitmap_init(size);

    if (bitmap == NULL || zero_bitmap == NULL)
    {
        return -1;
    }

    for (int i = 0; i < bitmap->size_bytes; ++i)
    {
        bitmap->data[i] = rand() % 256;
    }

    printf("bitmap to reset:");
    bitmap_print_bin(bitmap);

    puts("\nresetting bitmap...\n");
    
    bitmap_reset(bitmap);

    printf("resetted bitmap:");
    bitmap_print_bin(bitmap);

    if (bitmap_equal(bitmap, zero_bitmap) != 1)
    {
        puts("\nReset function is NOT working properly!");
        return -2;
    }

    puts("\nReset function is working properly!");
    bitmap_destroy(bitmap);
    bitmap_destroy(zero_bitmap);
    return 0;
}
