#include <stdint.h>
#include <stdio.h>

#include "mp5.h"
#include "mp9.h"


int32_t
match_requests (graph_t* g, pyr_tree_t* p, heap_t* h,
		request_t* r1, request_t* r2,
		vertex_set_t* src_vs, vertex_set_t* dst_vs, path_t* path)
{   
	src_vs->count=0, dst_vs->count=0;
	find_nodes(&(r1->from),src_vs,p,0);
	trim_nodes(g,src_vs,&(r2->from));
	find_nodes(&(r1->to),dst_vs,p,0);
	trim_nodes(g,dst_vs,&(r2->to));
	
	// for(int i=0; i<src_vs->count;i++){
    //     for(int j=0;j<dst_vs->count;j++){
	// printf("%d %d", src_vs->id[i],dst_vs->id[j]);
    // printf("\n");
	// }
	
	// }
	// return 0;
    //test swap
    // h->elt[0]=1,h->elt[2]=2;
	// swap(g,h,0,2);
    // printf("%d",h->elt[0]);
	// return 0;
	

    //test pop,addheap
	// h->n_elts=3;
	// g->vertex[4].from_src=2;
	// h->elt[1]=1,g->vertex[1].from_src=1;
	// h->elt[2]=2,g->vertex[2].from_src=5,
	// h->elt[3]=3, g->vertex[3].from_src=3;
	// printf(" %d %d %d",h->elt[1], h->elt[2], h->elt[3]);
	// printf("\n");
	// addheap(g,h,4);
	// printf("%d %d %d %d",h->elt[1], h->elt[2], h->elt[3],h->elt[4]);
	// printf("\n");
    // int pop_num;
	// pop_num=popheap(g,h);
	// printf(" %d %d %d", h->elt[1], h->elt[2], h->elt[3]);
	// printf("\n");
	// printf("%d", h->n_elts);
	// pop_num=popheap(g,h);
	// printf("\n");
	// printf(" %d %d %d",pop_num, h->elt[1], h->elt[2]);
    // return 0;
	if(dst_vs->count>0 && src_vs->count>0){
		if (dijkstra ( g, h, src_vs, dst_vs, path)){return 1;}
	}
    return 0;
}
