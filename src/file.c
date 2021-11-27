// file.c

#include "pathfinder.h"

void file_read(t_app *app) {
    if(app == NULL) error_throw(ERROR_SEG_FAULT, "arguments_handler");

    #ifdef _DEBUG_
        mx_printstr("File path: ");
        mx_printstr(app->file_path);
        mx_printchar('\n');
    #endif

    // read file to string
    app->file_text = mx_file_to_str(app->file_path);

    // check if file does not exist
    if(app->file_text == NULL) error_throw(ERROR_FILE_NOT_EXIST, app->file_path);

    // check if file is empty
    if(mx_strlen(app->file_text) == 0) error_throw(ERROR_EMPTY_FILE, app->file_path);
}

void file_parse(t_app *app) {
    int temp_vertices_count = 0;

    // split file text by \n into 2d array
    char **file_splited = mx_strsplit(app->file_text, '\n');

    // check if first line is not valid
    if(!mx_isnum(file_splited[0])) error_throw(ERROR_INVALID_LINE, "1");

    // set up sizes of global arrays
    app->vertices_count = mx_atoi(file_splited[0]);
    app->edges_count = 0;
    while(file_splited[app->edges_count])
        app->edges_count++;
    app->edges_count--;

    // check if vertices count is invalid
    if(app->vertices_count < 0) error_throw(ERROR_INVALID_LINE, "1");

    #ifdef _DEBUG_
        mx_printstr("Vertices count: ");
        mx_printint(app->vertices_count);
        mx_printchar('\n');
        mx_printstr("Edges count: ");
        mx_printint(app->edges_count);
        mx_printchar('\n');
    #endif

    // allocate memory for global arrays
    app->vertices = malloc(app->vertices_count * sizeof(char **));
    if(app->vertices == NULL) error_throw(ERROR_MEMORY_ALLOC, "file_parse:vertices");
    mx_memset(app->vertices, 0, app->vertices_count * sizeof(char **));
    app->edges = malloc(app->edges_count * sizeof(t_edge));
    if(app->edges == NULL) error_throw(ERROR_MEMORY_ALLOC, "file_parse:edges");
    mx_memset(app->edges, 0, app->edges_count * sizeof(t_edge));

    // go through all lines
    for(int i = 1; i < app->edges_count + 1; i++) {
        char *from = NULL;
        char *to = NULL;
        char *length = NULL;
        int from_index = -1; 
        int to_index = -1;
        int len = -1;

        // parse line to temporary variables
        if(!file_line_parse(file_splited[i], &from, &to, &length)) error_throw(ERROR_INVALID_LINE, mx_itoa(i + 1));
        // validate temporary variables
        if(!file_data_validate(&from, &to, &length)) error_throw(ERROR_INVALID_LINE, mx_itoa(i + 1));

        // check and add a vertices to global array from temporary variables and set their indexes
        for (int i = 0; i < app->vertices_count; i++) {
            if(app->vertices[i] == 0) {
                from_index = i;
                app->vertices[i] = mx_strdup(from);
                temp_vertices_count++;
                break;
            }
            if(!mx_strcmp(from, app->vertices[i])) {
                from_index = i;
                break;
            }
        }
        for (int i = 0; i < app->vertices_count; i++) {
            if(app->vertices[i] == 0) {
                to_index = i;
                app->vertices[i] = mx_strdup(to);
                temp_vertices_count++;
                break;
            }
            if(!mx_strcmp(to, app->vertices[i])) {
                to_index = i;
                break;
            }
        }

        // convert length from string to int
        len = mx_atoi(length);

        // check if exist copies of vertices in global array
        for (int i = 0; i < app->edges_count; i++) {
            if((from_index == app->edges[i].from && to_index == app->edges[i].to) ||
               (to_index == app->edges[i].from && from_index == app->edges[i].to)) {
                error_throw(ERROR_DUPLICATE_PATHS, "");
            }
        }

        // set parameters of current edge
        app->edges[i - 1].from = from_index;
        app->edges[i - 1].to = to_index;
        app->edges[i - 1].length = len;

        // free allocated memory
        free(from);
        free(to);
        free(length);
    }

    // check if invalid count of vertices in global array
    if(app->vertices_count != temp_vertices_count) error_throw(ERROR_INVALID_VERTICES_NUMBER, "");
    for(int i = 0; i < app->edges_count; i++) {
        if((app->edges[i].from < 0) || (app->edges[i].to < 0)) {
            error_throw(ERROR_INVALID_VERTICES_NUMBER, "");
        }
    }

    // check if length of all edges is too big
    unsigned int length_sum = 0;
    for(int i = 0; i < app->edges_count; i++) {
        length_sum += app->edges[i].length;
    }
    if(length_sum > INT_MAX) error_throw(ERROR_OUT_OF_INT_MAX, "");

    #ifdef _DEBUG_
        mx_printstr("\nVertices list:\n");
        for (int i = 0; i < app->vertices_count; i++) {
            mx_printint(i);
            mx_printstr(": ");
            mx_printstr(app->vertices[i]);
            mx_printchar('\n');
        }

        mx_printstr("\nEdges list:\n");
        for (int i = 0; i < app->edges_count; i++) {
            mx_printstr("[");
            mx_printstr(app->vertices[app->edges[i].from]);
            mx_printstr(" -> ");
            mx_printstr(app->vertices[app->edges[i].to]);
            mx_printstr("] = ");
            mx_printint(app->edges[i].length);
            mx_printchar('\n');
        }
    #endif

    // free allocated memory
    for (int i = 0; i < app->edges_count + 3; i++) {
        free(file_splited[i]);
    }
    free(file_splited);
    file_splited = NULL;
}

bool file_line_parse(const char *line, char **from, char **to, char **length) {
    // find first delimiter
    int hyphen_index = mx_get_char_index(line, '-');
    if(hyphen_index <= 0) return false;
    
    // set first vertice name
    *from = mx_strndup(line, hyphen_index);
    if(*from == NULL) error_throw(ERROR_MEMORY_ALLOC, "file_line_parse:from");

    // find second delimiter
    line += hyphen_index + 1;
    int comma_index = mx_get_char_index(line, ',');
    if(comma_index <= 0) return false;

    // set second vertice name
    *to = mx_strndup(line, comma_index);
    if(*to == NULL) error_throw(ERROR_MEMORY_ALLOC, "file_line_parse:to");

    // set lenght string
    line += comma_index + 1;
    *length = mx_strdup(line);
    if(*length == NULL) error_throw(ERROR_MEMORY_ALLOC, "file_line_parse:length");
    if(mx_strlen(*length) == 0) return false;

    return true;
}

bool file_data_validate(char **from, char **to, char **length) {
    // check if vertices name is invalid
    for(int i = 0; i < mx_strlen(*from); i++) {
        if(!(mx_isalpha(from[0][i]) || mx_isdigit(from[0][i]))) return false;
    }
    for(int i = 0; i < mx_strlen(*to); i++) {
        if(!(mx_isalpha(to[0][i]) || mx_isdigit(to[0][i]))) return false;
    }

    // check if vertices name is equal
    if(!mx_strcmp(*from, *to)) return false;

    // check if length string in invalid
    for(int i = 0; i < mx_strlen(*length); i++) {
        if( !mx_isdigit(length[0][i]) ) return false;
    }

    return true;
}
