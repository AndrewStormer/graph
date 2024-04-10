#ifndef _mst_h
#define _mst_h
#include "graph.h"

//Tree
typedef struct nstruct {
    float key;
    Vertex * v;
    struct nstruct * p;
} Node;


void nodeSwap(Node * node1, Node * node2);
void heapify(Node * minHeap, int index, int size);
void buildHeap(Node * minHeap, int size);
Node * extractMin(Node * minHeap, int * heapSize);
Node * setAllAdjacentVertices(Node * minHeap, Node * currentVertex, int heapSize, Vertex * vertices, int countVertices);
Node * getNode(Node * minHeap, int heapSize, Vertex * adjVertex);

void MST_Prim(Vertex * vertices, int startnumber, int countvertices);
#endif
