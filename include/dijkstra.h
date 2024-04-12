#ifndef _dijkstra_h
#define _dijkstra_h

#include "mst.h"

Node * relax(Node * minheap, Adjacency * adjacency, Node * u, Node * v);
Node * dijkstra(Vertex * vertices, int vertexcount, int source);

#endif