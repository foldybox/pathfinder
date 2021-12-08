// pathfinder.h
#ifndef PATHFINDER_H
#define PATHFINDER_H

// Uncomment to switch to Debug mode
//#define _DEBUG_

#include <stdlib.h>
#include "libmx.h"
#include "error.h"

#ifdef _DEBUG_
    #include <stdio.h>
#endif

/// Edge structure
typedef struct s_edge {
    int from;
    int to;
    int length;
} t_edge;

/// Path structure
typedef struct s_path {
    int from;
    int to;
    int length;
    int vertices_count;
    int lengths_count;
    int *vertices;
    int *lengths;
} t_path;


/// Global application structure that contains global variables and arrays
typedef struct s_app {
    char *file_path;
    char *file_text;
    int vertices_count;
    int edges_count;
    char **vertices;
    t_edge *edges;
    t_list *paths;
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

/// A function that validate splited file data, checks for errors and returns boolean.
/// \param **from pointer to 'from' string
/// \param **to pointer to 'to' string
/// \param **length pointer to 'length' string
/// \return True if validate was success and False if not
bool file_data_validate(char **from, char **to, char **length);

/// A function that finds all shortest paths and fills up them into 'paths' global array.
/// \param *app pointer to global application variable
void paths_find(t_app *app);

/// A function that prints each path from 'paths' global array to standard output.
/// \param *app pointer to global application variable
void paths_print(t_app *app);

bool paths_list_cmp(void *a, void *b);

#endif // !PATHFINDER_H
