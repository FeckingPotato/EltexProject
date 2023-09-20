#include "ui.h"
#include "utils.h"
#include "err.h"
#include <stdio.h>
#include <logger.h>

#define LOG_PATH "./demo.log"

int main()
{
    bitmap_t *bitmaps[2];
    char input_string[10];
    char *end_ptr;
    long input_number;
    int exec_result;
    char error_string[10];
    logger_t *main_logger = logger_init();
    logger_set_path(main_logger, LOG_PATH);
    logger_enable_file(main_logger);
    logger_enable_stderr(main_logger);
    while (1)
    {
        exec_result = demo_init(bitmaps);
        if (exec_result == 0)
        {
            break;
        }
        clear_output(1);
    }
    clear_output(0);
    while (1)
    {
        printf("1. Print bitmaps (bin)\n"
               "1a. Print bitmaps(hex)\n"
               "2. Set bit\n"
               "3. Get bit\n"
               "4. Compare bitmaps\n"
               "5. Binary bitwise operations (overwrites the selected bitmap)\n"
               "6. Bitwise NOT (overwrites the selected bitmap)\n"
               "7. Concatenate the selected bitmap to another\n"
               "8. Copy the selected bitmap to another\n"
               "9. Clone the selected bitmap to another\n"
               "10. Replace an existing bitmap with a new one\n"
               "11. Save as bmp to saved_bitmap.bmp\n"
               "12. Save bitmap data to file\n"
               "13. Load bitmap data from file\n"
               "14. Reset bitmap\n"
               "15. Automated demo\n"
               "0. Exit\n"
               "Input: ");
        scanf("%s", input_string);
        input_number = strtol(input_string, &end_ptr, 10);
        clear_output(0);
        switch (input_number)
        {
            case 1:
                logger_log(main_logger, "Printing bitmaps (bin)", "info");
                exec_result = demo_print(bitmaps, end_ptr);
                break;
            case 2:
                logger_log(main_logger, "Printing bitmaps (hex)", "info");
                exec_result = demo_set_bit(bitmaps);
                break;
            case 3:
                logger_log(main_logger, "Getting bit", "info");
                exec_result = demo_get_bit(bitmaps);
                break;
            case 4:
                logger_log(main_logger, "Setting bit", "info");
                exec_result = demo_compare(bitmaps);
                break;
            case 5:
                logger_log(main_logger, "Entering the binary bitwise "
                                        "operator menu", "info");
                exec_result = demo_bin_bitwise(bitmaps);
                break;
            case 6:
                logger_log(main_logger, "Using NOT operator", "info");
                exec_result = demo_not_bitwise(bitmaps);
                break;
            case 7:
                logger_log(main_logger, "Concatenating bitmaps", "info");
                exec_result = demo_concat(bitmaps);
                break;
            case 8:
                logger_log(main_logger, "Copying a bitmap", "info");
                exec_result = demo_copy(bitmaps);
                break;
            case 9:
                logger_log(main_logger, "Cloning a bitmap", "info");
                exec_result = demo_clone(bitmaps);
                break;
            case 10:
                logger_log(main_logger, "Creating a new bitmap", "info");
                exec_result = demo_new(bitmaps);
                break;
            case 11:
                logger_log(main_logger, "Saving as bmp", "info");
                exec_result = demo_bmp(bitmaps);
                break;
            case 12:
                logger_log(main_logger, "Saving data", "info");
                exec_result = demo_save(bitmaps);
                break;
            case 13:
                logger_log(main_logger, "Loading data", "info");
                exec_result = demo_load(bitmaps);
                break;
            case 14:
                logger_log(main_logger, "resetting bitmap", "info");
                exec_result = demo_reset(bitmaps);
                break;
            case 15:
                logger_log(main_logger, "automated demo running", "info");
                exec_result = demo_auto(bitmaps);
                break;
            case 0:
                if (*end_ptr == '\0')
                {
                    exit(0);
                }
                exec_result = ERR_WRONG_OPTION;
            default:
                exec_result = ERR_WRONG_OPTION;
                break;
        }
        if (exec_result != ERR_SUCCESS)
        {
            sprintf(error_string, "%d", exec_result);
            logger_log(main_logger, error_string, "error");
        }
        else
        {
            logger_log(main_logger, "success", "info");
        }
        clear_output(1);
    }
}
