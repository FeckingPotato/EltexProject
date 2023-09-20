#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#define TIME_STRING_SIZE 40
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

size_t set_time(struct tm* time_struct, char time_string[TIME_STRING_SIZE])
{
    memset(time_string, 0, TIME_STRING_SIZE);
    size_t length = strftime(time_string, TIME_STRING_SIZE,
        "%d.%m.%Y %H:%M:%S, %A", time_struct);
    return length;
}

logger_t* logger_init()
{
    logger_t* logger = (logger_t*)calloc(sizeof(logger_t), 1);
    return logger;
}

void logger_enable_file(logger_t* logger)
{
    logger->file_enabled = ON;
}

void logger_disable_file(logger_t* logger)
{
    logger->file_enabled = OFF;
}

void logger_enable_stderr(logger_t* logger)
{
    logger->stderr_enabled = ON;
}

void logger_disable_stderr(logger_t* logger)
{
    logger->stderr_enabled = OFF;
}

void logger_set_path(
    logger_t* logger,
    const char* path)
{
    if (logger->file != NULL)
    {
        free(logger->file);
    }
    logger->file = (char*)malloc(strlen(path) + 1);
    strcpy(logger->file, path);
}

void logger_log(logger_t* logger,
    const char* message, 
    const char* level)
{
    if (logger->file_enabled == OFF && logger->stderr_enabled == OFF)
        return;

    struct tm* time_struct;
    char time_string[TIME_STRING_SIZE];
    const time_t timer = time(NULL);
    time_struct = localtime(&timer);
    set_time(time_struct, time_string);

    if (logger->file_enabled) 
    {
        FILE* log_file = fopen(logger->file, "a");

        if (log_file)
        {
            char useful_info[200];

            strcpy(useful_info, "[");
            strcat(useful_info, time_string);
            strcat(useful_info, "] ");

            if (strcmp(level, "warning") == 0) 
                strcat(useful_info, "WARN: ");

            else if (strcmp(level, "error") == 0)
                strcat(useful_info, "ERROR: ");

            else
                strcat(useful_info, "INFO: ");

            strcat(useful_info, message);
            strcat(useful_info, "\n");

            fputs(useful_info, log_file);
            fclose(log_file);
        }
        else
            perror("Something went wrong. File could not be opened.\n"
                "Try to specify a different path.\n");
    }

    if (logger->stderr_enabled) 
    {

        if (strcmp(level, "warning") == 0)
        {
            fprintf(stderr, YELLOW "[%s] WARN: "
                    WHITE "%s\n", time_string, message);
        }

        else if (strcmp(level, "error") == 0)
        {
            fprintf(stderr, RED "[%s] ERROR: "
                    WHITE "%s\n", time_string, message);
        }

        else
        {
            fprintf(stderr, GREEN "[%s] INFO: "
                    WHITE "%s\n", time_string, message);
        }
        
    }
   
}

void logger_destroy(logger_t* logger)
{
    free(logger->file);
    free(logger);
}
