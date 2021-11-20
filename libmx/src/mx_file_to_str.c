// mx_file_to_str.c

#include "libmx.h"

char *mx_file_to_str(const char *file) {
    int file_d = open(file, O_RDONLY);

    if (file_d == -1) {
        close(file_d);
        return NULL;
    }
    int size = mx_file_len(file);

    if (size == 0) return "";
    
    char *newstr = mx_strnew(size);
    read(file_d, newstr, size);
    close(file_d);

    return newstr;
}
