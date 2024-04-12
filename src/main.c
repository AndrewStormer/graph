#include "../include/graph.h"
#include "../include/dijkstra.h"

#define UNUSED(x) (void)(x) //Helps things compile!


int main(void) {
    int vertex_count = 0;
    int edge_count = 0;
    Vertex *graph = directed_graph_initialize("vertexlist.txt", &vertex_count, &edge_count);
    graphwalk(graph, vertex_count);

    Node *shortest_path_tree = dijkstra(graph, vertex_count, 1);
    UNUSED(shortest_path_tree);

    return 0;
}