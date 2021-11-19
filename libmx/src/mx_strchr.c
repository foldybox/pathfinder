// mx_strchr.c

#include "libmx.h"

char *mx_strchr(const char *s, int c) {
    while(1) {
        if(*s == c) {
            return (char *) s;
        }
        else if(*s == '\0'){
            if(c == '\0'){
                return (char *) s;
            }
            else {
                return NULL;
            }
        }
        else {
            s++;
        }
    }
}
