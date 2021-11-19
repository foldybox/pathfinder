// mx_strncpy.c

#include "libmx.h"

char* mx_strncpy(char *dst, const char *src, int len) {
    int i = 0;

    while (src[i] && i != len) {
        dst[i] = src[i];
        i++;
    }

    if(i < len) {
        dst[i] = '\0';
    }

    return dst;
}
