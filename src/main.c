#include "../include/graph.h"
#include "../include/dijkstra.h"

#define UNUSED(x) (void)(x) //Helps things compile!


int main(void) {
    graph_t *graph = directed_graph_initialize("vertexlist.txt");
    graphwalk(graph);

    node_t *shortest_path_tree = dijkstra(graph, 1);
    UNUSED(shortest_path_tree);

    return 0;
}