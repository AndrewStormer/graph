#ifndef _bellmanford_h
#define _bellmanford_h

#include "dijkstra.h"


node_t *bellmanford(graph_t *g, int source, int *negativeloopcycle);

#endif