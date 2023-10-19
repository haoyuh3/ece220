#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mp5.h"
#include "mp10.h"

#define MY_INFINITY   1000000000



void
find_nodes (locale_t* loc, vertex_set_t* vs, pyr_tree_t* p, int32_t nnum)
{
    // Do not modify the following line nor add anything above in the function.
    record_fn_call ();
    if (4 * nnum + 1 >= p->n_nodes){
        if (in_range(loc, p->node[nnum].x, p->node[nnum].y_left)){
            vs->count++;
            if (vs->count >= vs->id_array_size){
                vs->id_array_size *= 2;
                int32_t* temp = (int32_t *)realloc(vs->id, vs->id_array_size * sizeof(int32_t));
                if (temp != NULL) vs->id = temp;
            }
            if (vs->count == 1 || p->node[nnum].id > vs->id[vs->count - 2]){
                vs->id[vs->count - 1] = p->node[nnum].id;
                return;
            }
            for (int32_t i = 0; i < vs->count - 1; i++){
                if (vs->id[i] > p->node[nnum].id){
                    for (int32_t j = vs->count - 1; j >= i + 1; j--) vs->id[j] = vs->id[j - 1];
                    vs->id[i] = p->node[nnum].id;
                    break;
                }
            }
        }
        return;
    }
    else{
        int32_t N, E, S, W;
        N = loc->y - loc->range, E = loc->x + loc->range, S = loc->y + loc->range, W = loc->x - loc->range;
        if (N <= p->node[nnum].y_left && W <= p->node[nnum].x && 4 * nnum + 1 < p->n_nodes) find_nodes(loc, vs, p, 4 * nnum + 1);
        if (N <= p->node[nnum].y_right && E >= p->node[nnum].x && 4 * nnum + 2 < p->n_nodes) find_nodes(loc, vs, p, 4 * nnum + 2);
        if (S >= p->node[nnum].y_left && W <= p->node[nnum].x && 4 * nnum + 3 < p->n_nodes) find_nodes(loc, vs, p, 4 * nnum + 3);
        if (S >= p->node[nnum].y_right && E >= p->node[nnum].x && 4 * nnum + 4 < p->n_nodes) find_nodes(loc, vs, p, 4 * nnum + 4);
    }
}


void
trim_nodes (graph_t* g, vertex_set_t* vs, locale_t* loc)
{
    for (int32_t i = 0; i < vs->count; i++){
        if (in_range(loc, g->vertex[vs->id[i]].x, g->vertex[vs->id[i]].y)) continue;
        for (int32_t j = i; j < vs->count - 1; j++) vs->id[j] = vs->id[j + 1];
        vs->id[--vs->count] = 0;
        i--;
    }
}

void
swap_node(graph_t* g, heap_t* h, int32_t h1, int32_t h2){
    g->vertex[h->elt[h1]].heap_id = h2; g->vertex[h->elt[h2]].heap_id = h1;
    int32_t tmp = h->elt[h1]; h->elt[h1] = h->elt[h2]; h->elt[h2] = tmp;
}

void
update (graph_t* g, heap_t* h, int32_t id, int32_t value)
{
    g->vertex[id].from_src = value;
    int32_t hid = g->vertex[id].heap_id;
    while (hid > 0 && g->vertex[h->elt[hid]].from_src < g->vertex[h->elt[(hid - 1) / 2]].from_src){
        swap_node(g, h, hid, (hid - 1) / 2);
        hid = (hid - 1) / 2;
    }
    while (2 * hid + 1 < h->n_elts){
        if (2 * hid + 2 >= h->n_elts){
            if (g->vertex[h->elt[hid]].from_src > g->vertex[h->elt[2 * hid + 1]].from_src){
                swap_node(g, h, hid, 2 * hid + 1);
                hid = 2 * hid + 1;
            }
            else break;
        }
        else{
            if (g->vertex[h->elt[hid]].from_src > g->vertex[h->elt[2 * hid + 1]].from_src
            || g->vertex[h->elt[hid]].from_src > g->vertex[h->elt[2 * hid + 2]].from_src){
                if (g->vertex[h->elt[2 * hid + 1]].from_src < g->vertex[h->elt[2 * hid + 2]].from_src){
                    swap_node(g, h, hid, 2 * hid + 1);
                    hid = 2 * hid + 1;
                }
                else{
                    swap_node(g, h, hid, 2 * hid + 2);
                    hid = 2 * hid + 2;
                }
            }
            else break;
        }
    }
}

