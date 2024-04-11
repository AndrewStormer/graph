#include "../include/graph.h"


int main(void) {
    int vertex_count = 0;
    int edge_count = 0;
    Vertex *graph = directed_graph_initialize("vertexlist.txt", &vertex_count, &edge_count);
    graphwalk(graph, vertex_count);

    dijkstra(graph, vertex_count, 1);

    return 0;
}