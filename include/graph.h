#ifndef _graph_h
#define _graph_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stddef.h>

#ifndef __null
#define __null ((char *)0)
#endif

#define INT_MAX 2147483647

#define WHITE 0
#define GREY 1
#define BLACK 2


typedef struct estruct {
    int from;
    int to;
    float weight;
} Edge;


typedef struct astruct {
    Edge * edge;
    struct astruct * next;
} Adjacency;


typedef struct vstruct {
    int number;
    Adjacency * list;
} Vertex;

Vertex *directed_graph_initialize(char *filename, int *vertex_count, int *edge_count);
Vertex *undirected_graph_initialize(char *filename, int *vertex_count, int *edge_count);


void graphwalk(Vertex * graph, int vertexcount);

#endif
