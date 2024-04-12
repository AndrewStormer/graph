#include "../include/bellmanford.h"


Node * bellmanford(Vertex * vertices, int vertexcount, int source, int * negativeloopcycle) {
    printf("Bellmanford start\n");
    Node * shortestpath = malloc(sizeof(Node)*vertexcount);
    for (int i = 0; i < vertexcount; i++) {
        (shortestpath + i*sizeof(Node))->key = (i == source-1) ? 0 : INFINITY;
        (shortestpath + i*sizeof(Node))->p = NULL;
        (shortestpath + i*sizeof(Node))->v = (vertices + i*sizeof(Vertex));
    }

    Adjacency * cursor = NULL;
    for (int i = 0; i < vertexcount; i++) {
        cursor = (vertices + i*sizeof(Vertex))->list;
        while (cursor) {
            relax(shortestpath, cursor, (shortestpath + (cursor->edge->from-1)*sizeof(Node)), (shortestpath + (cursor->edge->to-1)*sizeof(Node)));
            cursor = cursor->next;
        }
    }
    cursor = NULL;
    Node * u = NULL, * v = NULL;
    for (int i = 0; i < vertexcount; i++) {
        cursor = (vertices + i*sizeof(Vertex))->list;
        while (cursor) {
            u = get_node(shortestpath, vertexcount, (vertices + (cursor->edge->from-1)*sizeof(Vertex)));
            v = get_node(shortestpath, vertexcount, (vertices + (cursor->edge->to-1)*sizeof(Vertex)));
            if (v->key > u->key + cursor->edge->weight || cursor->edge->weight < 0) {
                *negativeloopcycle = 0;
            }
            cursor = cursor->next;
        }
    }
    if (*negativeloopcycle) {
        for (int i = 1; i < vertexcount; i++) {
            printf("Shortest path weight from %d to %d is %f\n", source, (shortestpath + i*sizeof(Node))->v->number, (shortestpath + i*sizeof(Node))->key);
        }
    } else 
        printf("Negative weight cycle detected\n");
    return shortestpath;
}