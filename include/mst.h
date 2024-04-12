#ifndef _mst_h
#define _mst_h
#include "graph.h"

typedef struct estruct edge_t;
typedef struct astruct adjacency_t;
typedef struct vstruct vertex_t;

//Tree
typedef struct nstruct {
    float key;
    vertex_t *v;
    struct nstruct *p;
} node_t;


void node_swap(node_t *node1, node_t *node2);
void heapify(node_t *minHeap, int index, int size);
void build_heap(node_t *minHeap, int size);
node_t *extract_min(node_t *minHeap, int *heapSize);
node_t *set_all_adjacent_vertices(node_t *minHeap, node_t *currentVertex, int heapSize, vertex_t *vertices, int countVertices);
node_t *get_node(node_t *minHeap, int heapSize, vertex_t *adjVertex);

node_t *mst_Prim(graph_t *g, int startnumber);
#endif
