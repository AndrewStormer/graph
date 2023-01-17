#include "bfs.h"


QNode * createqnode(BFSNode * v) {
    QNode * qnode = malloc(sizeof(QNode)); if (!qnode) return NULL;
    qnode->next = NULL;
    qnode->v = v;

    return qnode;
}


QNode * enqueue(QNode * queue, BFSNode * v) {
    QNode * newqnode = createqnode(v); if (!newqnode) return NULL;
    if (!queue)
        return newqnode;
    QNode * cursor = queue;

    while (cursor->next) {
        cursor = cursor->next;
    }
    cursor->next = newqnode;

    return queue;
}


QNode * removetop(QNode ** queue) {
    if (*queue) {
        QNode * temp = *queue;
        if ((*queue)->next) {
            *queue = (*queue)->next;
        }
        return temp;
    } else {
        return NULL;
    }
}


BFSNode * initializeDFSTree(Vertex * vertices, int vertexcount) {
    BFSNode * tree = malloc(sizeof(BFSNode)*vertexcount); if (!tree) return NULL;
    for (int i = 0; i < vertexcount; i++) {
        (tree + i*sizeof(BFSNode))->v = (vertices + i*sizeof(Vertex));
        (tree + i*sizeof(BFSNode))->color = WHITE;
        (tree + i*sizeof(BFSNode))->d = INT_MAX;
        (tree + i*sizeof(BFSNode))->p = NULL;
    }    

    return tree;
}


BFSNode * BFS(Vertex * vertices, int vertexcount, int startnumber) {
    printf("BFS Start\n");
    BFSNode * tree = initializeDFSTree(vertices, vertexcount); if (!tree) return NULL;
    QNode * queue = NULL;
    queue = enqueue(queue, (tree + (startnumber-1)*sizeof(BFSNode)));
    queue->v->d = 0;
    int foundvertices = 0;

    while (queue && foundvertices != vertexcount-1) {
        QNode * qu = removetop(&queue);
        BFSNode * u = qu->v;

        Adjacency * cursor = u->v->list;
        while (cursor) {
            BFSNode * adjacenctvertex = (tree + (cursor->edge->to-1)*sizeof(BFSNode));
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
