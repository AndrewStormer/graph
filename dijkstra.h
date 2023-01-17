#include "mst.h"

Node * relax(Node * minheap, Adjacency * adjacency, Node * u, Node * v);
Node * dijkstra(Vertex * vertices, int vertexcount, int source);