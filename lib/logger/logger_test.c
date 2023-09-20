#include "logger_test.h"
#include "logger.h"
#include <stdio.h>

int logger_test() 
{

    logger_t* logger = logger_init();

    if (logger == NULL)
    {
        return -1;
    }

    logger_set_path(logger, "demo.txt");

    logger_enable_file(logger);
    logger_enable_stderr(logger);

    printf("\n--- All modes are enabled ---\n");

    logger_log(logger, "error", "error");
    logger_log(logger, "warning", "warning");
    logger_log(logger, "info", "info by default");

    logger_disable_file(logger);
    logger_disable_stderr(logger);
    printf("\n--- All modes are disabled ---\n");
    logger_log(logger, "And this will not.", "");

    logger_enable_file(logger);
    printf("\n--- Only file mode is enabled ---\n");
    logger_log(logger, "Only to file.", "");

    logger_disable_file(logger);
    logger_enable_stderr(logger);
    printf("\n--- Only stderr mode is enabled ---\n");
    logger_log(logger, "Only to stderr.", "");

    logger_destroy(logger);
    printf("\n--- Logger destroyed ---\n");

    return 0;
}
