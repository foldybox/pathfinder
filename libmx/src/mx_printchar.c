// mx_printchar.c

#include "libmx.h"

void mx_printchar(char c){
    char *buff = &c;
    write(1, buff, 1);
}


