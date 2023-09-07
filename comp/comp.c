#include "comp.h"
#include "../bitmap_struct.h"

int bitmap_equal(
    bitmap_t *a,
    bitmap_t *b)
{
        if (a == NULL || b == NULL) // checking for possible NULL pointers
        {
            return -1;
        }
        if (a->size != b->size) // checking if the sizes match
        {
            return -2;
        }
        size_t last_full_byte;
        if (a->size == a->size_bytes * 8) // getting the amount of bytes to compare
        {
            last_full_byte = a->size_bytes;
        }
        else
        {
            last_full_byte = a->size_bytes - 1;
        }
        for (size_t i = 0; i < last_full_byte; i++) // comparing bytes
        {
            if (a->data[i] != b->data[i])
            {
                return 0;
            }
        }
        if (last_full_byte != a->size_bytes) // comparing bits in the last byte
        {
            for (size_t i = 0; i < 8; i++) {
                bit_t cur_bit_a = (((a->data)[last_full_byte] & (1 << i)) != 0);
                bit_t cur_bit_b = (((b->data)[last_full_byte] & (1 << i)) != 0);
                if (cur_bit_a != cur_bit_b)
                {
                    return 0;
                }
            }
        }
        return 1;
}

int bitmap_more(
    bitmap_t *a,
    bitmap_t *b)
{
    if (a == NULL || b == NULL) // checking for possible NULL pointers
    {
        return -1;
    }
    if (a->size != b->size) // checking if the sizes match
    {
        return -2;
    }
    size_t last_full_byte;
    if (a->size == a->size_bytes * 8) // getting the amount of bytes to compare
    {
        last_full_byte = a->size_bytes;
    }
    else
    {
        last_full_byte = a->size_bytes - 1;
    }
    for (size_t i = 0; i < last_full_byte; i++) // comparing bytes
    {
        if (a->data[i] > b->data[i])
        {
            return 1;
        }
        if (a->data[i] < b->data[i])
        {
            return 0;
        }
    }
    if (last_full_byte != a->size_bytes) // comparing bits in the last byte
    {
        for (size_t i = 0; i < 8; i++) {
            bit_t cur_bit_a = (((a->data)[last_full_byte] & (1 << i)) != 0);
            bit_t cur_bit_b = (((b->data)[last_full_byte] & (1 << i)) != 0);
            if (cur_bit_a > cur_bit_b)
            {
                return 1;
            }
            if (cur_bit_a < cur_bit_b)
            {
                return 0;
            }
        }
    }
    return 0;
}

int bitmap_less(
    bitmap_t *a,
    bitmap_t *b)
{
    return bitmap_more(b, a);
}

int bitmap_more_or_equal(
    bitmap_t *a,
    bitmap_t *b)
{
    return bitmap_more(a, b) || bitmap_equal(a, b);
}

int bitmap_less_or_equal(
    bitmap_t *a,
    bitmap_t *b)
{
    return bitmap_less(a, b) || bitmap_equal(a, b);
}