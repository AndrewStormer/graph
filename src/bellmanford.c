#include "../include/bellmanford.h"


node_t *bellmanford(graph_t *g, int source, int *negativeloopcycle) {   
    if (!g || !g->v || g->edge_count < 1 || g->vertex_count < 1 || !negativeloopcycle)
        return NULL;
    vertex_t *vertices = g->v;
    int vertexcount = g->vertex_count;

    node_t *shortestpath = malloc(sizeof(node_t)*vertexcount);
    for (int i = 0; i < vertexcount; i++) {
        (shortestpath + i*sizeof(node_t))->key = (i == source-1) ? 0 : INFINITY;
        (shortestpath + i*sizeof(node_t))->p = NULL;
        (shortestpath + i*sizeof(node_t))->v = (vertices + i*sizeof(vertex_t));
    }

    adjacency_t *cursor = NULL;
    for (int i = 0; i < vertexcount; i++) {
        cursor = (vertices + i*sizeof(vertex_t))->list;
        while (cursor) {
            relax(shortestpath, cursor, (shortestpath + (cursor->edge->from-1)*sizeof(node_t)), (shortestpath + (cursor->edge->to-1)*sizeof(node_t)));
            cursor = cursor->next;
        }
    }
    cursor = NULL;
    node_t *u = NULL, *v = NULL;
    for (int i = 0; i < vertexcount; i++) {
        cursor = (vertices + i*sizeof(vertex_t))->list;
        while (cursor) {
            u = get_node(shortestpath, vertexcount, (vertices + (cursor->edge->from-1)*sizeof(vertex_t)));
            v = get_node(shortestpath, vertexcount, (vertices + (cursor->edge->to-1)*sizeof(vertex_t)));
            if (v->key > u->key + cursor->edge->weight || cursor->edge->weight < 0) {
                *negativeloopcycle = 0;
            }
            cursor = cursor->next;
        }
    }
    if (*negativeloopcycle) {
        for (int i = 1; i < vertexcount; i++) {
            printf("Shortest path weight from %d to %d is %f\n", source, (shortestpath + i*sizeof(node_t))->v->number, (shortestpath + i*sizeof(node_t))->key);
        }
    } else 
        printf("Negative weight cycle detected\n");
    return shortestpath;
}