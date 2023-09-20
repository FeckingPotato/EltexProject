#include "../bitmap.h"
#include "../bitmap_struct.h"
#include <string.h>

bitmap_t *bitmap_concat(
    bitmap_t *dest,
    bitmap_t *source)
{
    bitmap_t *bitmap = bitmap_init(dest->size + source->size);
    uint8_t temp_data[dest->size_bytes + source->size_bytes];
    memcpy(temp_data, dest->data, dest->size_bytes);
    memcpy(temp_data + dest->size_bytes, source->data, source->size_bytes);
    uint8_t unused_bits_dest = dest->size_bytes * 8 - dest->size;
    if (unused_bits_dest != 0)
    {
        for (
            size_t i = dest->size_bytes;
            i < dest->size_bytes + source->size_bytes;
            i++)
        {
            temp_data[i - 1] &= (uint8_t) 0xFF << unused_bits_dest;
            temp_data[i - 1] |=
                temp_data[i] >> (8 - unused_bits_dest);
        }
    }
    memcpy(bitmap->data, temp_data, bitmap->size_bytes);
    return bitmap;
}
