// mx_printchar.c

#include "libmx.h"

void mx_printchar(char c){
    char *buff = &c;
    write(STDOUT_FILENO, buff, 1);
}
