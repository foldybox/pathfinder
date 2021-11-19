// pathfinder.h
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <stdlib.h>
#include "libmx.h"
#include "error.h"

typedef struct s_edge {
    int from;
    int to;
    int length;
} t_edge;

typedef struct s_path {
    int from;
    int to;
    int length;
    t_list *vertices;
    t_list *lengths;
} t_path;

typedef struct s_app {
    char *file_path;
    char **vertices;
    t_edge *edges;
    t_path *paths;
} t_app;


/// A function that allocates memory for global application variable and sets all its fields to NULL.
/// \return pointer to global application variable
t_app *app_init();

/// A function that frees up application memory.
/// \param *app pointer to global application variable
void app_free(t_app *app);

/// A function that handles command line arguments, checks for errors and sets 'file_path' global variable.
/// \param *app pointer to global application variable
/// \param argc count of command line arguments
/// \param **argv array of command line arguments
void arguments_handler(t_app *app, int argc, char **argv);

// A function that reads file, checks for errors and fill up 'vertices' and 'edges' global arrays.
/// \param *app pointer to global application variable
void read_file(t_app *app);

// A function that finds all shortest paths and fills up them into 'paths' global array.
/// \param *app pointer to global application variable
void pathfinder(t_app *app);

// A function that prints each path from 'paths' global array to standard output.
/// \param *app pointer to global application variable
void print_paths(t_app *app);

#endif // !PATHFINDER_H
