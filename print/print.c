#include "../bitmap_struct.h"
#include "bitmap.h"
#include <stdio.h>

/* Designed for bitmaps no more than 4 GB */
int print_bitmap_bin(const bitmap_t* bitmap)
{
    if (bitmap == NULL || bitmap->size == 0)
        return -1;

    size_t full_bytes_count = bitmap->size / 8;
    if (!full_bytes_count)
    {
        full_bytes_count = 1;
    }

    size_t curr_bit = 0;

    puts("\n===================================================");
    puts("Offset    |  Byte   0  Byte   1  Byte   2  Byte   3");
    printf("----------+----------------------------------------");

    for (size_t byte_num = 0; byte_num < bitmap->size_bytes; ++byte_num)
    {
        /* print offset */
        if (byte_num % 4 == 0)
        {
            printf("\n%08X  |  ", byte_num);
        }

        /* print byte in binary */
        for (char bit_pos = 7; bit_pos >= 0; --bit_pos, ++curr_bit)
        {
            /* if last byte is not full */
            if (curr_bit >= bitmap->size)
            {
                printf("-");
                continue;
            }

            if (bitmap->data[byte_num] & (1 << bit_pos))
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
        }

        printf("  ");
    }
    
    puts("\n===================================================");
    return 0;
}

/* Designed for bitmaps no more than 4 GB */
int print_bitmap_hex(const bitmap_t* bitmap)
{
    if (bitmap == NULL || bitmap->size_bytes == 0)
        return -1;

    puts("\n===========================================");
    puts("Offset    |   0   1   2   3   4   5   6   7");
    printf("----------+--------------------------------");

    for (size_t byte_num = 0; byte_num < bitmap->size_bytes; ++byte_num)
    {
        /* print offset */
        if (byte_num % 8 == 0)
        {
            printf("\n%08X  |  ", byte_num);
        }

        /* print byte in hex */
        printf("%02X  ", bitmap->data[byte_num]);
    }

    puts("\n===========================================");
    return 0;
}
