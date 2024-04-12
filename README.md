# Graph
## Getting Started

### Create a new build directory: 

mkdir build && cd build

### Create a .txt file in this format:

<vertex_count>

<edge_count>

<vertex_number> <edge_number> <edge_weight>

#### Note: The above line needs to be repeated edge_count times

### CMake: cmake ..

### Make and Run: make && ./<file_name>


## Use Cases:

```
int main(void) {
    int vertex_count;
    int edge_count;
    vertex_t *graph = directed_graph_initalize("vertexlist.txt", &vertex_count, &edge_count);
}
```