#include "../include/dijkstra.h"


Node * relax(Node * minheap, Adjacency * adjacency, Node * u, Node * v) {
    if (v->key > u->key + adjacency->edge->weight) {
        v->key = u->key + adjacency->edge->weight;
        v->p = u;
    }
    return minheap;
}


Node * dijkstra(Vertex * vertices, int vertexcount, int source) {
    printf("Dijkstra start\n");
    Node * minheap = malloc(sizeof(Node)*vertexcount); if (!minheap) return NULL;
    int heapsize = vertexcount;
    for (int i = 0; i < vertexcount; i++) {
        (minheap + i*sizeof(Node))->key = (i == source-1) ? 0 : INFINITY;
        (minheap + i*sizeof(Node))->p = NULL;
        (minheap + i*sizeof(Node))->v = (vertices + i*sizeof(Vertex));
    }
    buildHeap(minheap, vertexcount);

    Node * u = NULL, * v = NULL;
    Adjacency * cursor = NULL;
    while (minheap && heapsize > 0) {
        u = extractMin(minheap, &heapsize);
        cursor = u->v->list;
        while (cursor) { 
            v = getNode(minheap, vertexcount, (vertices + (cursor->edge->to-1)*sizeof(Vertex)));
            minheap = relax(minheap, cursor, u, v);
            cursor = cursor->next;
        }
        buildHeap(minheap, heapsize);
    }
    for (int i = 1; i < vertexcount; i++) {
        printf("Shortest path weight from %d to %d is %f\n", source, (minheap + (vertexcount-i-1)*sizeof(Node))->v->number, (minheap + (vertexcount-i-1)*sizeof(Node))->key);
    }

    free(minheap);
    return minheap;
}