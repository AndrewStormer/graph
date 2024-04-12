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
} edge_t;


typedef struct astruct {
    edge_t *edge;
    struct astruct *next;
} adjacency_t;


typedef struct vstruct {
    int number;
    adjacency_t *list;
} vertex_t;

typedef enum {DIRECTED, UNDIRECTED} dir_t;


typedef struct graph {
    vertex_t *v;
    int vertex_count;
    int edge_count;
    dir_t type;
} graph_t;

graph_t *directed_graph_initialize(char *filename);
graph_t *undirected_graph_initialize(char *filename);


void graphwalk(graph_t *graph);

#endif
