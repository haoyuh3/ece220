#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mp5.h"
#include "mp10.h"

#define MY_INFINITY   1000000000
//initialize the heap
extern void initial_h(heap_t*h);
extern int32_t popheap(graph_t* g,heap_t* h);
//addheap is used to add the neighbor which have smaller src and add them into heap  and it will obey the heap structure which will have smallest
//number at the top
extern void addheap(graph_t* g,heap_t* h, int id);
//swap two element in the heap
extern void swap(graph_t* g, heap_t* h, int child, int parent);
//pop the top of the heap 
//is used to loop all the neighbours
extern void update(graph_t* g, heap_t* h,int heapid);

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
    
    if(4*nnum+1>=num_node){  //there is no subtree
       if(in_range(loc,x1,yleft)){ //the position is (x1, y_left)
        vs->count=vs->count+1;
            if (vs->count >= vs->id_array_size){ //if exceed array size
                vs->id_array_size *= 2;
                int32_t* t = (int32_t *)realloc(vs->id, vs->id_array_size * sizeof(int32_t));//judge whether it is null
                if (t!= NULL) vs->id = t;
            }
            if (vs->count == 1 || p->node[nnum].id > vs->id[vs->count - 2]){ //judge whether it is the first
                vs->id[vs->count - 1] = p->node[nnum].id;
                return;
            }
            for (int32_t i = 0; i < vs->count - 1; i++){ //this part is used to sort
                if (vs->id[i] > p->node[nnum].id){
                    for (int32_t j = vs->count - 1; j >= i + 1; j--) {
                        vs->id[j] = vs->id[j - 1];
                    }
                    vs->id[i] = p->node[nnum].id;
                    break;
                }
            }
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
    int to_num=g->n_vertices;
    int heapid;
    int next_node;
    int start_point, end_point;
    int distance=MY_INFINITY;
    path->n_vertices=0;
    //we need to find a start point
    h->n_elts=0;
    // initialize the heap
    for(int i=0; i<g->n_vertices;i++){
        h->elt[i]=0;
    }
    for(int i=0; i<src->count;i++){
        for(int j=0;j<dest->count;j++){
            
        //first we have to set all src to infinity
            int signal=0;
             for (int h=0; h<to_num;h++){
                g->vertex[h].from_src=MY_INFINITY;
            }
            initial_h(h); // use initial_h to initial the previous heap
            int32_t num=1;
            int id_pred;
            start_point=src->id[i], end_point=dest->id[j];
            h->elt[0]=start_point; //start store the node at h[0]
            g->vertex[start_point].heap_id=0, g->vertex[start_point].from_src=0;
            g->vertex[start_point].pred=start_point;
            heapid=start_point;
            // update->pop out ->update  if heap is empty or it can pop end point
            while(h->n_elts!=0 || signal==0){
                signal=1;
                update(g,h,heapid); 
                next_node=popheap(g,h);//pop point is always shortest point besides it is a node which need to explore its neighbor
                heapid=next_node; //locate the heapid and get its neghbor once we pop sth we have to find its neghbor
                if(heapid==end_point){break;}    // if the top is end_point we have shortest
            }
            if(heapid!=end_point){continue;} // can not find shortest
            id_pred=heapid;
            
            int short_path;
            short_path=g->vertex[heapid].from_src;
            if(distance>short_path){ //we need to find the shortest path
                while(id_pred!=start_point){
                num++; //the num of vertex
                id_pred=g->vertex[id_pred].pred;
            }
                distance=short_path; //used to store the short path in one loop
                path->n_vertices=num;
                path->tot_dist=distance;
                path->id = (int32_t *)calloc(num, sizeof(int32_t));//initialize to 0
                if(path->id==NULL){return 0;}
                for(int k=num-1; k>=0;k--){ //change the id
                    path->id[k]=heapid;
                    heapid=g->vertex[heapid].pred;
                }
               
                
            }   
            
        }
    }
    if (path->n_vertices>0){return 1;} 
    return 0;
}
// we need to find every neghbor in the current node and we should add every neighbor to the heap
//  in the update function we should update from_src distance  and pred id
//num of heap is the last space

//1. update when we pop one element we will set it a main node and we should check the neghbor of the main node
// and add them to the heap (condition: we add heap when the src distance become smaller)
void update(graph_t* g, heap_t* h,int heapid){ // heapid is the id of the current heap node index in graph and we check its neighbor (it should be the heap we just pop out)
  //id_new is the neighbor id
  int id,id_new; 
  int* neighbor;
  int* distance_array;
  // distance indicate distance from current node while rs is from source
  int distance; 
  int num_neighbours;
  id=heapid;
  // id is the current id
  int pre_rs=g->vertex[id].from_src;
  //int pre_heapid=g->vertex[id].pred;
  num_neighbours=g->vertex[id].n_neighbors;
  distance_array=g->vertex[id].distance;
  neighbor=g->vertex[id].neighbor; //neighbour is the array of neighbor indices
  for(int i=0;i<num_neighbours;i++){
    id_new=neighbor[i]; // neighbor id
    distance= distance_array[i]; 
    if(distance+pre_rs<g->vertex[id_new].from_src){
        addheap(g, h, id_new); //add every neighbor to heap
        g->vertex[id_new].pred=id; // update the pre id
        g->vertex[id_new].from_src=distance+pre_rs; //update the from_src if it become smaller
    } 
   }
}
// id is the node id 
//heap at most have 2 subtree we can locate its leaves or tree by divide 2 
void addheap(graph_t* g, heap_t* h, int id){
  
  int num;
  int distance,distance_parent;
  h->n_elts++;  // have one more space
  num=h->n_elts;
  h->elt[num]=id;   //heap store the node id 
  g->vertex[id].heap_id=num; // initilaize to the last place 
  distance=g->vertex[id].from_src; // get distance
  int parent;
  if(num%2==0){
    parent=num/2;
  }else{
    parent=(num-1)/2;  // get parent place
  }
  while (num>0)
  {
    distance_parent=g->vertex[h->elt[parent]].from_src; // compare with parent
    if(distance<distance_parent){ // if distance
        swap(g,h,num,parent); 
        num=parent;
        if(num%2==0){
            parent=num/2;
        }else{
        parent=(num-1)/2;  // get parent place
        }
    }else{
        break;
    }
  } 
}
// this part will help to get next main node
//output is the next node which have least from_rc and pred is the previousnode

// 2. pop we get the top element and the bottom element move to the top
int32_t popheap(graph_t* g, heap_t* h){
    int next_node=h->elt[1];
    int num=1; // head
    int num_heap=h->n_elts;
    h->elt[1]=h->elt[num_heap];
    h->n_elts--;
    int id=h->elt[1];
    int src=g->vertex[id].from_src;
    int src_1,src_2;
    
    while (2*num<=h->n_elts){     // indicate that there are child
        if (2*num+1<=h->n_elts){ //indicate  second child
            src_1=g->vertex[h->elt[2*num]].from_src, src_2=g->vertex[h->elt[2*num+1]].from_src;
            // printf("%d %d",src_1,src_2);
            // printf("\n");
            if(src<=src_1 && src<=src_2){ //smaller tahn child
                break;
            }else{
                if(src_1>src_2){
                    swap(g,h,num,2*num+1);
                    num=2*num+1;
                }
                if(src_1<=src_2){
                    swap(g,h,num,2*num);
                    num=2*num;
                } 
            }
        }
        if (2*num+1>h->n_elts){//indicate there isonly one child
            src_1=g->vertex[h->elt[2*num]].from_src;
            if(src>src_1){// larger than child
                swap(g,h,num,2*num);
                num=2*num;
            }else{
                break;
            }
        }    
    }
    
    return next_node;
}
// should swap heap location and change heap id  (heap id)
void swap(graph_t* g, heap_t* h, int child, int parent){ 
    int t; 
    t=h->elt[child], h->elt[child]= h->elt[parent],h->elt[parent]=t; 
    g->vertex[h->elt[parent]].heap_id=parent, g->vertex[h->elt[child]].heap_id=child;
}
void initial_h(heap_t*h){
    int n=h->n_elts;
    for(int i=0;i<=n;i++){
        h->elt[i]=0;
    }
    h->n_elts=0;

}

