#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Stack.h"
#include "../graph_undirected_unweighted.h"

static void dfs(Graph g, int src, bool *visited);

void depthFirstSearch(Graph g, int src) {
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));
    
    Stack s = StackNew();

    StackPush(s, src);

    while (!StackIsEmpty(s)) {
        Vertex curr = StackPop(s);
        visited[curr] = true;

        // do stuff
        printf("%d ", curr);

        for (int i = GraphNumVertices - 1; i >= 0; i--) {
            if (GraphIsAdjacent(g, curr, i) && !visited[i]) {
                StackPush(s, i);
            }
        }
    }

    free(visited);
    return;
}
