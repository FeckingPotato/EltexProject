#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
void clear_stdin()
{
    stdin->_IO_read_ptr = stdin->_IO_read_end;
}

void clear_output(int anykey)
{
    if (anykey)
    {
        printf("Press ENTER to continue.");
        fflush(stdout);
        clear_stdin();
        getc(stdin);
    }
    system(CLEAR);
}
