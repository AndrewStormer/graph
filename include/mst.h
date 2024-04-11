#ifndef _mst_h
#define _mst_h
#include "graph.h"

//Tree
typedef struct nstruct {
    float key;
    Vertex *v;
    struct nstruct *p;
} Node;


void node_swap(Node *node1, Node *node2);
void heapify(Node *minHeap, int index, int size);
void build_heap(Node *minHeap, int size);
Node *extract_min(Node *minHeap, int *heapSize);
Node *set_all_adjacent_vertices(Node *minHeap, Node *currentVertex, int heapSize, Vertex *vertices, int countVertices);
Node *get_node(Node *minHeap, int heapSize, Vertex *adjVertex);

void MST_Prim(Vertex *vertices, int startnumber, int countvertices);
#endif
