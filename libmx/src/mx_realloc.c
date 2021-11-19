// mx_realloc.c

#include "libmx.h"

void *mx_realloc(void *ptr, size_t new_size) {
    size_t cur_size;
    void *new_ptr;

    if (ptr == 0) return malloc(new_size);

    #ifdef __APPLE__
    cur_size = malloc_size(ptr);
    #elif __linux__
    cur_size = malloc_usable_size(ptr);
    #endif

    if (new_size <= cur_size) return ptr;

    new_ptr = malloc(new_size);
    mx_memcpy(new_ptr, ptr, cur_size);
    free(ptr);

    return new_ptr;
}
