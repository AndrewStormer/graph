#include "../include/mst.h"


//Min Heap functions
void node_swap(node_t *node1, node_t *node2) {
    node_t temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}


void heapify(node_t *minHeap, int index, int size) {
    int left = 2*index + 1, right = 2*index + 2, min = index;
    
    if (size > left && ((minHeap + sizeof(node_t)*left)->key < (minHeap + sizeof(node_t)*min)->key))
        min = left;
    if (size > right && ((minHeap + sizeof(node_t)*right)->key < (minHeap + sizeof(node_t)*min)->key))
        min = right;
    
    if (min != index) {
        node_swap((minHeap + sizeof(node_t)*min), (minHeap + sizeof(node_t)*index));
        heapify(minHeap, min, size);
    }
}


void build_heap(node_t *minHeap, int size) {
    int startNumber = (size/2);
    for (int i = startNumber; i >= 0; i--) {
        heapify(minHeap, i, size);
    }
}


//returns minumum elements of heap and decreases heapSize
node_t *extract_min(node_t *minHeap, int *heapSize) {
    --*heapSize;
    node_swap(minHeap, (minHeap + (*heapSize)*sizeof(node_t)));

    return (minHeap + (*heapSize)*sizeof(node_t));
}


//Utility Functions
vertex_t *get_vertex(vertex_t *vertices, int countVertices, int edgeNumber) {
    if (edgeNumber > countVertices)
        return NULL;
    return (vertices + edgeNumber*sizeof(vertex_t));
}


node_t *get_node(node_t *minHeap, int heapSize, vertex_t *adjVertex) {
    for (int i = 0; i < heapSize; i++) {
        node_t *vertex = (minHeap + i*sizeof(node_t));
        if (vertex->v == adjVertex)
            return vertex;
    }
    return NULL;
}


/*
Goes through each adjacent vertex to the vertex passed in and links their parent and sets their key value to the weight of the edge if that vertex isn't already discovered and the weight of the edge is less than it's key value
*/
node_t *set_all_adjacent_vertices(node_t *minHeap, node_t *currentVertex, int heapSize, vertex_t *vertices, int countVertices) {
    adjacency_t *listCursor = currentVertex->v->list; if (!listCursor) return minHeap;

    while (listCursor) {
        vertex_t *adjVertex = NULL;
        if (listCursor->edge->to == currentVertex->v->number) {
            adjVertex = get_vertex(vertices, countVertices, listCursor->edge->from-1); if (!adjVertex) {printf("\nget_vertex function call failed\n"); return NULL;};
        } else {
            adjVertex = get_vertex(vertices, countVertices, listCursor->edge->to-1); if (!adjVertex) {printf("\nget_vertex function call failed\n"); return NULL;};
        }

        node_t *adjNode = get_node(minHeap, heapSize, adjVertex);
        if (adjNode && listCursor->edge->weight < adjNode->key) {
            adjNode->p = currentVertex;
            adjNode->key = listCursor->edge->weight;
        }
        listCursor = listCursor->next;
    }
    return minHeap;
}


/*
Used when the mst_prim algorithm is first run. This function initializes each vertices key to infinity, except the starting vertex which is set to 0
*/
node_t *initialize_prim_heap(vertex_t *vertices, int startNumber, int countVertices) {
    if (!vertices || startNumber < 0 || startNumber > countVertices || countVertices < 1)
        return NULL;
    node_t *minHeap = malloc(countVertices*sizeof(node_t)); 
    if (!minHeap) 
        return NULL;

    for (int i = 0; i < countVertices; i++) {
        node_t *vertex = (minHeap + i*sizeof(node_t));
        vertex->v = (vertices + i*sizeof(vertex_t));
        vertex->p = NULL;

        if (vertex->v->number == startNumber) {
            vertex->key = 0.0;
            node_swap(minHeap + i*sizeof(node_t), minHeap);
        } else {
            vertex->key = INFINITY;
        }
    }
    return minHeap;
}


void tree_walk(node_t *mst, int countVertices) {
    float totalWeight = 0.0;

    node_t *vertex1 = NULL;
    node_t *vertex2 = NULL; 

    for (int i = countVertices-1; i >= 0 ; i--) {
        for (int j = countVertices-1; j >= 0; j--) {
            vertex1 = (mst + i*sizeof(node_t));
            vertex2 = (mst + j*sizeof(node_t));

            if (vertex1->p == vertex2) {
                printf("%d",vertex2->v->number);
                printf("->%d", vertex1->v->number);
                printf("(%f)\n", vertex1->key);
                totalWeight += vertex1->key;
            } 
        }
    }
    printf("Total mst weight: %f\n", totalWeight);
}


void freemst(node_t *mst) {
    free(mst);
}


node_t *mst_prim(graph_t *g, int startNumber ) {
    if (!g || !g->v || g->edge_count < 1 || g->vertex_count < 1 || g->type != UNDIRECTED)
        return NULL;

    vertex_t *vertices = g->v;
    int countVertices = g->vertex_count;
    node_t *minHeap = initialize_prim_heap(vertices, startNumber, countVertices);
    int heapSize = countVertices;

    while (heapSize > 0 && minHeap) {
        node_t *u = extract_min(minHeap, &heapSize); if (!u) {printf("extract_min function call failed\n"); break;};
        minHeap = set_all_adjacent_vertices(minHeap, u, heapSize, vertices, countVertices); if (!minHeap) {printf("set_all_adjacent_vertices function call failed\n"); break;};
        build_heap(minHeap, heapSize);
    }
    return minHeap;
}
