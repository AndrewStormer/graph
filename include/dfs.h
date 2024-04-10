#include "graph.h"


typedef struct dfsnstruct {
    Vertex * v;
    struct dfsnstruct * p;
} DFSNode;


DFSNode * DFS(Vertex * vertices, int vertexcount);