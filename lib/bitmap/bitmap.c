#include "bitmap.h"
#include "bitmap_struct.h"
#include <stdio.h>

bitmap_t *bitmap_init(size_t size)
{
    bitmap_t *bitmap = (bitmap_t *) malloc(sizeof(bitmap_t));
    if (bitmap == NULL)
    {
        return NULL;
    }

    bitmap->size = size;
    bitmap->size_bytes = (size + 7) / 8;
    bitmap->data = (uint8_t *) calloc(bitmap->size_bytes, sizeof(uint8_t));

    if (bitmap->data == NULL)
    {
        free(bitmap);
        return NULL;
    }
    return bitmap;
}

int bitmap_destroy(bitmap_t *bitmap)
{
    if (bitmap == NULL)
    {
        return -1;
    }
    free(bitmap->data);
    free(bitmap);
    return 0;
}

bit_t bitmap_get_bit(
    bitmap_t *bitmap,
    size_t index)
{
    if (bitmap == NULL)
    {
        return -1;
    }
    if (index >= bitmap->size)
    {
        return -2;
    }
    size_t byteOffset = index / 8;
    size_t bitOffset = index % 8;
    return ((bitmap->data)[byteOffset] & (1 << (7 - bitOffset))) != 0;
}

int bitmap_set_bit(
    bitmap_t *bitmap,
    size_t index,
    bit_t bit)
{
    if (bitmap == NULL)
    {
        return -1;
    }
    if (index >= bitmap->size)
    {
        return -2;
    }
    if (bit > 1)
    {
        return -3;
    }
    size_t byteOffset = index / 8;
    size_t bitOffset = index % 8;
    if (bit)
    {
        (bitmap->data)[byteOffset] |= 1 << (7 - bitOffset);
    }
    else
    {
        (bitmap->data)[byteOffset] &= ~(1 << (7 - bitOffset));
    }
    return 0;
}

size_t bitmap_size(bitmap_t *bitmap)
{
    if (bitmap == NULL)
    {
        return 0;
    }
    return bitmap->size;
}

size_t bitmap_size_bytes(bitmap_t *bitmap)
{
    if (bitmap == NULL)
    {
        return 0;
    }
    return bitmap->size_bytes;
}
