#include "bitmap.h"
#include <stdio.h>

bitmap_t *bitmap_init(size_t size)
{
    bitmap_t *bitmap = (bitmap_t*) malloc(sizeof (bitmap_t));
    if (bitmap == NULL)
    {
        perror("unable to allocate memory for the bitmap");
        return NULL;
    }

    bitmap->size = size;
    bitmap->size_bytes = (size + 7) / 8;
    bitmap->data = (uint8_t*) calloc(bitmap->size_bytes, sizeof(uint8_t));

    if (bitmap->data == NULL)
    {
        perror("unable to allocate memory for the bitmap data");
        free(bitmap);
        return NULL;
    }
    return bitmap;
}

void bitmap_destroy(bitmap_t *bitmap)
{
    free(bitmap->data);
    free(bitmap);
}

bit_t get_bit(
        bitmap_t *bitmap,
        size_t index)
{
    if (index >= bitmap->size)
    {
        return 2;
    }
    size_t byteOffset = index / 8;
    size_t bitOffset = index % 8;
    return ((bitmap->data)[byteOffset] & (1 << bitOffset)) != 0;
}

int set_bit(
        bitmap_t *bitmap,
        size_t index,
        bit_t bit)
{
    if (index >= bitmap->size)
    {
        return 2;
    }
    if (bit > 1)
    {
        return 3;
    }
    size_t byteOffset = index / 8;
    size_t bitOffset = index % 8;
    if (bit)
    {
        (bitmap->data)[byteOffset] |= 1 << bitOffset;
    }
    else {
        (bitmap->data)[byteOffset] &= ~(1 << bitOffset);
    }
    return 0;
}