#include "../include/dfs.h"


dfsnode_t *initdfsnodes(vertex_t *vertices, int vertexcount) {
    dfsnode_t *tree = malloc(sizeof(dfsnode_t)*vertexcount); if (!tree) return NULL;
    for (int i = 0; i < vertexcount; i++) {
        (tree + i*sizeof(dfsnode_t))->p = NULL;
        (tree + i*sizeof(dfsnode_t))->v = (vertices + i*sizeof(vertex_t));
    }
    return tree;
}


dfsnode_t *DFSvisit(dfsnode_t *tree, int index, int vertexcount,int *time, int color[], int d[], int f[]) {
    dfsnode_t *u = (tree + index*sizeof(dfsnode_t));
    ++*time;
    color[index] = GREY;
    d[index] = *time;
    printf("vertex %d discovered at time %d\n", index+1, *time);

    adjacency_t *cursor = u->v->list;
    while (cursor) {
        if (color[(cursor->edge->to)-1] == WHITE) {
            (tree + ((cursor->edge->from)-1)*sizeof(dfsnode_t))->p = u;
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


dfsnode_t *DFS(graph_t *g) {
    if (!g || !g->v || g->edge_count < 1 || g->vertex_count < 1)
        return NULL;

    vertex_t *vertices = g->v;
    int vertexcount = g->vertex_count;

    dfsnode_t *tree = initdfsnodes(vertices, vertexcount); if (!tree) return NULL;
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