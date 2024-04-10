#include "../include/mst.h"
#include "../include/bfs.h"
#include "../include/dfs.h"
#include "../include/dijkstra.h"
#include "../include/bellmanford.h"


void decoderelationstring(char *buffer, int *from, int *to, float *weight) {
    const char delim[] = " ";
    char * token;

    token = strtok(buffer, delim);
    if (token) {
        *from = atoi(token);
    }
    buffer += strlen(token) + 1;
    token = strtok(buffer, delim);
    if (token) {
        *to = atoi(token);
    }
        
    token = strtok(NULL, token);
    if(token) {
        *weight = atof(token);
    }
    //printf("%d->%d %f\n", *from, *to, *weight);
}


Edge * createedge(int from, int to, float weight) {
    Edge * edge = malloc(sizeof(Edge)); if (!edge) return NULL;
    edge->from = from;
    edge->to = to;
    edge->weight = weight;

    return edge;
}


Adjacency * createadjacency(Edge * edge) {
    Adjacency * adjacency = malloc(sizeof(Adjacency)); if (!adjacency) return NULL;
    adjacency->edge = edge;
    adjacency->next = NULL;

    return adjacency;
}


Adjacency * insertadjacency(Adjacency * list, Adjacency * newadjacency) {
    if (!list) {
        return newadjacency;
    } else {
        Adjacency * cursor = list;

        while (cursor->next) {
            cursor = cursor->next;
        }
        cursor->next = newadjacency;
        return list;
    }
}


Vertex * initializevertices(int vertexcount) {
    Vertex * vertices = malloc(sizeof(Vertex)*vertexcount); if (!vertices) return NULL;

    for (int i = 0; i < vertexcount; i++) {
        (vertices + i*sizeof(Vertex))->number = i+1;
        (vertices + i*sizeof(Vertex))->list = NULL;
    }
    return vertices;
}


Vertex * createdirectedgraph(int vertexcount, int edgecount, int from[], int to[], float weight[]) {
    Vertex * vertices = initializevertices(vertexcount); if (!vertices) return NULL;
    Vertex * sourcevertex = NULL;
    Edge * adjacentedge = NULL;
    Adjacency * newadjacency = NULL;

    for (int i = 0; i < edgecount; i++) {
        adjacentedge = createedge(from[i], to[i], weight[i]); if (!adjacentedge) return NULL;
        newadjacency = createadjacency(adjacentedge); if (!newadjacency) return NULL;

        sourcevertex = (vertices + (from[i]-1)*sizeof(Vertex));
        sourcevertex->list = insertadjacency(sourcevertex->list, newadjacency);
    }
    return vertices;
}


Vertex * createundirectedgraph(int vertexcount, int edgecount, int from[], int to[], float weight[]) {
    Vertex * vertices = initializevertices(vertexcount);
    Vertex * sourcevertex = NULL, * sinkvertex = NULL;
    Edge * adjacentedge1 = NULL, * adjacentedge2 = NULL;
    Adjacency * newadjacency1 = NULL, * newadjacency2 = NULL;

    for (int i = 0; i < edgecount; i++) {
        adjacentedge1 = createedge(from[i], to[i], weight[i]); if (!adjacentedge1) return NULL;
        newadjacency1 = createadjacency(adjacentedge1); if (!newadjacency1) return NULL;
        adjacentedge2 = createedge(from[i], to[i], weight[i]); if (!adjacentedge2) return NULL;
        newadjacency2 = createadjacency(adjacentedge1); if (!newadjacency2) return NULL;

        sourcevertex = (vertices + (from[i]-1)*sizeof(Vertex));
        sourcevertex->list = insertadjacency(sourcevertex->list, newadjacency1);
        sinkvertex = (vertices + (to[i]-1)*sizeof(Vertex));
        sinkvertex->list = insertadjacency(sinkvertex->list, newadjacency2);
    }
    return vertices;
}



void rungraphalgorithms(FILE * fp) {
    int vertexcount, edgecount, from = 0, to = 0, index = 0; char * line = NULL; size_t linesize = 0; float weight = 0.0;
    fscanf(fp, "%d", &vertexcount);
    fscanf(fp, "%d", &edgecount);

    int * fromarr = malloc(sizeof(int)*edgecount); if (!fromarr) exit(1);
    int * toarr = malloc(sizeof(int)*edgecount); if (!toarr) exit(1);
    float * weightarr = malloc(sizeof(float)*edgecount); if (!weightarr) exit(1);

    getline(&line, &linesize, fp);
    while(getline(&line, &linesize, fp) != -1 && index < edgecount) {
        decoderelationstring(line, &from, &to, &weight);
        printf("%d->%d(%f)\n", from, to , weight);
        fromarr[index] = from; toarr[index] = to; weightarr[index] = weight;
        index++;
    }

    Vertex * directedgraph = createdirectedgraph(vertexcount, edgecount, fromarr, toarr, weightarr); if (!directedgraph) { printf("createdirectedgraph function call failed!\n"); exit(1);}
    Vertex * undirectedgraph = createundirectedgraph(vertexcount, edgecount, fromarr, toarr, weightarr); if (!undirectedgraph) { printf("createundirectedgraph function call failed!\n"); exit(1);}

    BFS(undirectedgraph, vertexcount, 1); //Breadth first search of either a directed or undirected graph
    DFS(undirectedgraph, vertexcount); //Depth first search of either a directed or undirext graph
    //MST_Prim(undirectedgraph, 1, vertexcount); //Creates a Minimum Spanning Tree on the undirected graph
    dijkstra(directedgraph, vertexcount, 1); //Finds all shorts paths from the each vertex to the source
    bool negativeweightcycle = true;
    bellmanford(directedgraph, vertexcount, 1, &negativeweightcycle);
}



void graphwalk(Vertex * graph, int vertexcount) {
    Adjacency * cursor = NULL;
    for (int i = 0; i < vertexcount; i++) {
        cursor = (graph + i*sizeof(Vertex))->list;
        while (cursor) {
            if (cursor->edge != NULL) {
                printf("%d->%d %f\n", cursor->edge->from, cursor->edge->to, cursor->edge->weight);
            } else
                break;
            cursor = cursor->next;
        }
    }
}