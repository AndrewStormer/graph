#include "../include/graph.h"


void decoderelationstring(char *buffer, int *from, int *to, float *weight) {
    const char delim[] = " ";
    char *token;

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


Edge *createedge(int from, int to, float weight) {
    Edge *edge = malloc(sizeof(Edge)); 
    if (!edge) 
        return NULL;

    edge->from = from;
    edge->to = to;
    edge->weight = weight;

    return edge;
}


Adjacency *createadjacency(Edge *edge) {
    Adjacency *adjacency = malloc(sizeof(Adjacency)); 
    if (!adjacency) 
        return NULL;

    adjacency->edge = edge;
    adjacency->next = NULL;

    return adjacency;
}


Adjacency *insertadjacency(Adjacency *list, Adjacency *newadjacency) {
    if (!newadjacency)
        return NULL;

    if (!list) {
        list = newadjacency;
        return newadjacency;
    }
    
    Adjacency *cursor = list;

    while (cursor->next) {
        cursor = cursor->next;
    }
    cursor->next = newadjacency;
    return list;
}


Vertex *initializevertices(int vertexcount) {
    if (vertexcount < 0)
        return NULL;

    Vertex *vertices = malloc(sizeof(Vertex)*vertexcount); 
    if (!vertices)
        return NULL;

    for (int i = 0; i < vertexcount; ++i) {
        (vertices + i*sizeof(Vertex))->number = i+1;
        (vertices + i*sizeof(Vertex))->list = NULL;
    }
    return vertices;
}


Vertex *createdirectedgraph(int vertexcount, int edgecount, int *from, int *to, float *weight) {
    if (vertexcount < 0 || !from || !to || !weight)
        return NULL;
    Vertex *vertices = initializevertices(vertexcount); 
    if (!vertices) 
        return NULL;
    Vertex *sourcevertex = NULL;
    Edge *adjacentedge = NULL;
    Adjacency *newadjacency = NULL;

    for (int i = 0; i < edgecount; i++) {
        adjacentedge = createedge(from[i], to[i], weight[i]);
        if (!adjacentedge)  {
            free(vertices);
            return NULL;
        }
        newadjacency = createadjacency(adjacentedge); 
        if (!newadjacency)   {
            free(vertices);
            return NULL;
        }

        sourcevertex = (vertices + (from[i]-1)*sizeof(Vertex));
        sourcevertex->list = insertadjacency(sourcevertex->list, newadjacency);
        if (!sourcevertex->list)  {
            free(vertices);
            return NULL;
        }
    }
    return vertices;
}


Vertex *createundirectedgraph(int vertexcount, int edgecount, int from[], int to[], float weight[]) {
    Vertex *vertices = initializevertices(vertexcount);
    Vertex *sourcevertex = NULL;
    Vertex *sinkvertex = NULL;
    Edge *adjacentedge1 = NULL;
    Edge *adjacentedge2 = NULL;
    Adjacency *newadjacency1 = NULL;
    Adjacency *newadjacency2 = NULL;

    for (int i = 0; i < edgecount; i++) {
        adjacentedge1 = createedge(from[i], to[i], weight[i]);
        if (!adjacentedge1) {
            free(vertices);
            return NULL;
        }

        newadjacency1 = createadjacency(adjacentedge1); 
        if (!newadjacency1) {
            free(vertices);
            return NULL;
        }

        adjacentedge2 = createedge(from[i], to[i], weight[i]); 
        if (!adjacentedge2) {
            free(vertices);
            return NULL;
        }

        newadjacency2 = createadjacency(adjacentedge1); 
        if (!newadjacency2) {
            free(vertices);
            return NULL;
        }

        sourcevertex = (vertices + (from[i]-1)*sizeof(Vertex));
        sourcevertex->list = insertadjacency(sourcevertex->list, newadjacency1);
        if (!sourcevertex->list) {
            free(vertices);
            return NULL;
        }

        sinkvertex = (vertices + (to[i]-1)*sizeof(Vertex));
        sinkvertex->list = insertadjacency(sinkvertex->list, newadjacency2);
        if (!sinkvertex->list) {
            free(vertices);
            return NULL;
        }
    }
    return vertices;
}


Vertex *directed_graph_initialize(char *filename, int *vertex_count, int *edge_count) {
    if (!filename || strlen(filename) == 0 || !vertex_count || !edge_count)
        return NULL;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return NULL;
    }

    fscanf(fp, "%d", vertex_count);
    if (!vertex_count)
        return NULL;
    fscanf(fp, "%d", edge_count);
    if (!edge_count)
        return NULL;

    char *line = NULL;
    size_t linesize;
    int *from = malloc((*edge_count+1)*sizeof(int));
    int *to = malloc((*edge_count+1)*sizeof(int));
    float *weight = malloc((*edge_count+1)*sizeof(float));

    int index = 0;

    getline(&line, &linesize, fp);
    while((getline(&line, &linesize, fp) != -1) && index < *edge_count) {
        decoderelationstring(line, &from[index], &to[index], &weight[index]);
        ++index;
    }
    Vertex *graph = createdirectedgraph(*vertex_count, *edge_count, from, to, weight);
    if (!graph)
        return NULL;
    free(from);
    free(to);
    free(weight);
    return graph;
}


Vertex *undirected_graph_initialize(char *filename, int *vertex_count, int *edge_count) {
    if (!filename || strlen(filename) == 0 || !vertex_count || !edge_count)
        return NULL;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return NULL;
    }

    fscanf(fp, "%d", vertex_count);
    if (!vertex_count)
        return NULL;
    fscanf(fp, "%d", edge_count);
    if (!edge_count)
        return NULL;

    char *line = NULL;
    size_t linesize;
    int *from = malloc((*edge_count+1)*sizeof(int));
    int *to = malloc((*edge_count+1)*sizeof(int));
    float *weight = malloc((*edge_count+1)*sizeof(float));

    int index = 0;

    getline(&line, &linesize, fp);
    while((getline(&line, &linesize, fp) != -1) && index < *edge_count) {
        decoderelationstring(line, &from[index], &to[index], &weight[index]);
        ++index;
    }
    Vertex *graph = createundirectedgraph(*vertex_count, *edge_count, from, to, weight);
    if (!graph)
        return NULL;
    free(from);
    free(to);
    free(weight);
    return graph;
}



void graphwalk(Vertex *graph, int vertexcount) {
    Adjacency *cursor = NULL;
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