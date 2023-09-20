#include "ui.h"
#include "err.h"
#include "utils.h"
#include <stdio.h>

long get_long(const char *message, char **end_ptr)
{
    char input_string[10];
    printf("%s", message);
    scanf("%s", input_string);
    return strtol(input_string, end_ptr, 10);
}

unsigned long get_ulong(const char *message, char **end_ptr)
{
    char input_string[10];
    printf("%s", message);
    scanf("%s", input_string);
    return strtoul(input_string, end_ptr, 10);
}

int get_bitmap()
{
    char *end_ptr;
    long result = get_long("Type in the bitmap number (1/2): ", &end_ptr);
    if (((result != 1) && (result != 2)) || (*end_ptr != '\0'))
    {
        printf("Wrong bitmap number\n");
        return ERR_BITMAP_INDEX;
    }
    return (int) (result - 1);
}

int demo_init(bitmap_t *bitmaps[2])
{
    char *end_ptr;
    size_t input_num =
        get_ulong("Type in the size of the first bitmap: ", &end_ptr);
    if (*end_ptr != '\0')
    {
        printf("Wrong size\n");
        return ERR_BITMAP_SIZE; // TODO: Logger
    }
    bitmaps[0] = bitmap_init(input_num);

    input_num = get_ulong("Type in the size of the second bitmap: ", &end_ptr);
    if (*end_ptr != '\0')
    {
        printf("Wrong size\n");
        return ERR_BITMAP_SIZE; // TODO: Logger
    }
    bitmaps[1] = bitmap_init(input_num);
    return ERR_SUCCESS;
}

int demo_print(
    bitmap_t *bitmaps[2],
    const char *option)
{
    printf("First bitmap:");
    if (*option == 'a')
    {
        bitmap_print_hex(bitmaps[0]);
    }
    else
    {
        bitmap_print_bin(bitmaps[0]);
    }
    printf("\n");
    printf("Second bitmap:");
    if (*option == 'a')
    {
        bitmap_print_hex(bitmaps[1]);
    }
    else
    {
        bitmap_print_bin(bitmaps[1]);
    }
    printf("\n");
    return ERR_SUCCESS;
}

int demo_set_bit(bitmap_t *bitmaps[2])
{
    int bitmap_number = get_bitmap();
    if (bitmap_number < 0)
    {
        return bitmap_number;
    }
    char *end_ptr;
    size_t index = get_ulong("Type in the bit index to set: ", &end_ptr);
    if ((index >= bitmap_size(bitmaps[bitmap_number])) || (*end_ptr != '\0'))
    {
        printf("Wrong index\n");
        return ERR_BITMAP_INDEX;
    }
    bit_t bit = get_ulong("Type in the bit value: ", &end_ptr);
    bitmap_set_bit(bitmaps[bitmap_number], index, bit);
    return ERR_SUCCESS;
}

int demo_get_bit(bitmap_t *bitmaps[2])
{
    int bitmap_number = get_bitmap();
    if (bitmap_number < 0)
    {
        return bitmap_number;
    }
    char *end_ptr;
    size_t index = get_ulong("Type in the bit index to get: ", &end_ptr);
    if ((index >= bitmap_size(bitmaps[bitmap_number])) || (*end_ptr != '\0'))
    {
        printf("Wrong index\n");
        return ERR_BITMAP_INDEX;
    }
    printf("The bit is: %d\n", bitmap_get_bit(bitmaps[bitmap_number], index));
    return ERR_SUCCESS;
}

int demo_compare(bitmap_t *bitmaps[2])
{
    if (bitmap_size(bitmaps[0]) != bitmap_size(bitmaps[1]))
    {
        printf("Unable to compare bitmaps of different sizes\n");
        return ERR_SIZE_MISMATCH;
    }
   int result[5];
    result[0] = bitmap_equal(bitmaps[0], bitmaps[1]);
    result[1] = bitmap_more(bitmaps[0], bitmaps[1]);
    result[2] = bitmap_less(bitmaps[0], bitmaps[1]);
    result[3] = bitmap_more_or_equal(bitmaps[0], bitmaps[1]);
    result[4] = bitmap_less_or_equal(bitmaps[0], bitmaps[1]);
    printf("Comparing the first bitmap (A) with the second bitmap (B)\n"
           "A == B: %d\n"
           "A > B: %d\n"
           "A < B: %d\n"
           "A >= B: %d\n"
           "A <= B: %d\n",
           result[0], result[1], result[2], result[3], result[4]);
    return ERR_SUCCESS;
}

