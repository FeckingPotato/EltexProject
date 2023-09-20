#include "concat_test.h"
#include "../bitmap.h"
#include "../bitmap_struct.h"
#include <stdio.h>

int concat_test()
{

    bitmap_t* source = bitmap_init(3);
    if (source == NULL)
    {
        return -1;
    }

    printf("Created a source bitmap of size %zu\n"
        "Data pointer: %p\n"
        "Size (bits): %zu\n"
        "Size (bytes): %zu\n", 
        3, source->data, source->size, source->size_bytes);


    bitmap_set_bit(source, 0, 1);
    bitmap_set_bit(source, 2, 1);   
    bitmap_print_bin(source);

    bitmap_t* dest = bitmap_init(5);
    if (dest == NULL)
    {
        return -1;
    }

    printf("Created a bitmap of size %zu\n"
        "Data pointer: %p\n"
        "Size (bits): %zu\n"
        "Size (bytes): %zu\n",
        5, dest->data, dest->size, dest->size_bytes);
    
    bitmap_set_bit(dest, 0, 1);
    bitmap_set_bit(dest, 1, 1);
    bitmap_print_bin(dest);

    dest = bitmap_concat(dest, source);
    if (dest == NULL)
    {
        return -1;
    }

    printf("Got new bitmap of size %zu\n"
        "Data pointer: %p\n"
        "Size (bits): %zu\n"
        "Size (bytes): %zu\n", 
        5, dest->data, dest->size, dest->size_bytes);

    bitmap_print_bin(dest);

    return 0;

}