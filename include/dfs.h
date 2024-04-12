#ifndef _dfs_h
#define _dfs_h

#include "graph.h"


typedef struct dfsnstruct {
    vertex_t *v;
    struct dfsnstruct *p;
} dfsnode_t;


dfsnode_t *DFS(graph_t *g);

#endif