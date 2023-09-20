# Логирование
## logger.h
Содержит функции, позволяющие пользователю настроить логирование в процессе работы программы.
## logger_t *logger_init()
Инициализирует структуру логгера, выделяя под нее память, не включая логирование.
## void logger_enable_file(logger_t *logger)
Включает функцию логирования и записи в файл.
## void logger_disable_file(logger_t *logger)
Выключает логирование в файл.
## void logger_enable_stderr(logger_t *logger)
Включает функцию логирования и записи в stderr.
## void logger_disable_stderr(logger_t *logger)
Выключает логирование в stderr.
## void logger_set_path(logger_t *logger, const char* path)
Принимает в качестве входных параметров путь к файлу, куда будет вестись запись. Если файла не существует, он будет создан.
## void logger_log(logger_t *logger, const char* message, const char* level)
Записывает сообщение в лог-файл. Уровень level определяется пользователем: "error" - ошибка, "warning" - предупреждение, "info" - информация.
<br>
***Примечание***: уровень info настроен по умолчанию, не трубется вводить данные для установки данного уровня критичности.
## void logger_destroy(logger_t *logger)
Освобождает память, выделенную для структуры логгера.  
