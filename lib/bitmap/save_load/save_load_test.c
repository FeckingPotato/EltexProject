#include "../bitmap_struct.h"
#include "../bitmap.h"
#include <stdio.h>
#include <stdlib.h>

int save_load_test()
{
    int size = rand() % 100;
    bitmap_t *bitmap_to_save = bitmap_init(size);
    bitmap_t *bitmap_to_load = bitmap_init(size);

    if (bitmap_to_save == NULL || bitmap_to_load == NULL)
    {
        return -1;
    }

    int full_bytes = size / 8;
    for (int i = 0; i < full_bytes; ++i)
    {
        bitmap_to_save->data[i] = rand() % 256;
    }

    for (int i = 8 * full_bytes; i < size; ++i)
    {
        bitmap_set_bit(bitmap_to_save, i, rand() % 2);
    }

    printf("bitmap to save:");
    bitmap_print_bin(bitmap_to_save);

    puts("\nsaving bitmap to saved_bitmap.bin ...");
    bitmap_save(
        bitmap_to_save,
        "saved_bitmap.bin");

    puts("loading bitmap from saved_bitmap.bin ...\n");
    bitmap_load(
        bitmap_to_load,
        "saved_bitmap.bin");

    printf("loaded bitmap:");
    bitmap_print_bin(bitmap_to_load);

    if (bitmap_equal(bitmap_to_save, bitmap_to_load) != 1)
    {
        puts("bitmaps are not equal!");
        return -2;
    }

    puts("\nSave/load functions are working properly!");
    bitmap_destroy(bitmap_to_save);
    bitmap_destroy(bitmap_to_load);
    return 0;
}
