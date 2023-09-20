#include "bmp_test.h"
#include "../bitmap.h"
#include "../bitmap_struct.h"
#include <stdio.h>

#define BIT_SIZE 121

int bmp_test()
{
	bitmap_t* my_bitmap = bitmap_init(BIT_SIZE);

	for(int i = 0; i < BIT_SIZE; i++)
	{
		if (i % 3 == 0)
        {
            bitmap_set_bit(my_bitmap, i, 1);
        }
	}

	char* sample = "sample.bmp";
	char* testing = "testing.bmp";
	bitmap_write_bmp(testing, my_bitmap, 2, 8);
	FILE* sampleFP = fopen(sample, "rb");
	FILE* testingFP = fopen(testing, "rb");
	if (sampleFP != NULL && testingFP != NULL)
	{
		int sampleTmp = getc(sampleFP);
        int testingTmp = getc(testingFP);
        size_t byte_counter = 0;
		while (sampleTmp != EOF || testingTmp != EOF)
		{
			if(sampleTmp != testingTmp)
			{
                printf("EROR: sample bmp is not equal to testing bmp at "
                       "byte %zu\n", byte_counter);
				return -1;
			}
            sampleTmp = getc(sampleFP);
            testingTmp = getc(testingFP);
            byte_counter++;
		}
		fclose(sampleFP);
		fclose(testingFP);
        printf("Successfully written and read from bmp file\n");
		return 0;
	}
    printf("EROR: failed to open file\n");
	return -1;
}
