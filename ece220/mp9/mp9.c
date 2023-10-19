#include <stdint.h>
#include <stdio.h>

#include "mp5.h"
#include "mp9.h"

#define MY_INFINITY   1000000000
//initialize the heap
extern void initial_h(heap_t*h);
extern void popheap(graph_t* g,heap_t* h);
//addheap is used to add the neighbor which have smaller src and add them into heap  and it will obey the heap structure which will have smallest
//number at the top
//extern void addheap(graph_t* g,heap_t* h, int id);
//swap two element in the heap
extern void swap(graph_t* g, heap_t* h, int child, int parent);
//pop the top of the heap 
//is used to loop all the neighbours
extern void update(graph_t* g, heap_t* h,int heapid,int value);

void
find_nodes (locale_t* loc, vertex_set_t* vs, pyr_tree_t* p, int32_t nnum)
{   
    // Do not modify the following line nor add anything above in the function.
    record_fn_call ();
    int loc_x,loc_y,radius;
    loc_x=loc->x, loc_y=loc->y,radius=loc->range;
    int x1,yleft,yright,id_find;
    int num_node;
    num_node=p->n_nodes;
    x1=p->node[nnum].x;
    yleft=p->node[nnum].y_left;
    yright=p->node[nnum].y_right;
    id_find=p->node[nnum].id;
    int *va_list;
    vs->id=va_list;
    
    if(4*nnum+1>=num_node){  //there is no subtree
       if(in_range(loc,x1,yleft)){ //the position is (x1, y_left)
    //     vs->id[vs->count]=id_find; //store the id
        vs->count++; //add one count 
    //     if (vs->count >=MAX_IN_VERTEX_SET){return;}
       }
    }else{  // we have to judge the quadrants
        //if(4*nnum+1<=num_node){ // 4n+1 have child   always true
        if(loc_x-radius<=x1 && loc_y-radius<=yleft){ // indicate it will reach 4n+1
            find_nodes(loc,vs,p,4*nnum+1);
        }
        if (4*nnum+2<num_node){ //4n+2 have child
            if(loc_x+radius>=x1 && loc_y-radius<=yright){
                find_nodes(loc,vs,p,4*nnum+2);
            }
        }
        if (4*nnum+3<num_node){ //4n+3 have child
            if(loc_x-radius<=x1 && loc_y+radius>=yleft){
                find_nodes(loc,vs,p,4*nnum+3);
            }
        }
        if (4*nnum+4<num_node){
            if(loc_x+radius>=x1 && loc_y+radius>=yright){
                find_nodes(loc,vs,p,4*nnum+4);
            }
        }
    }
}
void
trim_nodes (graph_t* g, vertex_set_t* vs, locale_t* loc)
{   
    int id;
    int num_vs; 
    num_vs=vs->count;
    int x, y;
    for (int h=0;h<num_vs;h++){ //loop all the vs and get graph id and x y
        id=vs->id[h];
        x=g->vertex[id].x;
        y=g->vertex[id].y;
        if (in_range(loc, x, y)!=1){ // if it is not in range
            num_vs--; //already minus 1
            vs->count=num_vs;
            for (int k=h;k<num_vs;k++){ //at this time num_vs has minus one and it will not overflow
                vs->id[k]=vs->id[k+1];  // delete the id
            }   
            h--; 
        }
    }
} 
// the alogorithm can be divided into three differnet parts 1.update 2. scan 3.add
//1. update: loop all the neighbor and update its frpm_src adn pred (we can ignore whether we visit because heap can help to find min
// the condition: we only add the heap when the src is smaller than its original
//2 scan use small root heap to pop out small distance  the pop id is the main node(we can signal graph id when when we pop out some node)
// when we meet same id again we should check its neghbor again because we may find another shour path
//important pred is used as signal ( if pred is not main node then ignore it)
// 3 add :use pop out to pop the min value in the heap