void pop (graph_t* g, heap_t* h){
    swap_node(g, h, 0, --h->n_elts);
    h->elt[h->n_elts] = 0;
    int32_t hid = 0;
    while (2 * hid + 1 < h->n_elts){
        if (2 * hid + 2 >= h->n_elts){
            if (g->vertex[h->elt[hid]].from_src > g->vertex[h->elt[2 * hid + 1]].from_src){
                swap_node(g, h, hid, 2 * hid + 1);
                hid = 2 * hid + 1;
            }
            else break;
        }
        else{
            if (g->vertex[h->elt[hid]].from_src > g->vertex[h->elt[2 * hid + 1]].from_src
            || g->vertex[h->elt[hid]].from_src > g->vertex[h->elt[2 * hid + 2]].from_src){
                if (g->vertex[h->elt[2 * hid + 1]].from_src < g->vertex[h->elt[2 * hid + 2]].from_src){
                    swap_node(g, h, hid, 2 * hid + 1);
                    hid = 2 * hid + 1;
                }
                else{
                    swap_node(g, h, hid, 2 * hid + 2);
                    hid = 2 * hid + 2;
                }
            }
            else break;
        }
    }
}

int32_t
dijkstra (graph_t* g, heap_t* h, vertex_set_t* src, vertex_set_t* dest,
          path_t* path)
{
    h->n_elts = g->n_vertices;
    for (int32_t i = 0; i < g->n_vertices; i++){
        g->vertex[i].from_src = MY_INFINITY;
        g->vertex[i].heap_id = h->elt[i] = i;
    }

    for (int32_t i = 0; i < src->count; i++) update(g, h, src->id[i], 0);
    const int32_t MAXN = g->n_vertices + 10;
    int32_t v_type[MAXN], v = dest->id[0]; 
    for (int32_t i = 0; i < MAXN; i++) v_type[i] = 0;
    for (int32_t i = 0; i < src->count; i++) v_type[src->id[i]] = 1;
    for (int32_t i = 0; i < dest->count; i++){
        if (v_type[dest->id[i]] == 1){
            path->tot_dist = 0;
            path->n_vertices = 1;
            path->id[0] = dest->id[i];
            return 1;
        }
        v_type[dest->id[i]] = 2;
    }

    while (h->n_elts != 0){
        int32_t u = h->elt[0];
        pop(g, h);
        if (v_type[u] == 2){
            v = u;
            break;
        }
        for (int32_t i = 0; i < g->vertex[u].n_neighbors; i++){
            int32_t v = g->vertex[u].neighbor[i], w = g->vertex[u].distance[i];
            if (g->vertex[v].from_src > g->vertex[u].from_src + w){
                update(g, h, v, g->vertex[u].from_src + w);
                g->vertex[v].pred = u;
            }
        }
    }
    if (g->vertex[v].from_src == MY_INFINITY) return 0;

    int32_t cnt = 1, v1 = v;
    while (v_type[v1] != 1){
        cnt++;
        v1 = g->vertex[v1].pred;
    }

    path->id = (int32_t *)malloc(cnt * sizeof(int32_t));
    path->n_vertices = 0; path->tot_dist = g->vertex[v].from_src;

    while (v_type[v] != 1){
        path->id[path->n_vertices++] = v;
        v = g->vertex[v].pred;
    }
    path->id[path->n_vertices++] = v;

    for (int32_t i = 0, j, tmp; i < path->n_vertices / 2; i++){
        j = path->n_vertices - 1 - i;
        tmp = path->id[i]; path->id[i] = path->id[j]; path->id[j] = tmp;
    }
    return 1;
}

