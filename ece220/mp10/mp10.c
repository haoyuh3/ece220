#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mp10.h"

int32_t
findminimap(graph_t* g, pyr_tree_t* p, int32_t x, int32_t y, int32_t nnum){
    if (21 <= nnum && nnum <= 84) return nnum - 21;
    if (x <= p->node[nnum].x && y <= p->node[nnum].y_left) return findminimap(g, p, x, y, 4 * nnum + 1);
    if (x <= p->node[nnum].x && y >= p->node[nnum].y_left) return findminimap(g, p, x, y, 4 * nnum + 2);
    if (x >= p->node[nnum].x && y <= p->node[nnum].y_right) return findminimap(g, p, x, y, 4 * nnum + 3);
    if (x >= p->node[nnum].x && y <= p->node[nnum].y_right) return findminimap(g, p, x, y, 4 * nnum + 4);
    return 0;
}

int32_t 
mark_vertex_minimap (graph_t* g, pyr_tree_t* p)
{
    for (int32_t i = 0; i < g->n_vertices; i++){
        if (g->n_vertices <= 64) g->vertex[i].mm_bit = i;
        else g->vertex[i].mm_bit = findminimap(g, p, g->vertex[i].x, g->vertex[i].y, 0);
    }
    return 1;
}


void 
build_vertex_set_minimap (graph_t* g, vertex_set_t* vs)
{
    for (int32_t i = 0; i < vs->count; i++) vs->minimap |= (1ull << g->vertex[vs->id[i]].mm_bit);
}


void 
build_path_minimap (graph_t* g, path_t* p)
{
    for (int32_t i = 0; i < p->n_vertices; i++) p->minimap |= (1ull << g->vertex[p->id[i]].mm_bit);
}


int32_t
merge_vertex_sets (const vertex_set_t* v1, const vertex_set_t* v2,
		   vertex_set_t* vint)
{
    int32_t i = 0, j = 0;
    while (i < v1->count && j < v2->count){
        if (v1->id[i] < v2->id[j]) i++;
        else if (v1->id[i] == v2->id[j]){
            vint->id[vint->count++] = v1->id[i];
            i++; j++;
        }
        else j++;
    }
    if (vint->count == 0) return 0;
    return 1;
}

