// arguments_handler.c

#include "pathfinder.h"

void arguments_handler(t_app *app, int argc, char **argv) {
    // check if invalid value of arguments
    if(argc != 2) error_throw(ERROR_INVALID_ARGS, "arguments_handler");

    app->file_path = argv[1];
}
