#include "comp.h"
#include "../bitmap_struct.h"

int bitmap_equal(
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap)
{
    if (first_bitmap == NULL || second_bitmap == NULL)
        // checking for possible NULL pointers
    {
        return -1;
    }
    if (first_bitmap->size != second_bitmap->size)
        // checking if the sizes match
    {
        return -2;
    }
    size_t last_full_byte;
    if (first_bitmap->size == first_bitmap->size_bytes * 8)
        // getting the amount of bytes to compare
    {
        last_full_byte = first_bitmap->size_bytes;
    }
    else
    {
        last_full_byte = first_bitmap->size_bytes - 1;
    }
    for (size_t i = 0; i < last_full_byte; i++)
        // comparing bytes
    {
        if (first_bitmap->data[i] != second_bitmap->data[i])
        {
            return 0;
        }
    }
    if (last_full_byte != first_bitmap->size_bytes)
        // comparing bits in the last byte
    {
        for (size_t i = 0; i < 8; i++)
        {
            bit_t cur_bit_a =
                (((first_bitmap->data)[last_full_byte] & (1 << i)) != 0);
            bit_t cur_bit_b =
                (((second_bitmap->data)[last_full_byte] & (1 << i)) != 0);
            if (cur_bit_a != cur_bit_b)
            {
                return 0;
            }
        }
    }
    return 1;
}

int bitmap_more(
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap)
{
    if (first_bitmap == NULL || second_bitmap == NULL)
        // checking for possible NULL pointers
    {
        return -1;
    }
    if (first_bitmap->size != second_bitmap->size)
        // checking if the sizes match
    {
        return -2;
    }
    size_t last_full_byte;
    if (first_bitmap->size == first_bitmap->size_bytes * 8)
        // getting the amount of bytes to compare
    {
        last_full_byte = first_bitmap->size_bytes;
    }
    else
    {
        last_full_byte = first_bitmap->size_bytes - 1;
    }
    for (size_t i = 0; i < last_full_byte; i++)
        // comparing bytes
    {
        if (first_bitmap->data[i] > second_bitmap->data[i])
        {
            return 1;
        }
        if (first_bitmap->data[i] < second_bitmap->data[i])
        {
            return 0;
        }
    }
    if (last_full_byte != first_bitmap->size_bytes)
        // comparing bits in the last byte
    {
        for (size_t i = 0; i < 8; i++)
        {
            bit_t cur_bit_a =
                (((first_bitmap->data)[last_full_byte] & (1 << i)) != 0);
            bit_t cur_bit_b =
                (((second_bitmap->data)[last_full_byte] & (1 << i)) != 0);
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
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap)
{
    return bitmap_more(second_bitmap, first_bitmap);
}

int bitmap_more_or_equal(
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap)
{
    return (bitmap_more(first_bitmap, second_bitmap)
            || bitmap_equal(first_bitmap, second_bitmap));
}

int bitmap_less_or_equal(
    bitmap_t *first_bitmap,
    bitmap_t *second_bitmap)
{
    return (bitmap_less(first_bitmap, second_bitmap)
            || bitmap_equal(first_bitmap, second_bitmap));
}