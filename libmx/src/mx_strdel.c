// mx_strdel.c

#include "libmx.h"

void mx_strdel(char **str) {
    free(*str);
    *str = NULL;
}
