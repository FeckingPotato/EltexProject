#include "../bitmap.h"
#include "../bitmap_struct.h"
#include <string.h>

bitmap_t *bitmap_copy(bitmap_t *bitmap)
{
    if (bitmap == NULL)
    {
        return NULL;
    }
    bitmap_t *result = (bitmap_t *) calloc(sizeof(bitmap_t), 1);
    result->data = bitmap->data;
    result->size = bitmap->size;
    result->size_bytes = bitmap->size_bytes;
    return result;
}

bitmap_t *bitmap_clone(bitmap_t *bitmap)
{
    if (bitmap == NULL)
    {
        return NULL;
    }
    bitmap_t *result = bitmap_init(bitmap->size);
    memcpy(result->data, bitmap->data, bitmap->size_bytes);
    return result;
}
