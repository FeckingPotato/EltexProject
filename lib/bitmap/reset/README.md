# reset.h

Содержит функцию обнуления карты (с сохранением её размера)

## int bitmap_reset(const bitmap_t *bitmap);

Заполняет поле data нулями, возвращает 0 в случае успеха, -1 если bitmap равен NULL