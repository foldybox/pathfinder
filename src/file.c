// read_file.c

#include "pathfinder.h"

void file_read(t_app *app) {
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

    // #ifdef _DEBUG_
    //     mx_printstr("File content:\n");
    //     mx_printstr(app->file_text);
    //     mx_printchar('\n');
    // #endif
}

void file_parse(t_app *app) {
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

/*
    1. Split line to strings: vertice0, vertice1, length.
    2. Check if vertices exist in the array and save them and their indexes.
    3. Set indexes and length in the edge struct.
*/

    for(int i = 1; i < app->edges_count + 1; i++) {
        char *from = NULL;
        char *to = NULL;
        char *length = NULL;
        int from_index = -1; 
        int to_index = -1;
        int len = -1;

        if(!file_line_parse(file_splited[i], &from, &to, &length)) error_throw(ERROR_INVALID_LINE, mx_itoa(i + 1));
        if(!file_line_validate(&from, &to, &length)) error_throw(ERROR_INVALID_LINE, mx_itoa(i + 1));

        for (int j = 0; j < app->vertices_count; j++) {
            if(app->vertices[j] == 0) {
                from_index = j;
                app->vertices[j] = mx_strdup(from);
                break;
            }
            if(!mx_strcmp(from, app->vertices[j])) {
                from_index = j;
                break;
            }
        }

        for (int j = 0; j < app->vertices_count; j++) {
            if(app->vertices[j] == 0) {
                to_index = j;
                app->vertices[j] = mx_strdup(to);
                break;
            }
            if(!mx_strcmp(to, app->vertices[j])) {
                to_index = j;
                break;
            }
        }

        len = mx_atoi(length);

        for (int i = 0; i < app->edges_count; i++) {
            if((from_index == app->edges[i].from && to_index == app->edges[i].to) ||
               (to_index == app->edges[i].from && from_index == app->edges[i].to)) {
                error_throw(ERROR_DUPLICATE_PATHS, "");
            }
        }

        app->edges[i - 1].from = from_index;
        app->edges[i - 1].to = to_index;
        app->edges[i - 1].length = len;

        free(from);
        free(to);
        free(length);
    }

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
            mx_printint(app->edges[i].from);
            mx_printstr("-");
            mx_printint(app->edges[i].to);
            mx_printstr("] => ");
            mx_printint(app->edges[i].length);
            mx_printchar('\n');
        }
    #endif

    free(file_splited);
}

bool file_line_parse(const char *line, char **from, char **to, char **length) {
    int hyphen_index = mx_get_char_index(line, '-');
    if(hyphen_index <= 0) return false;

    *from = mx_strndup(line, hyphen_index);
    if(*from == NULL) error_throw(ERROR_MEMORY_ALLOC, "file_line_parse:from");

    line += hyphen_index + 1;
    int comma_index = mx_get_char_index(line, ',');
    if(comma_index <= 0) return false;

    *to = mx_strndup(line, comma_index);
    if(*to == NULL) error_throw(ERROR_MEMORY_ALLOC, "file_line_parse:to");

    line += comma_index + 1;
    *length = mx_strdup(line);
    if(*length == NULL) error_throw(ERROR_MEMORY_ALLOC, "file_line_parse:length");
    if(mx_strlen(*length) == 0) return false;

    return true;
}

bool file_line_validate(char **from, char **to, char **length) {
    for(int i = 0; i < mx_strlen(*from); i++) {
        if(!(mx_isalpha(from[0][i]) || mx_isdigit(from[0][i]))) return false;
    }

    for(int i = 0; i < mx_strlen(*to); i++) {
        if(!(mx_isalpha(to[0][i]) || mx_isdigit(to[0][i]))) return false;
    }

    if(!mx_strcmp(*from, *to)) return false;

    for(int i = 0; i < mx_strlen(*length); i++) {
        if( !mx_isdigit(length[0][i]) ) return false;
    }

    return true;
}
