#pragma once
#include <stdint.h>
#include <stdlib.h>

struct bitmap
{
    uint8_t *data;
    size_t size;
    size_t size_bytes;
};
