#include "../include/graph.h"


void decoderelationstring(char *buffer, int *from, int *to, float *weight) {
    const char delim[] = " \0\n";
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


edge_t *createedge(int from, int to, float weight) {
    edge_t *edge = malloc(sizeof(edge_t)); 
    if (!edge) 
        return NULL;

    edge->from = from;
    edge->to = to;
    edge->weight = weight;

    return edge;
}


adjacency_t *createadjacency(edge_t *edge) {
    adjacency_t *adjacency = malloc(sizeof(adjacency_t)); 
    if (!adjacency) 
        return NULL;

    adjacency->edge = edge;
    adjacency->next = NULL;

    return adjacency;
}


adjacency_t *insertadjacency(adjacency_t *list, adjacency_t *newadjacency) {
    if (!newadjacency)
        return NULL;

    if (!list) {
        return newadjacency;
    }
    
    adjacency_t *cursor = list;

    while (cursor->next) {
        cursor = cursor->next;
    }
    cursor->next = newadjacency;
    return list;
}


vertex_t *initializevertices(int vertexcount) {
    if (vertexcount < 0)
        return NULL;

    vertex_t *vertices = malloc(sizeof(vertex_t)*vertexcount); 
    if (!vertices)
        return NULL;

    for (int i = 0; i < vertexcount; ++i) {
        (vertices + i*sizeof(vertex_t))->number = i+1;
        (vertices + i*sizeof(vertex_t))->list = NULL;
    }
    return vertices;
}


vertex_t *createdirectedgraph(int vertexcount, int edgecount, int *from, int *to, float *weight) {
    if (vertexcount < 0 || !from || !to || !weight)
        return NULL;
    vertex_t *vertices = initializevertices(vertexcount); 
    if (!vertices) 
        return NULL;


    for (int i = 0; i < edgecount; i++) {
        edge_t *adjacentedge = createedge(from[i], to[i], weight[i]);
        if (!adjacentedge)  {
            free(vertices);
            return NULL;
        }
        adjacency_t *newadjacency = createadjacency(adjacentedge); 
        if (!newadjacency)   {
            free(vertices);
            return NULL;
        }

        vertex_t *sourcevertex = (vertices + (from[i]-1)*sizeof(vertex_t));
        sourcevertex->list = insertadjacency(sourcevertex->list, newadjacency);
        if (!sourcevertex->list)  {
            free(vertices);
            return NULL;
        }
    }
    return vertices;
}


vertex_t *createundirectedgraph(int vertexcount, int edgecount, int *from, int *to, float *weight) {
    vertex_t *vertices = initializevertices(vertexcount);

    for (int i = 0; i < edgecount; i++) {
        edge_t *adjacentedge1 = createedge(from[i], to[i], weight[i]);
        if (!adjacentedge1) {
            free(vertices);
            return NULL;
        }

        adjacency_t *newadjacency1 = createadjacency(adjacentedge1); 
        if (!newadjacency1) {
            free(vertices);
            return NULL;
        }

        edge_t *adjacentedge2 = createedge(from[i], to[i], weight[i]); 
        if (!adjacentedge2) {
            free(vertices);
            return NULL;
        }

        adjacency_t *newadjacency2 = createadjacency(adjacentedge1); 
        if (!newadjacency2) {
            free(vertices);
            return NULL;
        }

        vertex_t *sourcevertex = (vertices + (from[i]-1)*sizeof(vertex_t));
        sourcevertex->list = insertadjacency(sourcevertex->list, newadjacency1);
        if (!sourcevertex->list) {
            free(vertices);
            return NULL;
        }

        vertex_t *sinkvertex = (vertices + (to[i]-1)*sizeof(vertex_t));
        sinkvertex->list = insertadjacency(sinkvertex->list, newadjacency2);
        if (!sinkvertex->list) {
            free(vertices);
            return NULL;
        }
    }
    return vertices;
}


graph_t *directed_graph_initialize(char *filename) {
    if (!filename || strlen(filename) == 0)
        return NULL;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return NULL;
    }

    int vertex_count;
    int edge_count;

    fscanf(fp, "%d", &vertex_count);
    fscanf(fp, "%d", &edge_count);

    char *line = NULL;
    size_t linesize;
    int *from = malloc((edge_count)*sizeof(int));
    int *to = malloc((edge_count)*sizeof(int));
    float *weight = malloc((edge_count)*sizeof(float));

    int index = 0;

    getline(&line, &linesize, fp);
    while(index < edge_count && (getline(&line, &linesize, fp) != -1)) {
        decoderelationstring(line, &from[index], &to[index], &weight[index]);
        ++index;
    }
    fclose(fp);
    graph_t *graph = malloc(sizeof(graph_t));
    if (!graph) {
        free(from);
        free(to);
        free(weight);
    }
    graph->edge_count = edge_count;
    graph->vertex_count = vertex_count;
    graph->v = createdirectedgraph(vertex_count, edge_count, from, to, weight);
    graph->type = DIRECTED;
    free(from);
    free(to);
    free(weight);
    if (!graph->v)
        return NULL;
    return graph;
}


graph_t *undirected_graph_initialize(char *filename) {
    if (!filename || strlen(filename) == 0)
        return NULL;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return NULL;
    }

    int vertex_count;
    int edge_count;

    fscanf(fp, "%d", &vertex_count);
    fscanf(fp, "%d", &edge_count);



    char *line = NULL;
    size_t linesize;
    int *from = malloc((edge_count+1)*sizeof(int));
    int *to = malloc((edge_count+1)*sizeof(int));
    float *weight = malloc((edge_count+1)*sizeof(float));

    int index = 0;

    getline(&line, &linesize, fp);
    while((getline(&line, &linesize, fp) != -1) && index < edge_count) {
        decoderelationstring(line, &from[index], &to[index], &weight[index]);
        ++index;
    }
    fclose(fp);

    graph_t *graph = malloc(sizeof(graph_t));
    if (!graph) {
        free(from);
        free(to);
        free(weight);
    }
    graph->edge_count = edge_count;
    graph->vertex_count = vertex_count;
    graph->v = createundirectedgraph(vertex_count, edge_count, from, to, weight);
    graph->type = UNDIRECTED;
    free(from);
    free(to);
    free(weight);
    if (!graph->v)
        return NULL;
    return graph;
}



void graphwalk(graph_t *grapht) {
    vertex_t *graph = grapht->v;
    int vertexcount = grapht->vertex_count;
    adjacency_t *cursor = NULL;
    for (int i = 0; i < vertexcount; i++) {
        cursor = (graph + i*sizeof(vertex_t))->list;
        while (cursor) {
            if (cursor->edge != NULL) {
                printf("%d->%d %f\n", cursor->edge->from, cursor->edge->to, cursor->edge->weight);
            } else
                break;
            cursor = cursor->next;
        }
    }
}