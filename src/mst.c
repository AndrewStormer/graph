#include "../include/mst.h"
#include "../include/graph.h"



//Min Heap functions
void node_swap(Node * node1, Node * node2) {
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
        node_swap((minHeap + sizeof(Node)*min), (minHeap + sizeof(Node)*index));
        heapify(minHeap, min, size);
    }
}


void build_heap(Node * minHeap, int size) {
    int startNumber = (size/2);
    for (int i = startNumber; i >= 0; i--) {
        heapify(minHeap, i, size);
    }
}


//returns minumum elements of heap and decreases heapSize
Node * extract_min(Node * minHeap, int * heapSize) {
    --*heapSize;
    node_swap(minHeap, (minHeap + (*heapSize)*sizeof(Node)));

    return (minHeap + (*heapSize)*sizeof(Node));
}


//Utility Functions
Vertex * get_vertex(Vertex * vertices, int countVertices, int edgeNumber) {
    return (vertices + edgeNumber*sizeof(Vertex));
}


Node * get_node(Node * minHeap, int heapSize, Vertex * adjVertex) {
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
Node * set_all_adjacent_vertices(Node * minHeap, Node * currentVertex, int heapSize, Vertex * vertices, int countVertices) {
    Adjacency * listCursor = currentVertex->v->list; if (!listCursor) return minHeap;

    while (listCursor) {
        Vertex * adjVertex = NULL;
        if (listCursor->edge->to == currentVertex->v->number) {
            adjVertex = get_vertex(vertices, countVertices, listCursor->edge->from-1); if (!adjVertex) {printf("\nget_vertex function call failed\n"); return NULL;};
        } else {
            adjVertex = get_vertex(vertices, countVertices, listCursor->edge->to-1); if (!adjVertex) {printf("\nget_vertex function call failed\n"); return NULL;};
        }

        Node * adjNode = get_node(minHeap, heapSize, adjVertex);
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
Node * initialize_prim_heap(Vertex * vertices, int startNumber, int countVertices) {
    Node * minHeap = malloc(countVertices*sizeof(Node)); if (!minHeap) return NULL;

    for (int i = 0; i < countVertices; i++) {
        Node * vertex = (minHeap + i*sizeof(Node));
        vertex->v = (vertices + i*sizeof(Vertex));
        vertex->p = NULL;

        if (vertex->v->number == startNumber) {
            vertex->key = 0.0;
            node_swap(minHeap + i*sizeof(Node), minHeap);
        } else {
            vertex->key = INFINITY;
        }
    }
    return minHeap;
}


void tree_walk(Node * MST, int countVertices) {
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
    Node * minHeap = initialize_prim_heap(vertices, startNumber, countVertices);
    int heapSize = countVertices;

    while (heapSize > 0 && minHeap) {
        Node * u = extract_min(minHeap, &heapSize); if (!u) {printf("extract_min function call failed\n"); break;};
        minHeap = set_all_adjacent_vertices(minHeap, u, heapSize, vertices, countVertices); if (!minHeap) {printf("set_all_adjacent_vertices function call failed\n"); break;};
        build_heap(minHeap, heapSize);
    }

    if (minHeap)
        tree_walk(minHeap, countVertices);
    else
        printf("Something went wrong with your MST_Prim function call!\n");
    freeMST(minHeap);
}
