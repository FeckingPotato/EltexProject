#include "../lib/logger/logger_test.h"
#include "../lib/bitmap/comp/comp_test.h"
#include "../lib/bitmap/copy_clone/copy_clone_test.h"
#include "../lib/bitmap/concat/concat_test.h"
#include "../lib/bitmap/bitwise/bitwise_test.h"
#include "../lib/bitmap/bmp/bmp_test.h"
#include "../lib/bitmap/save_load/save_load_test.h"
#include "../lib/bitmap/reset/reset_test.h"
#include <stdio.h>

int main()
{
    printf("Logger test\n");
    if (logger_test() != 0)
    {
        return -1;
    }
    printf("\n\n\nComparison test\n");
    if (comp_test() != 0)
    {
        return -1;
    }
    printf("\n\n\nCopying/cloning test\n");
    if (copy_clone_test() != 0)
    {
        return -1;
    }
    printf("\n\n\nConcatenation test\n");
    if (concat_test() != 0)
    {
        return -1;
    }
    printf("\n\n\nBitwise test\n");
    if (bitwise_test() != 0)
    {
        return -1;
    }
    printf("\n\n\nBMP test\n");
    if (bmp_test() != 0)
    {
        return -1;
    }
    printf("\n\n\nSave/load test\n");
    if (save_load_test() != 0)
    {
        return -1;
    }
    printf("\n\n\nReset test\n");
    if (reset_test() != 0)
    {
        return -1;
    }
}