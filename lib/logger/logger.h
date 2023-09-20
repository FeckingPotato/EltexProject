#pragma once
#define ON 1
#define OFF 0
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define WHITE "\033[37m"


typedef struct Logger {
    int file_enabled;
    int stderr_enabled;
    char* file;
} logger_t;

logger_t* logger_init();
void logger_enable_file(logger_t* logger);
void logger_disable_file(logger_t* logger);
void logger_enable_stderr(logger_t* logger);
void logger_disable_stderr(logger_t* logger);

void logger_set_path(
    logger_t* logger,
    const char* path);

void logger_log(
    logger_t* logger,
    const char* message, const char* level);

void logger_destroy(logger_t* logger);
