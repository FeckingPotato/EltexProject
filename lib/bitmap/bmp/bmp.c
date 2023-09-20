#include "../bitmap.h"
#include "../bitmap_struct.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TYPE_FILE         0x4D42    // BM
#define NUM_PLANE           1       // Number of layers
#define COMPRESSION         0       // No compression
#define NUM_COLORS          0       // Number of colors used
#define IMPORTANT_COLORS    0       // Number of important colors
#define BITS_PER_PIXEL      1       // The number of bits encoding a pixel
#define BMP_HEADER_SIZE     54      // Standard BMP header size
#define DIB_HEADER_SIZE     40      // Standard DIB header size
#define RESOLUTION_PPM      0       // Standard PPM resolution
#define RGB_TABLE_SIZE      8       // RGB table size

typedef struct
{
    uint16_t type;              // File type: 0x4d42 (BM)
    uint32_t size;              // File size in bytes
    uint16_t reserved1;         // Not used (0)
    uint16_t reserved2;         // Not used (0)
    uint32_t offset;            // Image data offset in bytes
    uint32_t dib_header_size;   // DIB Header size in bytes
    int32_t width_px;          // Image width
    int32_t height_px;         // Image height
    uint16_t num_planes;        // Number of color planes
    uint16_t bits_per_pixel;    // Bits per pixel
    uint32_t compression;       // Compression type
    uint32_t image_size_bytes;  // Image size in bytes
    int32_t x_resolution_ppm;  // Pixels per meter
    int32_t y_resolution_ppm;  // Pixels per meter
    uint32_t num_colors;        // Number of colors
    uint32_t important_colors;  // Important colors
} BMPHeader;

typedef struct
{
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
    uint8_t rgbReserved;
} RGBQUAD;

BMPHeader *filling_head(
    bitmap_t *my_bitmap,
    int32_t width,
    int32_t height)
{
    BMPHeader *bmp_header = (BMPHeader *) malloc(sizeof(BMPHeader));

    bmp_header->type = TYPE_FILE;
    bmp_header->reserved1 = 0;
    bmp_header->reserved2 = 0;
    bmp_header->offset = BMP_HEADER_SIZE + RGB_TABLE_SIZE;
    bmp_header->dib_header_size = DIB_HEADER_SIZE;
    bmp_header->num_planes = NUM_PLANE;
    bmp_header->compression = COMPRESSION;
    bmp_header->num_colors = NUM_COLORS;
    bmp_header->important_colors = IMPORTANT_COLORS;
    bmp_header->bits_per_pixel = BITS_PER_PIXEL;
    bmp_header->size = BMP_HEADER_SIZE + RGB_TABLE_SIZE + my_bitmap->size_bytes;
    bmp_header->image_size_bytes = my_bitmap->size_bytes;
    bmp_header->height_px = height;
    bmp_header->width_px = width;
    bmp_header->x_resolution_ppm = RESOLUTION_PPM;
    bmp_header->y_resolution_ppm = RESOLUTION_PPM;

    return bmp_header;
}

RGBQUAD *get_color(
    uint8_t first,
    uint8_t second,
    uint8_t third,
    uint8_t fourth)
{
    RGBQUAD *color = (RGBQUAD *) malloc(sizeof(RGBQUAD));

    color->rgbBlue = first;
    color->rgbGreen = second;
    color->rgbRed = third;
    color->rgbReserved = fourth;

    return color;
}

int bitmap_write_bmp(
    char *fileName,
    bitmap_t *my_bitmap,
    int32_t width,
    int32_t height)
{

    FILE *fp = fopen(fileName, "wb");

    if (fp == NULL)
    {
        perror("can`t open the file");
        return -1;
    }

    if ((width * height) > my_bitmap->size_bytes)
    {
        perror("the image is too large for this bitmap");
        return -1;
    }

    if ((width * height) < my_bitmap->size_bytes)
    {
        perror("the image is too small for this bitmap");
    }

    if (width < height)
    {
        int32_t tmp = width;
        width = height;
        height = tmp;
        perror("the ratio has been changed");
    }

    // BMPHeader initialization
    BMPHeader *header = filling_head(my_bitmap, width, height);

    // BMPColor initialization
    RGBQUAD *black = get_color(0, 0, 0, 0);
    RGBQUAD *white = get_color(0xff, 0xff, 0xff, 0xff);

    //Writing header
    size_t num_write = fwrite(&header->type, sizeof(header->type), 1, fp);
    num_write += fwrite(&header->size, sizeof(header->size), 1, fp);
    num_write += fwrite(&header->reserved1, sizeof(header->reserved1), 1, fp);
    num_write += fwrite(&header->reserved2, sizeof(header->reserved2), 1, fp);
    num_write += fwrite(&header->offset, sizeof(header->offset), 1, fp);
    num_write += fwrite(&header->dib_header_size, sizeof(header->dib_header_size), 1, fp);
    num_write += fwrite(&header->width_px, sizeof(header->width_px), 1, fp);
    num_write += fwrite(&header->height_px, sizeof(header->height_px), 1, fp);
    num_write += fwrite(&header->num_planes, sizeof(header->num_planes), 1, fp);
    num_write += fwrite(&header->bits_per_pixel, sizeof(header->bits_per_pixel), 1, fp);
    num_write += fwrite(&header->compression, sizeof(header->compression), 1, fp);
    num_write += fwrite(&header->image_size_bytes, sizeof(header->image_size_bytes), 1, fp);
    num_write += fwrite(&header->x_resolution_ppm, sizeof(header->x_resolution_ppm), 1, fp);
    num_write += fwrite(&header->y_resolution_ppm, sizeof(header->y_resolution_ppm), 1, fp);
    num_write += fwrite(&header->num_colors, sizeof(header->num_colors), 1, fp);
    num_write += fwrite(&header->important_colors, sizeof(header->important_colors), 1, fp);

    num_write += fwrite(white, 4, 1, fp);
    num_write += fwrite(black, 4, 1, fp);


    //Writing data
    num_write += fwrite(my_bitmap->data, my_bitmap->size_bytes, 1, fp);
    fclose(fp);

    return 0;
}
