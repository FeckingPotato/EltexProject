#include "../bitmap_struct.h"
#include "../bitmap.h"
#include <stdio.h>

int bitmap_save(
    const bitmap_t *bitmap,
    const char *file_name)
{
    if (bitmap == NULL || file_name == NULL)
    {
        return -1;
    }

    FILE *file = fopen(file_name, "wb");
    if (file == NULL)
    {
        return -2;
    }

    fwrite(
        bitmap->data,
        sizeof(uint8_t),
        bitmap->size_bytes,
        file);

    fclose(file);

    size_t unused_bits = bitmap->size_bytes * 8 - bitmap->size;
    if (unused_bits != 0)
    {
        bitmap->data[bitmap->size_bytes-1] &= ((uint8_t) 0xFF << unused_bits);
    }

    return 0;
}

int bitmap_load(
    const bitmap_t *bitmap,
    const char *file_name)
{
    if (bitmap == NULL || file_name == NULL)
    {
        return -1;
    }

    FILE *file = fopen(file_name, "rb");
    if (file == NULL)
    {
        return -2;
    }

    size_t curr_byte = 0;
    while (!feof(file) && curr_byte < bitmap->size_bytes)
    {
        fread(
            &(bitmap->data[curr_byte]),
            sizeof(uint8_t),
            1,
            file);

        ++curr_byte;
    }

    fclose(file);

    size_t unused_bits = bitmap->size_bytes * 8 - bitmap->size;
    if (unused_bits != 0)
    {
        bitmap->data[bitmap->size_bytes-1] &= ((uint8_t) 0xFF << unused_bits);
    }

    return 0;
}
