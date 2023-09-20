#include "../bitmap.h"
#include "../bitmap_struct.h"
#include <stdio.h>

bitmap_t *bitmap_and(
    bitmap_t *first,
    bitmap_t *second)
{

    if (first == NULL || second == NULL)
    {
        perror("One of the input structures is NULL");
        return NULL;
    }

    bitmap_t *result = NULL;
    size_t workingArea;

    if (first->size_bytes >= second->size_bytes)
    {
        result = bitmap_init(first->size);
        workingArea = second->size_bytes;
    }
    else
    {
        result = bitmap_init(second->size);
        workingArea = first->size_bytes;
    }

    if (result == NULL)
    {
        perror("result is NULL");
        return NULL;
    }

    for (size_t i = 0; i < workingArea; i++)
    {
        result->data[i] = first->data[i] & second->data[i];
    }

    return result;
}

bitmap_t *bitmap_or(
    bitmap_t *first,
    bitmap_t *second)
{
    if (first == NULL || second == NULL)
    {
        perror("One of the input structures is NULL");
        return NULL;
    }

    bitmap_t *result = NULL;

    if (first->size_bytes >= second->size_bytes)
    {
        result = bitmap_init(first->size);
        if (result == NULL)
        {
            perror("result is NULL");
            return NULL;
        }
        for (size_t i = 0; i < second->size_bytes; i++)
        {
            result->data[i] = first->data[i] | second->data[i];

        }
        for (size_t i = second->size_bytes; i < first->size_bytes; i++)
        {
            result->data[i] = first->data[i];
        }
    }
    else
    {
        result = bitmap_init(second->size);
        if (result == NULL)
        {
            perror("result is NULL");
            return NULL;
        }
        for (size_t i = 0; i < first->size; i++)
        {
            result->data[i] = first->data[i] | second->data[i];
        }
        for (size_t i = first->size; i < second->size; i++)
        {
            result->data[i] = second->data[i];
        }
    }

    return result;
}

bitmap_t *bitmap_xor(
    bitmap_t *first,
    bitmap_t *second)
{
    if (first == NULL || second == NULL)
    {
        perror("One of the input structures is NULL");
        return NULL;
    }

    bitmap_t *result = NULL;

    if (first->size_bytes >= second->size_bytes)
    {
        result = bitmap_init(first->size);
        if (result == NULL)
        {
            perror("result is NULL");
            return NULL;
        }
        for (size_t i = 0; i < second->size_bytes; i++)
        {
            result->data[i] = first->data[i] ^ second->data[i];

        }
        for (size_t i = second->size_bytes; i < first->size_bytes; i++)
        {
            result->data[i] = first->data[i];
        }
    }
    else
    {
        result = bitmap_init(second->size);
        if (result == NULL)
        {
            perror("result is NULL");
            return NULL;
        }
        for (size_t i = 0; i < first->size; i++)
        {
            result->data[i] = first->data[i] ^ second->data[i];
        }
        for (size_t i = first->size; i < second->size; i++)
        {
            result->data[i] = second->data[i];
        }
    }

    return result;
}

bitmap_t *bitmap_not(bitmap_t *input)
{
    if (input == NULL)
    {
        perror("One of the input structures is NULL");
        return NULL;
    }

    bitmap_t *result = bitmap_init(input->size);

    if (result == NULL)
    {
        perror("result is NULL");
        return NULL;
    }

    for (size_t i = 0; i < input->size_bytes; i++)
    {
        result->data[i] = ~input->data[i];
    }
    size_t unused_bits = input->size_bytes * 8 - input->size;
    if (unused_bits != 0)
    {
        result->data[input->size_bytes - 1] &=
            (uint8_t) 0xFF << unused_bits;
    }

    return result;
}
