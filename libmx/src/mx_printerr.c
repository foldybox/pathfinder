// mx_printerr.c

#include "libmx.h"

void mx_printerr(const char *s) {
    write(0, s, mx_strlen(s));
}
