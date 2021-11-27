// app.c

#include "pathfinder.h"

t_app *app_init() {
    t_app *app = malloc(sizeof(t_app));
    if(app == NULL) error_throw(ERROR_MEMORY_ALLOC, "app_init");

    app->file_path = NULL;
    app->vertices = NULL;
    app->edges = NULL;
    app->paths = NULL;

    return app;
}

void app_free(t_app *app) {
    if(app == NULL) error_throw(ERROR_SEG_FAULT, "app_free");

    if(app->file_text != NULL) {
        free(app->file_text);
        app->file_text = NULL;
    }
    if(app->vertices != NULL) {
        for (int i = 0; i < app->vertices_count; i++) {
            mx_strdel(&app->vertices[i]);
        }
        app->vertices = NULL;
    }
    if(app->edges != NULL) {
        free(app->edges);
        app->edges = NULL;
    }
    if(app->paths != NULL) {
        t_list *node = app->paths;
        while (node != NULL) {
            free(((t_path *)node->data)->vertices);
            free(((t_path *)node->data)->lengths);

            t_list *n = node->next;
            free((t_path *)node->data);
            free(node);
            node = n;
        }
        app->paths = NULL;
    }

    free(app);
    app = NULL;
}
