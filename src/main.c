#include "../include/graph.h"
#include "../include/dijkstra.h"
#include "../include/mst.h"


int main(void) {
    graph_t *graph = undirected_graph_initialize("vertexlist.txt");
    graphwalk(graph);

    node_t *mst = mst_prim(graph, 1);
    if (!mst)
        exit(1);
    tree_walk(mst, graph->vertex_count);

    graph_t *graph2 = directed_graph_initialize("vertexlist.txt");
    graphwalk(graph);
    node_t *shortest_path_tree = dijkstra(graph2, 1);
    if (!shortest_path_tree)
        exit(1);

    return 0;
}