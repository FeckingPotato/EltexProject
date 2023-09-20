#include "bitwise_test.h"
#include "../bitmap.h"
#include "../bitmap_struct.h"
#include <stdio.h>

int bitwise_test()
{
	bitmap_t* first_var = bitmap_init(8);
	bitmap_set_bit(first_var, 2, 1);
	bitmap_set_bit(first_var, 3, 1);
	bitmap_set_bit(first_var, 5, 1);
	bitmap_set_bit(first_var, 6, 1);

	bitmap_t* second_var = bitmap_init(8);
	bitmap_set_bit(second_var, 1, 1);
	bitmap_set_bit(second_var, 2, 1);
	bitmap_set_bit(second_var, 5, 1);
	bitmap_set_bit(second_var, 6, 1);
	bitmap_set_bit(second_var, 7, 1);

	bitmap_t* and_sample = bitmap_init(8);
	bitmap_set_bit(and_sample, 2, 1);
	bitmap_set_bit(and_sample, 5, 1);
	bitmap_set_bit(and_sample, 6, 1);

	bitmap_t* or_sample = bitmap_init(8);
	bitmap_set_bit(or_sample, 1, 1);
	bitmap_set_bit(or_sample, 2, 1);
	bitmap_set_bit(or_sample, 3, 1);
	bitmap_set_bit(or_sample, 5, 1);
	bitmap_set_bit(or_sample, 6, 1);
	bitmap_set_bit(or_sample, 7, 1);

	bitmap_t* xor_sample = bitmap_init(8);
	bitmap_set_bit(xor_sample, 1, 1);
	bitmap_set_bit(xor_sample, 3, 1);
	bitmap_set_bit(xor_sample, 7, 1);

	bitmap_t* not_sample = bitmap_init(8);
	bitmap_set_bit(not_sample, 1, 1);
	bitmap_set_bit(not_sample, 4, 1);
	bitmap_set_bit(not_sample, 7, 1);
	bitmap_set_bit(not_sample, 8, 1);


	bitmap_t* result = bitmap_and(first_var, second_var);

	for(size_t i = 1; i < 9; i++)
	{
		if(bitmap_get_bit(result, i) != bitmap_get_bit(and_sample, i))
		{
            printf("ERROR: AND failure\n");
			return -1;
		}
	}

	result = bitmap_or(first_var, second_var);

	for(size_t i = 1; i < 9; i++)
	{
		if(bitmap_get_bit(result, i) != bitmap_get_bit(or_sample, i))
		{
            printf("ERROR: OR failure\n");
			return -2;
		}
	}

	result = bitmap_xor(first_var, second_var);

	for(size_t i = 1; i < 9; i++)
	{
		if(bitmap_get_bit(result, i) != bitmap_get_bit(xor_sample, i))
		{
            printf("ERROR: XOR failure\n");
			return -3;
		}
	}

	result = bitmap_not(first_var);

	for(size_t i = 1; i < 9; i++)
	{
		if(bitmap_get_bit(result, i) != bitmap_get_bit(not_sample, i))
		{
            printf("ERROR: NOT failure\n");
			return -4;
		}
	}
    printf("Successfully tested bitwise operations\n");
	return 0;

}