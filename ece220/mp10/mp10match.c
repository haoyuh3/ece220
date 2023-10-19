#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mp5.h"
#include "mp10.h"


//
// These variables hold the heads of two singly-linked lists of 
// requests.  
//
// The avaialble list consists of unpaired requests: partner 
// should be NULL, and next is used to form the list.   
// 
// The shared list consists of groups with non-empty start and end 
// vertex intersections.  Only one of the requests in the group is in 
// the list.  The others are linked through the first's partner field 
// and then through the next field of the others in the group.  The 
// next field of the first request in a group is used to form the
// shared list.
//
// Note: for MP2, you should only build groups of two in the shared
// list.
//

static request_t* available = NULL;
static request_t* shared = NULL;


int32_t
handle_request (graph_t* g, pyr_tree_t* p, heap_t* h, request_t* r)
{
    r->src_vs = new_vertex_set();
    r->dst_vs = new_vertex_set();
    r->path = new_path();
    if (r->src_vs == NULL || r->dst_vs == NULL || r->path == NULL){
        free_vertex_set(r->src_vs);
        free_vertex_set(r->dst_vs);
        free_path(r->path);
        return 0;
    }
    find_nodes(&r->from, r->src_vs, p, 0);
    find_nodes(&r->to, r->dst_vs, p, 0);
    if (r->src_vs->count == 0 || r->dst_vs->count == 0){
        free_vertex_set(r->src_vs);
        free_vertex_set(r->dst_vs);
        free_path(r->path);
        return 0;
    }
    mark_vertex_minimap(g, p);
    build_vertex_set_minimap(g, r->src_vs);
    build_vertex_set_minimap(g, r->dst_vs);
    request_t* now = available;
    request_t* prev = NULL;
    int32_t match_ok = 0;
    while (now != NULL){
        if (((now->src_vs->minimap & r->src_vs->minimap) == 0) || ((now->dst_vs->minimap & r->dst_vs->minimap) == 0)){
            prev = now;
            now = now->next;
            continue;
        }
        vertex_set_t* vs1 = new_vertex_set();
        vertex_set_t* vs2 = new_vertex_set();
        path_t* p = new_path();
        int32_t msize1 = now->src_vs->count < r->src_vs->count ? now->src_vs->count : r->src_vs->count;
        int32_t msize2 = now->dst_vs->count < r->dst_vs->count ? now->dst_vs->count : r->dst_vs->count;
        vs1->id = (int32_t *)malloc(msize1 * sizeof(*vs1->id));
        vs2->id = (int32_t *)malloc(msize2 * sizeof(*vs1->id));
        if (merge_vertex_sets(now->src_vs, r->src_vs, vs1) == 0 || merge_vertex_sets(now->dst_vs, r->dst_vs, vs2) == 0){
            prev = now;
            now = now->next;
            continue;
        }
        build_vertex_set_minimap(g, vs1);
        build_vertex_set_minimap(g, vs2);
        match_ok |= dijkstra(g, h, vs1, vs2, p);
        if (match_ok){
            prev->next = now->next;

            r->next = shared;
            shared = r;

            r->partner = now;
            now->next = now->partner = NULL;

            free_vertex_set(now->src_vs);
            free_vertex_set(r->src_vs);
            free_vertex_set(now->dst_vs);
            free_vertex_set(r->dst_vs);
            free_path(now->path);
            free_path(r->path);

            build_path_minimap(g, p);
            now->src_vs = r->src_vs = vs1;
            now->dst_vs = r->dst_vs = vs2;
            now->path = r->path = p;
            break;
        }
        prev = now;
        now = now->next;
        free_vertex_set(vs1);
        free_vertex_set(vs2);
        free_path(p);
    }
    if (match_ok == 0){
        r->next = available;
        available = r;
    }
    return 1;
}


void
print_results ()
{
    request_t* r;
    request_t* prt;

    printf ("Matched requests:\n");
    for (r = shared; NULL != r; r = r->next) {
        printf ("%5d", r->uid);
	for (prt = r->partner; NULL != prt; prt = prt->next) {
	    printf (" %5d", prt->uid);
	}
	printf (" src=%016llX dst=%016llX path=%016llX\n", r->src_vs->minimap,
		r->dst_vs->minimap, r->path->minimap);
    }

    printf ("\nUnmatched requests:\n");
    for (r = available; NULL != r; r = r->next) {
        printf ("%5d src=%016llX dst=%016llX\n", r->uid, r->src_vs->minimap,
		r->dst_vs->minimap);
    }
}


int32_t
show_results_for (graph_t* g, int32_t which)
{
    request_t* r;
    request_t* prt;

    // Can only illustrate one partner.
    for (r = shared; NULL != r; r = r->next) {
	if (which == r->uid) {
	    return show_find_results (g, r, r->partner);
	}
	for (prt = r->partner; NULL != prt; prt = prt->next) {
	    if (which == prt->uid) {
		return show_find_results (g, prt, r);
	    }
	}
    }

    for (r = available; NULL != r; r = r->next) {
        if (which == r->uid) {
	    return show_find_results (g, r, r);
	}
    }
    return 0;
}


static void
free_request (request_t* r)
{
    free_vertex_set (r->src_vs);
    free_vertex_set (r->dst_vs);
    if (NULL != r->path) {
	free_path (r->path);
    }
    free (r);
}

void
free_all_data ()
{
    request_t* r;
    request_t* prt;
    request_t* next;

    // All requests in a group share source and destination vertex sets
    // as well as a path, so we need free those elements only once.
    for (r = shared; NULL != r; r = next) {
	for (prt = r->partner; NULL != prt; prt = next) {
	    next = prt->next;
	    free (prt);
	}
	next = r->next;
	free_request (r);
    }

    for (r = available; NULL != r; r = next) {
	next = r->next;
	free_request (r);
    }
}