int demo_bin_bitwise(bitmap_t *bitmaps[2])
{
    int bitmap_number = get_bitmap();
    if (bitmap_number < 0)
    {
        return bitmap_number;
    }
    char *end_ptr;
    long operation = get_long("Select the operation\n"
                              "1. AND\n"
                              "2. OR\n"
                              "3. XOR\n"
                              "Input: ", &end_ptr);
    if (operation <= 0 || operation > 3 || *end_ptr != '\0')
    {
        printf("Wrong operation\n");
        return ERR_WRONG_OPTION;
    }
    bitmap_t *temp;
    switch (operation)
    {
        case 1:
            temp = bitmap_and(bitmaps[0], bitmaps[1]);
            break;
        case 2:
            temp = bitmap_or(bitmaps[0], bitmaps[1]);
            break;
        case 3:
            temp = bitmap_xor(bitmaps[0], bitmaps[1]);
            break;
        default:
            return ERR_UNKNOWN;
    }
    bitmap_destroy(bitmaps[bitmap_number]);
    bitmaps[bitmap_number] = temp;
    return ERR_SUCCESS;
}

int demo_not_bitwise(bitmap_t *bitmaps[2])
{
    int bitmap_number = get_bitmap();
    if (bitmap_number < 0)
    {
        return bitmap_number;
    }
    bitmap_t *temp = bitmap_not(bitmaps[bitmap_number]);
    bitmap_destroy(bitmaps[bitmap_number]);
    bitmaps[bitmap_number] = temp;
    return ERR_SUCCESS;
}

int demo_concat(bitmap_t *bitmaps[2])
{
    int bitmap_number_source = get_bitmap();
    if (bitmap_number_source < 0)
    {
        return bitmap_number_source;
    }
    int bitmap_number_dest = (bitmap_number_source + 1) % 2;
    printf("Concatenating bitmap %d to %d\n",
           bitmap_number_source + 1, bitmap_number_dest + 1);
    bitmap_t *temp = bitmap_concat(bitmaps[bitmap_number_dest],
                                   bitmaps[bitmap_number_source]);
    bitmap_destroy(bitmaps[bitmap_number_dest]);
    bitmaps[bitmap_number_dest] = temp;
    return ERR_SUCCESS;
}

int demo_copy(bitmap_t *bitmaps[2])
{
    int bitmap_number_from = get_bitmap();
    if (bitmap_number_from < 0)
    {
        return bitmap_number_from;
    }
    int bitmap_number_to = (bitmap_number_from + 1) % 2;
    printf("Copying bitmap %d to %d\n",
           bitmap_number_from + 1,
           bitmap_number_to + 1); // TODO: check for existing copy
    bitmap_destroy(bitmaps[bitmap_number_to]);
    bitmaps[bitmap_number_to] = bitmap_copy(bitmaps[bitmap_number_from]);
    return ERR_SUCCESS;
}

int demo_clone(bitmap_t *bitmaps[2])
{
    int bitmap_number_from = get_bitmap();
    if (bitmap_number_from < 0)
    {
        return bitmap_number_from;
    }
    int bitmap_number_to = (bitmap_number_from + 1) % 2;
    printf("Cloning bitmap %d to %d\n",
           bitmap_number_from + 1, bitmap_number_to + 1);
    bitmap_destroy(bitmaps[bitmap_number_to]);
    bitmaps[bitmap_number_to] = bitmap_clone(bitmaps[bitmap_number_from]);
    return ERR_SUCCESS;
}

int demo_new(bitmap_t *bitmaps[2])
{
    int bitmap_number = get_bitmap();
    if (bitmap_number < 0)
    {
        return bitmap_number;
    }
    char *end_ptr;
    size_t input_num =
        get_ulong("Type in the size of the new bitmap: ", &end_ptr);
    if (*end_ptr != '\0')
    {
        printf("Wrong size\n");
        return ERR_BITMAP_SIZE; // TODO: Logger
    }
    bitmap_destroy(bitmaps[bitmap_number]);
    bitmaps[bitmap_number] = bitmap_init(input_num);
    return ERR_SUCCESS;
}

int demo_reset(bitmap_t *bitmaps[2])
{
    int bitmap_number = get_bitmap();
    if (bitmap_number < 0)
    {
        return bitmap_number;
    }
    bitmap_reset(bitmaps[bitmap_number]);
    return ERR_SUCCESS;
}

int demo_bmp(bitmap_t *bitmaps[2])
{
    int bitmap_number = get_bitmap();
    if (bitmap_number < 0)
    {
        return bitmap_number;
    }
    char *end_ptr;
    int width = (int) get_ulong("Type in the width of the image: ", &end_ptr);
    if (*end_ptr != '\0')
    {
        printf("Wrong width\n");
        return ERR_BITMAP_SIZE;
    }
    int height = (int) get_ulong("Type in the width of the image: ", &end_ptr);
    if (*end_ptr != '\0')
    {
        printf("Wrong height\n");
        return ERR_BITMAP_SIZE;
    }
    return bitmap_write_bmp("saved_bitmap.bmp", bitmaps[bitmap_number], width,
                            height); // TODO: Error handling
}