// I set start at h[0] which is not the head while h[1] is the head
//   1  ->h[1]
//  / \->
// 2   3
//function :
int32_t
dijkstra (graph_t* g, heap_t* h, vertex_set_t* src, vertex_set_t* dest,
          path_t* path)
{   
    path->n_vertices = 0;
    int32_t length = g->n_vertices + 10;
    int32_t g_type[length];
    int end_point = dest->id[0]; 
    h->n_elts = g->n_vertices;
    for (int32_t i = 0; i < g->n_vertices; i++){
        g->vertex[i].from_src = MY_INFINITY;
        g->vertex[i].heap_id = i;
        h->elt[i] =i;
    }

    for (int32_t i = 0; i < src->count; i++){
        update(g, h, src->id[i], 0);
    } 
    
    for (int32_t i = 0; i < length; i++) g_type[i] = 0;
    for (int32_t i = 0; i < dest->count; i++) g_type[dest->id[i]] = 1;
    for (int32_t i = 0; i < src->count; i++) g_type[src->id[i]] = 0;
  

    while (h->n_elts != 0){
        int st = h->elt[0];
        popheap(g, h);
        if (g_type[st] == 1){
            end_point = st;
            break;
        }
        for (int32_t i = 0; i < g->vertex[st].n_neighbors; i++){
            int32_t x = g->vertex[st].neighbor[i], w = g->vertex[st].distance[i];
            if (g->vertex[x].from_src > g->vertex[st].from_src + w){
                update(g, h, x, g->vertex[st].from_src + w);
                g->vertex[x].pred = st;
            }
        }
    }
    if (g->vertex[end_point].from_src == MY_INFINITY) return 0;
    
    path->tot_dist = g->vertex[end_point].from_src;
    while (g_type[end_point] != 0){
        path->id[path->n_vertices++] = end_point;
        end_point = g->vertex[end_point].pred;
    }
    path->id[path->n_vertices++] = end_point;
    
    return 1;
}
// we need to find every neghbor in the current node and we should add every neighbor to the heap
//  in the update function we should update from_src distance  and pred id
//num of heap is the last space

//1. update when we pop one element we will set it a main node and we should check the neghbor of the main node
// and add them to the heap (condition: we add heap when the src distance become smaller)
void update(graph_t* g, heap_t* h,int id, int distance){ // heapid is the id of the current heap node index in graph and we check its neighbor (it should be the heap we just pop out)
  //id_new is the neighbor id
  int id_now = g->vertex[id].heap_id;
  g->vertex[id].from_src=distance;
  while (id_now > 0 && g->vertex[h->elt[id_now]].from_src < g->vertex[h->elt[(id_now - 1) / 2]].from_src){
        swap(g, h, id_now, (id_now - 1) / 2);
        id_now = (id_now - 1) / 2;
    }
    while (2 * id_now + 1 < h->n_elts){
        if (2 * id_now + 2 >= h->n_elts){
            if (g->vertex[h->elt[id_now]].from_src > g->vertex[h->elt[2 * id_now + 1]].from_src){
                swap(g, h, id_now, 2 * id_now + 1);
                id_now = 2 * id_now + 1;
            }
            else break;
        }
        else{
            if (g->vertex[h->elt[id_now]].from_src > g->vertex[h->elt[2 * id_now + 1]].from_src|| g->vertex[h->elt[id_now]].from_src > g->vertex[h->elt[2 * id_now + 2]].from_src){
                if (g->vertex[h->elt[2 * id_now + 1]].from_src < g->vertex[h->elt[2 * id_now + 2]].from_src){
                    swap(g, h, id_now, 2 * id_now + 1);
                    id_now = 2 * id_now + 1;
                }else{
                    swap(g, h, id_now, 2 * id_now + 2);
                    id_now = 2 * id_now + 2;
                }
            }
            else {break;}
        }
    }
}
// id is the node id 
//heap at most have 2 subtree we can locate its leaves or tree by divide 2 
// this part will help to get next main node
//output is the next node which have least from_rc and pred is the previousnode

// 2. pop we get the top element and the bottom element move to the top
void popheap(graph_t* g, heap_t* h){
   swap(g, h, 0, --h->n_elts);
    h->elt[h->n_elts] = 0;
    int32_t start = 0;
    while (2*start + 1 < h->n_elts){
        if (2*start + 2 >= h->n_elts){
            if (g->vertex[h->elt[start]].from_src > g->vertex[h->elt[2*start+1]].from_src){
                swap(g, h, start, 2*start + 1);
                start = 2*start + 1;
            }
            else break;
        }
        else{
            if (g->vertex[h->elt[start]].from_src > g->vertex[h->elt[2*start+1]].from_src|| g->vertex[h->elt[start]].from_src > g->vertex[h->elt[2*start+2]].from_src){
                if (g->vertex[h->elt[2*start+1]].from_src < g->vertex[h->elt[2*start+2]].from_src){
                    swap(g, h, start, 2*start+1);
                    start= 2*start+ 1;
                }
                else{
                    swap(g, h, start, 2 * start + 2);
                    start = 2 * start + 2;
                }
            }
            else {break;}
        }
    }
}
// should swap heap location and change heap id  (heap id)
void swap(graph_t* g, heap_t* h, int child, int parent){ 
    int t; 
    t=h->elt[child], h->elt[child]= h->elt[parent],h->elt[parent]=t; 
    g->vertex[h->elt[parent]].heap_id=parent, g->vertex[h->elt[child]].heap_id=child;
}


