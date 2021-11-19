// mx_del_strarr.c

#include "libmx.h"

void mx_del_strarr(char ***arr) {
    while(**arr != NULL) {
        mx_strdel(*arr);
        arr++;
    }

    free(**arr);
    **arr = NULL;
}