int demo_save(bitmap_t *bitmaps[2])
{
    int bitmap_number = get_bitmap();
    if (bitmap_number < 0)
    {
        return bitmap_number;
    }
    char path[128];
    printf("Type in the path to the file to save: ");
    scanf("%s", path);
    return bitmap_save(bitmaps[bitmap_number], path); // TODO: Error handling
}

int demo_load(bitmap_t *bitmaps[2])
{
    int bitmap_number = get_bitmap();
    if (bitmap_number < 0)
    {
        return bitmap_number;
    }
    char path[128];
    printf("Type in the path to the file to load: ");
    scanf("%s", path);
    return bitmap_load(bitmaps[bitmap_number], path); // TODO: Error handling
}

int demo_auto(bitmap_t *bitmaps[2])
{
    bitmap_t *op_result;
    printf("Creating new bitmaps of size 13 and 16\n");
    bitmap_destroy(bitmaps[0]);
    bitmap_destroy(bitmaps[1]);
    bitmaps[0] = bitmap_init(13);
    bitmaps[1] = bitmap_init(16);
    demo_print(bitmaps, "");
    clear_output(1);

    printf("Setting bit 3 of bitmap 1 and bit 8 of bitmap 2\n");
    bitmap_set_bit(bitmaps[0], 3, 1);
    bitmap_set_bit(bitmaps[1], 8, 1);
    demo_print(bitmaps, "");
    clear_output(1);

    printf("Bitwise AND\n");
    op_result = bitmap_and(bitmaps[0], bitmaps[1]);
    bitmap_print_bin(op_result);
    printf("\n");
    bitmap_destroy(op_result);
    clear_output(1);

    printf("Bitwise OR\n");
    op_result = bitmap_or(bitmaps[0], bitmaps[1]);
    bitmap_print_bin(op_result);
    printf("\n");
    bitmap_destroy(op_result);
    clear_output(1);

    printf("Bitwise XOR\n");
    op_result = bitmap_xor(bitmaps[0], bitmaps[1]);
    bitmap_print_bin(op_result);
    printf("\n");
    bitmap_destroy(op_result);
    clear_output(1);

    printf("Bitwise NOT (first bitmap)\n");
    op_result = bitmap_not(bitmaps[0]);
    bitmap_print_bin(op_result);
    printf("\n");
    bitmap_destroy(op_result);
    clear_output(1);

    printf("Cloning the second bitmap to the first one\n");
    bitmap_destroy(bitmaps[0]);
    bitmaps[0] = bitmap_clone(bitmaps[1]);
    demo_print(bitmaps, "");
    clear_output(1);

    printf("Comparing bitmaps\n");
    demo_compare(bitmaps);
    clear_output(1);

    printf("Setting bit 0 of the first bitmap to 1 and comparing bitmaps\n");
    bitmap_set_bit(bitmaps[0], 0, 1);
    demo_compare(bitmaps);
    clear_output(1);

    printf("Concatenating the second bitmap to the first bitmap\n");
    op_result = bitmap_concat(bitmaps[0], bitmaps[1]);
    bitmap_print_bin(op_result);
    printf("\n");
    bitmap_destroy(op_result);
    clear_output(1);

    printf("Copying the first bitmap to the second one\n");
    bitmap_destroy(bitmaps[1]);
    bitmaps[1] = bitmap_copy(bitmaps[0]);
    demo_print(bitmaps, "");
    clear_output(1);

    printf("Setting bit 10 of the first bitmap to 1\n");
    bitmap_set_bit(bitmaps[0], 10, 1);
    demo_print(bitmaps, "");
    clear_output(1);

    printf("Creating a new bitmap of size 128"
           "and reading from read_example.bitmap\n");
    bitmaps[0] = bitmap_init(128);
    bitmap_load(bitmaps[0], "read_example.bitmap");
    demo_print(bitmaps, "");
    clear_output(1);

    printf("Writing bitmap 1 to a bmp file (demo.bmp)\n");
    bitmap_write_bmp("demo.bmp", bitmaps[0], 2, 8);
    clear_output(1);

    printf("Writing bitmap 1 to a binary file (demo.bitmap)\n");
    bitmap_save(bitmaps[0], "demo.bitmap");
    clear_output(1);

    printf("Resetting bitmap 1\n");
    bitmap_reset(bitmaps[0]);
    demo_print(bitmaps, "");
    clear_output(1);

    return ERR_SUCCESS;
}
