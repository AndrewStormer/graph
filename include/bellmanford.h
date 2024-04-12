#ifndef _bellmanford_h
#define _bellmanford_h

#include "dijkstra.h"


Node * bellmanford(Vertex * vertices, int vertexcount, int source, int * negativeloopcycle);

#endif