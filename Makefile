CC=gcc
CFLAGS = -Wall -Werror -c -g -std=c11 -I.
LDFLAGS = -lm -L.

%.o : %.c 
	@echo Compiling $^...
	@$(CC) $(CFLAGS) $^

graph : main.o mst.o graph.o bfs.o dfs.o dijkstra.o bellmanford.o
	@echo Linking $@ ...
	@$(CC) $^ $(LDFLAGS) -o $@
	@echo Done!

clean : 
	@rm -rf *.o
	@rm -rf graph
	@echo All Clean!