#include "mst.h"


//Min Heap functions
void nodeSwap(Node * node1, Node * node2) {
    Node temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}


void heapify(Node * minHeap, int index, int size) {
    int left = 2*index + 1, right = 2*index + 2, min = index;
    
    if (size > left && ((minHeap + sizeof(Node)*left)->key < (minHeap + sizeof(Node)*min)->key))
        min = left;
    if (size > right && ((minHeap + sizeof(Node)*right)->key < (minHeap + sizeof(Node)*min)->key))
        min = right;
    
    if (min != index) {
        nodeSwap((minHeap + sizeof(Node)*min), (minHeap + sizeof(Node)*index));
        heapify(minHeap, min, size);
    }
}


void buildHeap(Node * minHeap, int size) {
    int startNumber = (size/2);
    for (int i = startNumber; i >= 0; i--) {
        heapify(minHeap, i, size);
    }
}


//returns minumum elements of heap and decreases heapSize
Node * extractMin(Node * minHeap, int * heapSize) {
    --*heapSize;
    nodeSwap(minHeap, (minHeap + (*heapSize)*sizeof(Node)));

    return (minHeap + (*heapSize)*sizeof(Node));
}


//Utility Functions
Vertex * getVertex(Vertex * vertices, int countVertices, int edgeNumber) {
    return (vertices + edgeNumber*sizeof(Vertex));
}


Node * getNode(Node * minHeap, int heapSize, Vertex * adjVertex) {
    for (int i = 0; i < heapSize; i++) {
        Node * vertex = (minHeap + i*sizeof(Node));
        if (vertex->v == adjVertex)
            return vertex;
    }
    return NULL;
}


/*
Goes through each adjacent vertex to the vertex passed in and links their parent and sets their key value to the weight of the edge if that vertex isn't already discovered and the weight of the edge is less than it's key value
*/
Node * setAllAdjacentVertices(Node * minHeap, Node * currentVertex, int heapSize, Vertex * vertices, int countVertices) {
    Adjacency * listCursor = currentVertex->v->list; if (!listCursor) return minHeap;

    while (listCursor) {
        Vertex * adjVertex = NULL;
        if (listCursor->edge->to == currentVertex->v->number) {
            adjVertex = getVertex(vertices, countVertices, listCursor->edge->from-1); if (!adjVertex) {printf("\ngetVertex function call failed\n"); return NULL;};
        } else {
            adjVertex = getVertex(vertices, countVertices, listCursor->edge->to-1); if (!adjVertex) {printf("\ngetVertex function call failed\n"); return NULL;};
        }

        Node * adjNode = getNode(minHeap, heapSize, adjVertex);
        if (adjNode && listCursor->edge->weight < adjNode->key) {
            adjNode->p = currentVertex;
            adjNode->key = listCursor->edge->weight;
        }
        listCursor = listCursor->next;
    }
    return minHeap;
}


/*
Used when the MST_Prim algorithm is first run. This function initializes each vertices key to infinity, except the starting vertex which is set to 0
*/
Node * initializePrimHeap(Vertex * vertices, int startNumber, int countVertices) {
    Node * minHeap = malloc(countVertices*sizeof(Node)); if (!minHeap) return NULL;

    for (int i = 0; i < countVertices; i++) {
        Node * vertex = (minHeap + i*sizeof(Node));
        vertex->v = (vertices + i*sizeof(Vertex));
        vertex->p = NULL;

        if (vertex->v->number == startNumber) {
            vertex->key = 0.0;
            nodeSwap(minHeap + i*sizeof(Node), minHeap);
        } else {
            vertex->key = INFINITY;
        }
    }
    return minHeap;
}


void treeWalk(Node * MST, int countVertices) {
    float totalWeight = 0.0;

    Node * vertex1 = NULL;
    Node * vertex2 = NULL; 

    for (int i = countVertices-1; i >= 0 ; i--) {
        for (int j = countVertices-1; j >= 0; j--) {
            vertex1 = (MST + i*sizeof(Node));
            vertex2 = (MST + j*sizeof(Node));

            if (vertex1->p == vertex2) {
                printf("%d",vertex2->v->number);
                printf("->%d", vertex1->v->number);
                printf("(%f)\n", vertex1->key);
                totalWeight += vertex1->key;
            } 
        }
    }
    printf("Total MST weight: %f\n", totalWeight);
}


void freeMST(Node * MST) {
    free(MST);
}


void MST_Prim(Vertex * vertices, int startNumber, int countVertices) {
    printf("MST Start\n");
    Node * minHeap = initializePrimHeap(vertices, startNumber, countVertices);
    int heapSize = countVertices;

    while (heapSize > 0 && minHeap) {
        Node * u = extractMin(minHeap, &heapSize); if (!u) {printf("extractMin function call failed\n"); break;};
        minHeap = setAllAdjacentVertices(minHeap, u, heapSize, vertices, countVertices); if (!minHeap) {printf("setAllAdjacentVertices function call failed\n"); break;};
        buildHeap(minHeap, heapSize);
    }

    if (minHeap)
        treeWalk(minHeap, countVertices);
    else
        printf("Something went wrong with your MST_Prim function call!\n");
    freeMST(minHeap);
}
