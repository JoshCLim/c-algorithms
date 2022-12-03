#include <stdio.h>
#include <stdlib.h>

#include "../graph_undirected_unweighted.h"
#include "../Queue.h"

// Breadth first search but returns an array containing 
// the distance between src and each vertex.
// For an undirected, unweighted graph.
int *breadthFirstSearch(Graph g, int src) {
	int *dist = calloc(GraphNumVertices(g), sizeof(int));
  for (int i = 0; i < GraphNumVertices(g); i++) {
    dist[i] = -1;
  }
  Queue q = QueueNew();

	QueueEnqueue(q, src);
	dist[src] = 0;

	while (!QueueIsEmpty(q)) {
		Vertex curr = QueueDequeue(q);
		// printf("%d ", curr);

		for (Vertex i = 0; i < GraphNumVertices(g); i++) {
			if (GraphIsAdjacent(g, curr, i) && dist[i] == -1) {
				dist[i] = dist[curr] + 1;
				QueueEnqueue(q, i);
			}
		}
	}

	QueueFree(q);
  return dist;
}
