#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t* data;
    size_t size;
    size_t sizeBytes;
} Bitmap;

typedef uint8_t bit_t;

Bitmap *initBitmap(size_t size) {
    Bitmap *result = (Bitmap*) malloc(sizeof (Bitmap));
    if (result == NULL) {
        perror("unable to allocate memory for the bitmap");
        return NULL;
    }

    result->size = size;
    result->sizeBytes = (size + 7) / 8;
    result->data = (uint8_t*) calloc(result->sizeBytes, sizeof(uint8_t));

    if (result->data == NULL) {
        perror("unable to allocate memory for the bitmap data");
        free(result);
        return NULL;
    }
    return result;
}

void destroyBitmap(Bitmap *bitmap) {
    free(bitmap->data);
    free(bitmap);
}

bit_t getBit(Bitmap *bitmap, size_t index) {
    if (index >= bitmap->size) {
        return 2;
    }
    size_t byteOffset = index / 8;
    size_t bitOffset = index % 8;
    return ((bitmap->data)[byteOffset] & (1 << bitOffset)) != 0;
}

int setBit(Bitmap *bitmap, size_t index, bit_t bit) {
    if (index >= bitmap->size) {
        return 2;
    }
    if (bit > 1) {
        return 3;
    }
    size_t byteOffset = index / 8;
    size_t bitOffset = index % 8;
    if (bit) {
        (bitmap->data)[byteOffset] |= 1 << bitOffset;
    }
    else {
        (bitmap->data)[byteOffset] &= ~(1 << bitOffset);
    }
    return 0;
}

int main() {
    Bitmap *bitmap = initBitmap(13);
    printf("Created a bitmap with a size of 13\n");
    setBit(bitmap, 0, 1);
    setBit(bitmap, 8, 1);
    setBit(bitmap, 10, 1);
    printf("Set the following bits to 1: 0, 8, 10\n");
    printf("Bits:\n"
           "0: %u\n"
           "5: %u\n"
           "8: %u\n"
           "10: %u\n",
           getBit(bitmap, 0), getBit(bitmap, 5), getBit(bitmap, 8), getBit(bitmap, 10));
    destroyBitmap(bitmap);
    printf("Destroyed the bitmap\n");
}