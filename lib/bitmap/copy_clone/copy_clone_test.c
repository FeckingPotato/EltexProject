#include "../bitmap.h"
#include "../bitmap_struct.h"
#include <stdio.h>
#include <time.h>

int copy_clone_test()
{
    srand(time(NULL));
    size_t size = rand() % 100;
    bitmap_t *original = bitmap_init(size);
    if (original == NULL)
    {
        return -1;
    }
    printf("Created a bitmap of size %zu\n"
           "\n"
           "Original bitmap\n"
           "Data pointer: %p\n"
           "Size (bits): %zu\n"
           "Size (bytes): %zu\n"
           "\n", size, original->data, original->size, original->size_bytes);
    bitmap_t *copied = bitmap_copy(original);
    if (copied == NULL)
    {
        return -1;
    }
    printf("Copied bitmap\n"
           "Data pointer: %p\n"
           "Size (bits): %zu\n"
           "Size (bytes): %zu\n"
           "Equal to the original: %d\n"
           "\n", copied->data, copied->size, copied->size_bytes,
           bitmap_equal(original, copied));
    bitmap_t *cloned = bitmap_clone(original);
    if (cloned == NULL)
    {
        return -1;
    }
    printf("Cloned bitmap\n"
           "Data pointer: %p\n"
           "Size (bits): %zu\n"
           "Size (bytes): %zu\n"
           "Equal to the original: %d\n",
           cloned->data, cloned->size, cloned->size_bytes,
           bitmap_equal(original, cloned));
    return 0;
}
