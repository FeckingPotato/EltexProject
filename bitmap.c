#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t* data;
    size_t size;
    size_t sizeBytes;
} Bitmap;

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

int main() {
    Bitmap *bitmap = initBitmap(13);
    printf("Created a bitmap with a size of 13\n");
    destroyBitmap(bitmap);
    printf("Destroyed the bitmap\n");
}