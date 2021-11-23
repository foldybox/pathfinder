// paths.c

#include "pathfinder.h"

void paths_find(t_app *app) {
    int *vertices_weights = NULL;
    int *vertices_prev = NULL;
    bool *vertices_visited = NULL;

    // allocate memory for local arrays
    vertices_weights = malloc(app->vertices_count * sizeof(int));
    vertices_prev = malloc(app->vertices_count * sizeof(int));
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
            vertices_prev[i] = -1;
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
                        vertices_prev[app->edges[i].to] = active_vertice;
                    }
                }
                else if(active_vertice == app->edges[i].to) {
                    if(new_weight < vertices_weights[app->edges[i].from]) {
                        vertices_weights[app->edges[i].from] = new_weight;
                        vertices_prev[app->edges[i].from] = active_vertice;
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

        // add new path into global array
        for(int i = 0; i < app->vertices_count; i++) {
            t_path *path = malloc(sizeof(t_path));
            path->from = global_active_vertice;
            path->to = i;
            path->length = 0;
            path->vertices_count = 0;
            
            if(path->from == path->to) continue;

            // set ul path variables
            for(int i = path->to; i >= 0; i = vertices_prev[i]) {
                path->vertices_count++;
            }
            path->lengths_count = path->vertices_count - 1;
            path->vertices_count -= 2;

            // allocate mamory for path arrays
            path->vertices = malloc(path->vertices_count * sizeof(int));
            path->lengths = malloc(path->lengths_count * sizeof(int));

            // fill path middle vertices array
            for(int i = path->to, j = path->vertices_count; i >= 0 && j >= 0; i = vertices_prev[i], j--) {
                if(j == path->vertices_count) continue;
                path->vertices[j] = i;
            }

            // fill path length array
            for(int i = path->to, j = path->lengths_count - 1; i >= 0 && j >= 0; i = vertices_prev[i], j--) {
                for(int k = 0; k < app->edges_count; k++) {
                    if((i == app->edges[k].from && vertices_prev[i] == app->edges[k].to) || (vertices_prev[i] == app->edges[k].from && i == app->edges[k].to)) {
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
                    t_path *current = (t_path *)node->data;

                    if((path->from == current->from && path->to == current->to) || (path->to == current->from && path->from == current->to)) {
                        is_exist = true;
                    }
                }

                // if path is not exist in the global array add vertice into it.
                if(!is_exist) mx_push_back(&app->paths, path);
            }
        }
    }

    // free up allocated memory
    free(vertices_weights);
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
