#ifndef _dijkstra_h
#define _dijkstra_h

#include "mst.h"

node_t *relax(node_t *minheap, adjacency_t *adjacency, node_t *u, node_t *v);
node_t *dijkstra(graph_t *g, int source);

#endif