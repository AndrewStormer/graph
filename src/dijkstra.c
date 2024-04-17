#include "../include/dijkstra.h"


node_t *relax(node_t *minheap, adjacency_t *adjacency, node_t *u, node_t *v) {
    if (v->key > u->key + adjacency->edge->weight) {
        v->key = u->key + adjacency->edge->weight;
        v->p = u;
    }
    return minheap;
}


node_t *dijkstra(graph_t *g, int source) {
    if (!g || !g->v || g->edge_count < 1 || g->vertex_count < 1)
        return NULL;

    vertex_t *vertices = g->v;
    int vertexcount = g->vertex_count;

    node_t *minheap = malloc(sizeof(node_t)*vertexcount); 
    if (!minheap) 
        return NULL;
    int heapsize = vertexcount;
    for (int i = 0; i < vertexcount; i++) {
        (minheap + i*sizeof(node_t))->key = (i == source-1) ? 0 : INFINITY;
        (minheap + i*sizeof(node_t))->p = NULL;
        (minheap + i*sizeof(node_t))->v = (vertices + i*sizeof(vertex_t));
    }
    build_heap(minheap, vertexcount);

    node_t *u = NULL, *v = NULL;
    adjacency_t *cursor = NULL;
    while (minheap && heapsize > 0) {
        u = extract_min(minheap, &heapsize);
        cursor = u->v->list;
        while (cursor) { 
            v = get_node(minheap, vertexcount, (vertices + (cursor->edge->to-1)*sizeof(vertex_t)));
            if (!v)
                break;
            minheap = relax(minheap, cursor, u, v);
            cursor = cursor->next;
        }
        build_heap(minheap, heapsize);
    }
    for (int i = 1; i < vertexcount; i++) {
        printf("Shortest path weight from %d to %d is %f\n", source, (minheap + (vertexcount-i-1)*sizeof(node_t))->v->number, (minheap + (vertexcount-i-1)*sizeof(node_t))->key);
    }

    return minheap;
}