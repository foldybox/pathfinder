// mx_count_substr.c

#include "libmx.h"

int mx_count_substr(const char *str, const char* sub) {
    int res = 0;

    if (str == NULL || sub == NULL) {
        return -1;
    }
    if(mx_strlen(str) < mx_strlen(sub)) {
        return res;
    }

    while (*str != '\0') {
        if (!mx_strncmp((char *)str, (char *)sub, mx_strlen(sub))) {
            res++;
        } 
        str++;
    }

    return res;
}
