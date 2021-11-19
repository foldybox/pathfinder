// main.c

#include "pathfinder.h"

int main(int argc, char **argv) {
    t_app *app = app_init(); // init global app variables

    arguments_handler(app, argc, argv); // handle args errors and set $file_path variable
    read_file(app); // read file, handle errors and fill up $vertices and $edges arrays
    pathfinder(app); // find all paths and write it into $paths array
    print_paths(app); // print each path

    app_free(app); // free up memory
    return 0;
}
