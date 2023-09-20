#include "../bitmap_struct.h"
#include "../bitmap.h"
#include <string.h>

int bitmap_reset(const bitmap_t *bitmap)
{
    if (bitmap == NULL)
    {
        return -1;
    }
    memset(bitmap->data, 0, bitmap->size_bytes);
    return 0;
}
