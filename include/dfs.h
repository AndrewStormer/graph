#ifndef _dfs_h
#define _dfs_h

#include "graph.h"


typedef struct dfsnstruct {
    Vertex * v;
    struct dfsnstruct * p;
} DFSNode;


DFSNode * DFS(Vertex * vertices, int vertexcount);

#endif