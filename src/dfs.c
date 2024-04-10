#include "../include/dfs.h"


DFSNode * initdfsnodes(Vertex * vertices, int vertexcount) {
    DFSNode * tree = malloc(sizeof(DFSNode)*vertexcount); if (!tree) return NULL;
    for (int i = 0; i < vertexcount; i++) {
        (tree + i*sizeof(DFSNode))->p = NULL;
        (tree + i*sizeof(DFSNode))->v = (vertices + i*sizeof(Vertex));
    }
    return tree;
}


DFSNode * DFSvisit(DFSNode * tree, int index, int vertexcount,int * time, int color[], int d[], int f[]) {
    DFSNode * u = (tree + index*sizeof(DFSNode));
    ++*time;
    color[index] = GREY;
    d[index] = *time;
    printf("vertex %d discovered at time %d\n", index+1, *time);

    Adjacency * cursor = u->v->list;
    while (cursor) {
        if (color[(cursor->edge->to)-1] == WHITE) {
            (tree + ((cursor->edge->from)-1)*sizeof(DFSNode))->p = u;
            DFSvisit(tree, cursor->edge->to-1, vertexcount, time, color, d, f);
        }
        cursor = cursor->next;
    }
    ++*time;
    color[index] = BLACK;
    f[index] = *time;
    printf("vertex %d finished at time %d\n", u->v->number, *time);

    return tree;
}


DFSNode * DFS(Vertex * vertices, int vertexcount) {
    printf("DFS Start\n");
    DFSNode * tree = initdfsnodes(vertices, vertexcount); if (!tree) return NULL;
    int color[vertexcount]; for (int i = 0; i < vertexcount; i++) color[i] = WHITE;
    int d[vertexcount]; memset(color, 0, vertexcount);
    int f[vertexcount]; memset(color, 0, vertexcount);

    int time = 0;
    for (int i = 0; i < vertexcount; i++) {
        if (color[i] == WHITE) {
            tree = DFSvisit(tree, i, vertexcount, &time, color, d, f);
        }
    }

    return tree;
}