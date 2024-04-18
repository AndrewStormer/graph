#ifndef _bfs_h
#define _bfs_h

#include "graph.h"


//dfs tree
typedef struct bfsnstruct {
    int d, color;
    vertex_t *v;
    struct bfsnstruct *p;
} bfsnode_t;


typedef struct qnstruct {
    bfsnode_t *v;
    struct qnstruct *next;
} qnode_t;


bfsnode_t *bfs(graph_t *g, int startnumber);


#endif