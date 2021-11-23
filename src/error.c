// error.c

#include "pathfinder.h"

/*
    ERROR_INVALID_POINTS_NUMBER,
    ERROR_DUPLICATE_PATHS,
    ERROR_OUT_OF_INT_MAX,
    ERROR_MEMORY_ALLOC,
    ERROR_SEGMENTATION_FAULT
*/

void error_throw(t_error error, char *arg) {
    switch (error) {
        case ERROR_INVALID_ARGS: {
            mx_printerr("usage: ./pathfinder [filename]\n");
        } break;

        case ERROR_FILE_NOT_EXIST: {
            mx_printerr("error: file ");
            mx_printerr(arg);
            mx_printerr(" does not exist\n");
        } break;

        case ERROR_EMPTY_FILE: {
            mx_printerr("error: file ");
            mx_printerr(arg);
            mx_printerr(" is empty\n");
        } break;

        case ERROR_INVALID_LINE: {
            mx_printerr("error: line ");
            mx_printerr(arg);
            mx_printerr(" is not valid\n");
        } break;

        case ERROR_INVALID_VERTICES_NUMBER: {
            mx_printerr("error: invalid number of islands\n");
        } break;

        case ERROR_DUPLICATE_PATHS: {
            mx_printerr("error: duplicate bridges\n");
        } break;

        case ERROR_OUT_OF_INT_MAX: {
            mx_printerr("error: sum of bridges lengths is too big\n");
        } break;

        case ERROR_MEMORY_ALLOC: {
            mx_printerr("error: [");
            mx_printerr(arg);
            mx_printerr("] memory is not allocated\n");
        } break;

        case ERROR_SEG_FAULT: {
            mx_printerr("error: [");
            mx_printerr(arg);
            mx_printerr("] segmentation fault\n");
        } break;
    
        default: {
            mx_printerr("error: unknown error");
        } break;
    }
    exit(1);
}
