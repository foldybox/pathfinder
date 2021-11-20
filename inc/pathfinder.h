// pathfinder.h
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <stdlib.h>
#include "libmx.h"
#include "error.h"

#define _DEBUG_

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
    char *file_text;
    int vertices_count;
    int edges_count;
    char **vertices;
    t_edge *edges;
    t_path *paths;
} t_app;


/// A function that allocates memory for global application variable and sets all its fields to NULL.
/// \return Pointer to global application variable
t_app *app_init();

/// A function that frees up application memory.
/// \param *app pointer to global application variable
void app_free(t_app *app);

/// A function that handles command line arguments, checks for errors and sets 'file_path' global variable.
/// \param *app pointer to global application variable
/// \param argc count of command line arguments
/// \param **argv array of command line arguments
void arguments_handler(t_app *app, int argc, char **argv);

/// A function that reads file, checks for errors and fill up 'file_text' global variable.
/// \param *app pointer to global application variable
void file_read(t_app *app);

/// A function that parses file text, checks for errors and fill up 'vertices' and 'edges' global arrays.
/// \param *app pointer to global application variable
void file_parse(t_app *app);

/// A function that parses file line, checks for errors and returns splited data.
/// \param *line pointer to file line to parse
/// \param **from pointer to 'from' string
/// \param **to pointer to 'to' string
/// \param **length pointer to 'length' string
/// \return True if parse was success and False if not
bool file_line_parse(const char *line, char **from, char **to, char **length);

/// A function that validate file line, checks for errors and returns boolean.
/// \param **from pointer to 'from' string
/// \param **to pointer to 'to' string
/// \param **length pointer to 'length' string
/// \return True if validate was success and False if not
bool file_line_validate(char **from, char **to, char **length);

/// A function that finds all shortest paths and fills up them into 'paths' global array.
/// \param *app pointer to global application variable
void pathfinder(t_app *app);

/// A function that prints each path from 'paths' global array to standard output.
/// \param *app pointer to global application variable
void print_paths(t_app *app);

#endif // !PATHFINDER_H
