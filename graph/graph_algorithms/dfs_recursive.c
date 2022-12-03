#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../graph_undirected_unweighted.h"

static void dfs(Graph g, int src, bool *visited);

void depthFirstSearch(Graph g, int src) {
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));
	dfs(g, src, visited);
	free(visited);
	return;
}

static void dfs(Graph g, int src, bool *visited) {
	visited[src] = true;

    // DO STUFF
	printf("%d ", src);
    //

	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (GraphIsAdjacent(g, src, i) && !visited[i]) {
			dfs(g, i, visited);
		}
	}
}
