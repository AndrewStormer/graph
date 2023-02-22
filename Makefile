CC=gcc
CFLAGS = -Wall -Werror -I.
all: graph

graph : main.o graph.o bfs.o dfs.o dijkstra.o bellmanford.o mst.o
	@echo Linking...
	$(CC) $(CFLAGS) -o graph main.o graph.o bfs.o dfs.o mst.o dijkstra.o bellmanford.o -lm
	@echo Done!

main.o: main.c graph.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c main.c

graph.o : graph.c graph.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c graph.c

bfs.o : bfs.c bfs.h 
	@echo Compiling...
	$(CC) $(CFLAGS) -c bfs.c

dfs.o : dfs.c dfs.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c dfs.c

mst.o : mst.c mst.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c mst.c

dijkstra.o : dijkstra.c dijkstra.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c dijkstra.c

bellmanford.o : bellmanford.c bellmanford.h
	@echo Compiling...
	$(CC) $(CFLAGS) -c bellmanford.c


clean:
	$(RM) graph *.o *~
	@echo All clean!
