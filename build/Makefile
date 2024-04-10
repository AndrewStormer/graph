CC=gcc
CFLAGS = -Wall -Werror -I.
all: graph

graph : main.o graph.o bfs.o dfs.o dijkstra.o bellmanford.o mst.o
	@echo Linking...
	$(CC) $(CFLAGS) -o graph main.o graph.o bfs.o dfs.o mst.o dijkstra.o bellmanford.o -lm
	@echo Done!

main.o: ../src/main.c ../include/graph.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c ../src/main.c

graph.o : ../src/graph.c ../include/graph.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c ../src/graph.c

bfs.o : ../src/bfs.c ../include/bfs.h 
	@echo Compiling...
	$(CC) $(CFLAGS) -c ../src/bfs.c

dfs.o : ../src/dfs.c ../include/dfs.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c ../src/dfs.c

mst.o : ../src/mst.c ../include/mst.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c ../src/mst.c

dijkstra.o : ../src/dijkstra.c ../include/dijkstra.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c ../src/dijkstra.c

bellmanford.o : ../src/bellmanford.c ../include/bellmanford.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c ../src/bellmanford.c


clean:
	$(RM) graph *.o *~
	@echo All clean!
