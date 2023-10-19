#include <stdint.h>
#include <stdlib.h>

#include "mp10.h"


vertex_set_t*
new_vertex_set ()
{
    vertex_set_t* res = (vertex_set_t *)malloc(sizeof(*res));
    if (res == NULL) return NULL;
    res->count = 0;
    res->minimap = 0;
    res->id_array_size = 1;
    res->id = (int32_t *)malloc(res->id_array_size * sizeof(*res->id));
    if (res->id == NULL) return NULL;
    return res;
}


void
free_vertex_set (vertex_set_t* vs)
{
    if (vs->id != NULL) free(vs->id);
    if (vs != NULL) free(vs);
}


path_t*
new_path ()
{
    path_t* res = (path_t *)malloc(sizeof(*res));
    if (res == NULL) return NULL;
    res->n_vertices = 0;
    res->minimap = 0;
    res->id = (int32_t *)malloc(sizeof(*res->id));
    if (res->id == NULL) return NULL;
    return res;
}


void
free_path (path_t* path)
{
    if (path->id != NULL) free(path->id);
    if (path != NULL) free(path);
}