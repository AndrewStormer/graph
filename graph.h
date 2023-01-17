#ifndef _graph_h
#define _graph_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define INT_MAX 2147483647

#define WHITE 0
#define GREY 1
#define BLACK 2


typedef struct estruct {
    int from, to;
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

void rungraphalgorithms(FILE * fp);
void graphwalk(Vertex * graph, int vertexcount);

#endif
