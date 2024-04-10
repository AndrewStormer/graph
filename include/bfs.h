#ifndef _bfs_h
#define _bfs_h
#include "graph.h"


//DFS tree
typedef struct bfsnstruct {
    int d, color;
    Vertex * v;
    struct bfsnstruct * p;
} BFSNode;


typedef struct qnstruct {
    BFSNode * v;
    struct qnstruct * next;
} QNode;


BFSNode * BFS(Vertex * vertices, int vertexcount, int startnumber);


#endif