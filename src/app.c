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

    // if(app->file_path != NULL) {
    //     free(app->file_path);
    //     app->file_path = NULL;
    // }
    if(app->vertices != NULL) {
    //    mx_del_strarr(&app->vertices); !!!
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
