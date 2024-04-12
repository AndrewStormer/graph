#include "../include/bfs.h"


qnode_t *createqnode(bfsnode_t *v) {
    qnode_t *qnode = malloc(sizeof(qnode_t)); if (!qnode) return NULL;
    qnode->next = NULL;
    qnode->v = v;

    return qnode;
}


qnode_t *enqueue(qnode_t *queue, bfsnode_t *v) {
    qnode_t *newqnode = createqnode(v); if (!newqnode) return NULL;
    if (!queue)
        return newqnode;
    qnode_t *cursor = queue;

    while (cursor->next) {
        cursor = cursor->next;
    }
    cursor->next = newqnode;

    return queue;
}


qnode_t *removetop(qnode_t **queue) {
    if (*queue) {
        qnode_t *temp = *queue;
        if ((*queue)->next) {
            *queue = (*queue)->next;
        }
        return temp;
    } else {
        return NULL;
    }
}


bfsnode_t *initializeDFSTree(vertex_t *vertices, int vertexcount) {
    bfsnode_t *tree = malloc(sizeof(bfsnode_t)*vertexcount); if (!tree) return NULL;
    for (int i = 0; i < vertexcount; i++) {
        (tree + i*sizeof(bfsnode_t))->v = (vertices + i*sizeof(vertex_t));
        (tree + i*sizeof(bfsnode_t))->color = WHITE;
        (tree + i*sizeof(bfsnode_t))->d = INT_MAX;
        (tree + i*sizeof(bfsnode_t))->p = NULL;
    }    

    return tree;
}


bfsnode_t *BFS(graph_t *g, int startnumber) {
    vertex_t *vertices = g->v;
    int vertexcount = g->vertex_count;
    bfsnode_t *tree = initializeDFSTree(vertices, vertexcount); if (!tree) return NULL;
    qnode_t *queue = NULL;
    queue = enqueue(queue, (tree + (startnumber-1)*sizeof(bfsnode_t)));
    queue->v->d = 0;
    int foundvertices = 0;

    while (queue && foundvertices != vertexcount-1) {
        qnode_t *qu = removetop(&queue);
        bfsnode_t *u = qu->v;

        adjacency_t *cursor = u->v->list;
        while (cursor) {
            bfsnode_t *adjacenctvertex = (tree + (cursor->edge->to-1)*sizeof(bfsnode_t));
            if (adjacenctvertex->color == WHITE) {
                printf("Found vertex %d from vertex %d with a distance of %d from source\n", adjacenctvertex->v->number, u->v->number, u->d+1);
                adjacenctvertex->color = GREY;
                adjacenctvertex->d = u->d+1;
                adjacenctvertex->p = u;
                queue = enqueue(queue, adjacenctvertex);
                ++foundvertices;
            }
            u->color = BLACK;
            cursor = cursor->next;
        }
    }
    return tree;
}
