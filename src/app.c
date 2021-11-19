// app.c

#include "pathfinder.h"

t_app *app_init() {
    t_app *app = malloc(sizeof(t_app));
    if(app == NULL) error_throw(ERROR_MEMORY_ALLOC, "");

    app->file_path = NULL;
    app->vertices = NULL;
    app->edges = NULL;
    app->paths = NULL;

    return app;
}

void app_free(t_app *app) {
    if(app == NULL) error_throw(ERROR_SEGMENTATION_FAULT, "");

    if(app->file_path != NULL) {
        free(app->file_path);
        app->file_path = NULL;
    }
    if(app->vertices != NULL) {
        free(app->vertices);
        app->vertices = NULL;
    }
    if(app->edges != NULL) {
        free(app->edges);
        app->edges = NULL;
    }
    if(app->paths != NULL) {
        free(app->paths);
        app->paths = NULL;
    }

    free(app);
    app = NULL;
}
