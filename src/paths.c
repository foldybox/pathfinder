// paths.c

#include "pathfinder.h"

#define MAX_BUF 16

void paths_find(t_app *app) {
    int *vertices_weights = NULL;
    int **vertices_prev = NULL;
    bool *vertices_visited = NULL;

    // allocate memory for local arrays
    vertices_weights = malloc(app->vertices_count * sizeof(int));
    vertices_prev = malloc(app->vertices_count * sizeof(int *));
    for(int i = 0; i < app->vertices_count; i++) {
        vertices_prev[i] = malloc(MAX_BUF * sizeof(int));
    }
    vertices_visited = malloc(app->vertices_count * sizeof(int));

    // main cycle which use Dijkstra's algorithm to each vertice like a root vertice
    for(int global_active_vertice = 0; global_active_vertice < app->vertices_count; global_active_vertice++) {
        int active_vertice = global_active_vertice;
        bool is_all_visited = false;

        // set ul local arrays
        for (int i = 0; i < app->vertices_count; i++) {
            vertices_weights[i] = INT_MAX;
        }
        vertices_weights[active_vertice] = 0;
        for (int i = 0; i < app->vertices_count; i++) {
            mx_memset(vertices_prev[i], -1, MAX_BUF * sizeof(int));
        }
        mx_memset(vertices_visited, 0, app->vertices_count * sizeof(int));

        // Dijkstra's algorithm cycle for each other vertice
        while (!is_all_visited) {
            // check active vertice edges
            for(int i = 0; i < app->edges_count; i++) {
                // continue if vertice is visited
                for(int j = 0; j < app->vertices_count; j++) {
                    if(vertices_visited[j] == app->edges[i].to || vertices_visited[j] == app->edges[i].from) continue;
                }

                // calculate new weight for active vertice 
                int new_weight = vertices_weights[active_vertice] + app->edges[i].length;
                
                // check if this is edge of active vertice
                if(active_vertice == app->edges[i].from) {
                    if(new_weight < vertices_weights[app->edges[i].to]) {
                        vertices_weights[app->edges[i].to] = new_weight;
                        mx_memset(vertices_prev[app->edges[i].to], -1, MAX_BUF * sizeof(int));
                        vertices_prev[app->edges[i].to][0] = active_vertice;
                    }
                    else if(new_weight == vertices_weights[app->edges[i].to]) {
                        for (int j = 0; j < MAX_BUF; j++) {
                            if(vertices_prev[app->edges[i].to][j] == -1) {
                                vertices_prev[app->edges[i].to][j] = active_vertice;
                                break;
                            }
                        }
                    }
                }
                else if(active_vertice == app->edges[i].to) {
                    if(new_weight < vertices_weights[app->edges[i].from]) {
                        vertices_weights[app->edges[i].from] = new_weight;
                        mx_memset(vertices_prev[app->edges[i].from], -1, MAX_BUF * sizeof(int));
                        vertices_prev[app->edges[i].from][0] = active_vertice;
                    }
                    else if(new_weight == vertices_weights[app->edges[i].from]) {
                        for (int j = 0; j < MAX_BUF; j++) {
                            if(vertices_prev[app->edges[i].from][j] == -1) {
                                vertices_prev[app->edges[i].from][j] = active_vertice;
                                break;
                            }
                        }
                    }
                }
            }

            // set active vertice visited
            vertices_visited[active_vertice] = true;

            // set active vertice by choosing minimal weight vertice value
            for(int i = 0; i < app->vertices_count; i++) {
                if(!vertices_visited[i] && i != active_vertice) {
                    active_vertice = i;
                    break;
                }
            }
            for(int i = 0; i < app->vertices_count; i++) {
                if(!vertices_visited[i] && vertices_weights[i] < vertices_weights[active_vertice]) active_vertice = i;
            }

            // check if all vertices were active
            for(int i = 0; i < app->vertices_count; i++) {
                is_all_visited = true;
                if(!vertices_visited[i]) {
                    is_all_visited = false;
                    break;
                }
            }
        }

        int **vertices_prev_table = malloc(app->vertices_count * sizeof(int *));
        for(int i = 0; i < app->vertices_count; i++) {
            vertices_prev_table[i] = malloc(MAX_BUF * sizeof(int));
            mx_memset(vertices_prev_table[i], 0, MAX_BUF);
        }

        int mult = 1;
        for(int i = 0; i < app->vertices_count; i++) {
            if(vertices_prev[i][1] == -1) {
                for (int k = 0; k < MAX_BUF; k++) {
                    vertices_prev_table[i][k] = vertices_prev[i][0];
                }
                continue;
            }
            int count = 0;
            for (int k = 0; k < MAX_BUF; k++) {
                if(vertices_prev[i][k] != -1) count++;
            }
            mult *= count;

            int m = 0;
            for (int k = 0; k < MAX_BUF; k++) {
                vertices_prev_table[i][k] = vertices_prev[i][m];
                m++;
                if(m % mult == 0) m = 0;
            }
        }

        // add new path into global array
        for(int i = 0; i < app->vertices_count; i++) {
            for(int m = mult - 1; m >= 0; m--) {
                if(global_active_vertice == i) break;

                t_path *path = malloc(sizeof(t_path));
                path->from = global_active_vertice;
                path->to = i;
                path->length = 0;
                path->vertices_count = 0;

                // set all path variables
                for(int i = path->to; i >= 0; i = vertices_prev_table[i][m]) {
                    path->vertices_count++;
                }
                path->lengths_count = path->vertices_count - 1;
                path->vertices_count -= 2;

                // allocate mamory for path arrays
                path->vertices = malloc(path->vertices_count * sizeof(int));
                path->lengths = malloc(path->lengths_count * sizeof(int));

                // fill path middle vertices array
                for(int i = path->to, j = path->vertices_count; i >= 0 && j >= 0; i = vertices_prev_table[i][m], j--) {
                    if(j == path->vertices_count) continue;
                    path->vertices[j] = i;
                }

                // fill path length array
                for(int i = path->to, j = path->lengths_count - 1; i >= 0 && j >= 0; i = vertices_prev_table[i][m], j--) {
                    for(int k = 0; k < app->edges_count; k++) {
                        if((i == app->edges[k].from && vertices_prev_table[i][m] == app->edges[k].to) || (vertices_prev_table[i][m] == app->edges[k].from && i == app->edges[k].to)) {
                            path->lengths[j] = app->edges[k].length;
                        }
                    }
                }

                // calculate path full length
                for(int i = 0; i < path->lengths_count; i++) {
                    path->length += path->lengths[i];
                }

                // add new path to global paths array
                if(app->paths == NULL) {
                    app->paths = mx_create_node(path);
                }
                else {
                    // check all global array for existing current path
                    bool is_exist = false;
                    for(t_list *node = app->paths; node != NULL; node = node->next) {
                        t_path *active = (t_path *)node->data;
                        bool is_front = false, is_bottom = false, is_vertices = true, is_empty_vertices = true;

                        if((path->from == active->from && path->to == active->to)) is_front = true;
                        if((path->to == active->from && path->from == active->to)) is_bottom = true;

                        if(path->vertices_count != 0) {
                            is_empty_vertices = false;
                            if(path->vertices_count != active->vertices_count) {
                                for (int i = 0; i < path->vertices_count; i++) {
                                    if(path->vertices[i] != active->vertices[i]) {
                                        is_vertices = false;
                                        break;
                                    }
                                }
                            }
                            else {
                                is_vertices = false;
                            }
                        }

                        if(is_empty_vertices && (is_front || is_bottom)) {
                            is_exist = true;
                            break;
                        }
                        else if(is_vertices && (is_front || is_bottom)) {
                            is_exist = true;
                            break;
                        }
                        else if(is_bottom) {
                            is_exist = true;
                            break;
                        }
                    }

                    // if path is not exist in the global array add vertice into it.
                    if(!is_exist) mx_push_back(&app->paths, path);
                }
            }
        }

        for(int i = 0; i < app->vertices_count; i++) {
            free(vertices_prev_table[i]);
        }
        free(vertices_prev_table);
    }

    // free up allocated memory
    free(vertices_weights);
    for(int i = 0; i < app->vertices_count; i++) {
        free(vertices_prev[i]);
    }
    free(vertices_prev);
    free(vertices_visited);
}

void paths_print(t_app *app) {
    for(t_list *node = app->paths; node != NULL; node = node->next) {
        t_path *path = (t_path *)node->data;

        mx_printstr("========================================\n");

        mx_printstr("Path: ");
        mx_printstr(app->vertices[path->from]);
        mx_printstr(" -> ");
        mx_printstr(app->vertices[path->to]);
        mx_printchar('\n');

        mx_printstr("Route: ");
        mx_printstr(app->vertices[path->from]);
        for(int i = 0; i < path->vertices_count; i++) {
            mx_printstr(" -> ");
            mx_printstr(app->vertices[path->vertices[i]]);
        }
        mx_printstr(" -> ");
        mx_printstr(app->vertices[path->to]);
        mx_printchar('\n');

        mx_printstr("Distance: ");
        if(path->lengths_count > 1) {
            for(int i = 0; i < path->lengths_count; i++) {
                if(i != 0) mx_printstr(" + ");
                mx_printint(path->lengths[i]);
            }
            mx_printstr(" = ");
        }
        mx_printint(path->length);
        mx_printchar('\n');

        mx_printstr("========================================\n");
    }
}
