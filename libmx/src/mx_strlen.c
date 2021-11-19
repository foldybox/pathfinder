// mx_strlen.c

#include "libmx.h"

int mx_strlen(const char *s) {
    int index = 0;

    while (s[index] != '\0') {
        index++;
    }

    return index;
}
