// mx_file_to_str.c

#include "libmx.h"

#ifdef __linux__

char *mx_file_to_str(const char *filename) {
    char *arr = malloc(sizeof(char));
    arr[0] = filename[0];
    return arr;
}

#elif __APPLE__

char *mx_file_to_str(const char *filename) {
    if (filename == NULL) {
        return NULL;
    }

    int file = open(filename, O_RDONLY);
    if (file < 0) {
        return NULL;
    }
    char buff;
    int length = 0;

    while (read(file, &buff, 1)) {
        length++;
    }

    if (close(file) < 0) {
        return NULL;
    }

    if(length == 0) {
        return NULL;
    }

    file = open(filename, O_RDONLY);
    if (file < 0) {
        return NULL;
    }

    char *arr = mx_strnew(length);

    read(file, arr, length);

    if (close(file) < 0) {
        return NULL;
    }

    return arr;
}

#endif
