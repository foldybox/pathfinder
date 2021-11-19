// mx_strstr.c

#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    if(mx_strlen(haystack) < mx_strlen(needle)) {
        return NULL;
    }

    while(*haystack != '\0'){
        if(mx_strncmp(haystack, needle, mx_strlen(needle)) == 0) {
            return mx_strchr(haystack, *needle);
        }
        haystack++;
    }

    return NULL;
}
