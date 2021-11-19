// error.c

#include "pathfinder.h"

void error_throw(t_error error, char *arg) {
    if(error == ERROR_DUPLICATE_PATHS) {
        
    }
    mx_printerr(arg);
}
