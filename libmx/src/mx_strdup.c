// mx_strdup.c

#include "libmx.h"

char *mx_strdup(const char *str){
    char *new_str = mx_strnew((mx_strlen(str)));
    
    if(str != NULL) {
        mx_strcpy(new_str, str);
        return new_str;
    }
    else {
        return NULL;
    }
}
