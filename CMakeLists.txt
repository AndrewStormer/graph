cmake_minimum_required(VERSION 3.5)
project(main)

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(graph SHARED src/graph.c)
add_library(bfs SHARED src/graph.c src/bfs.c)
add_library(dfs SHARED src/graph.c src/dfs.c)
add_library(mst SHARED src/graph.c src/mst.c)
add_library(dijkstra SHARED src/graph.c src/mst.c src/dijkstra.c)
add_library(bellmanford SHARED src/graph.c src/mst.c src/dijkstra.c src/bellmanford.c)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} m graph dijkstra)





