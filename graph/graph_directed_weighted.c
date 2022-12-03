// COMP2521 Assignment 2

// adapted from COMP2521 exercise breadth-first-search given files
// https://webcms3.cse.unsw.edu.au/COMP2521/22T3/resources/80232
//
// Implementation of the weighted digraph ADT

// Written by: Josh Lim (z5422179)
// Date: 12 Nov 2022

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph_directed_weighted.h"

struct graph {
	int nV;
	Weight **edges;
};

// function prototypes
static bool validVertex(Graph g, Vertex v);
static Graph doGraphNew(int nV);

/**
 * Creates a new graph with the given number of vertices and no edges.
 * 
 * @param nV - the number of vertices
 * @return Graph - new graph with nV vertices and no edges
 */
Graph GraphNew(int nV) {
	assert(nV > 0);
	
	Graph g = doGraphNew(nV);
	for (Vertex v = 0; v < nV; v++) {
		for (Vertex w = 0; w < nV; w++) {
			g->edges[v][w] = -INFINITY;
		}
	}
	
	return g;
}

/**
 * creates a new graph with number of vertices nV
 * 
 * @param nV - number of vertices in graph
 * @return Graph - pointer to struct graph allocated
 */
static Graph doGraphNew(int nV) {
	Graph g = malloc(sizeof(*g));
	if (g == NULL) {
		fprintf(stderr, "GraphNew: Insufficient memory!\n");
		exit(EXIT_FAILURE);
	}
	
	g->nV = nV;
	
	g->edges = malloc(nV * sizeof(Weight *));
	if (g->edges == NULL) {
		fprintf(stderr, "GraphNew: Insufficient memory!\n");
		exit(EXIT_FAILURE);
	}
	for (Vertex v = 0; v < nV; v++) {
		g->edges[v] = malloc(nV * sizeof(Weight));
		if (g->edges[v] == NULL) {
			fprintf(stderr, "GraphNew: Insufficient memory!\n");
			exit(EXIT_FAILURE);
		}
	}
	
	return g;
}

/**
 * Frees all the memory allocated for the given graph.
 * 
 * @param g - graph to free
 */
void GraphFree(Graph g) {
	assert(g != NULL);
	
	for (Vertex v = 0; v < g->nV; v++) {
		free(g->edges[v]);
	}
	free(g->edges);
	free(g);
}

/**
 * find the number of vertices in a given graph
 * 
 * @param g - graph to count number of vertices in
 * @return int - number of vertices in Graph g
 */
int GraphNumVertices(Graph g) {
	assert(g != NULL);
	
	return g->nV;
}

/**
 * Adds a directed, weighted edge between two vertices to the given graph. If
 * the edge already exists, this function does nothing. Assumes that v != w.
 * 
 * @param g - graph to add edge to
 * @param v - vertex that the edge is coming from
 * @param w - vertex that the edge is directed to
 * @param weight - weight of edge
 */
void GraphAddEdge(Graph g, Vertex v, Vertex w, Weight weight) {
	assert(g != NULL);
	assert(validVertex(g, v));
	assert(validVertex(g, w));
	assert(v != w);
	
	g->edges[v][w] = weight;
}

/**
 * Removes a directed edge between two vertices from the given graph.
 * If the edge does not exist, this function does nothing. Assumes that
 * v != w.
 * 
 * @param g - graph to remove edge from
 * @param v - vertex that the edge is coming from
 * @param w - vertex that th edge is directed to
 */
void GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
	assert(g != NULL);
	assert(validVertex(g, v));
	assert(validVertex(g, w));
	assert(v != w);
	
	g->edges[v][w] = false;
}

/**
 * Checks whether there is an edge from Vertex v to Vertex w in the given
 * graph. Returns the weight of the edge if it exists, otherwise -INFINITY.
 * 
 * @param g - graph to check if edge is in
 * @param v - vertex that the edge is coming from
 * @param w - vertex that the edge is directed to
 * @returns Weight - weight of the edge from v to w,
 *                   or -INFINITY if it does not exist
 */
Weight GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
	assert(g != NULL);
	assert(validVertex(g, v));
	assert(validVertex(g, w));
	
	return g->edges[v][w];
}

/**
 * Finds the shortest path to all nodes in a graph from Vertex source.
 * Returns a predecessor and distance array.
 * 
 * @param g - graph to find the shortest path within
 * @param source - source vertex to find the shortest path to every other vertex
 * @returns Path - a struct containing the resultant distance and 
 *                 predecessor arrays
 */
Path GraphShortestPath(Graph g, Vertex source) {
	// using Dijkstra's algorithm
	Path p;
	p.dist = malloc(sizeof(double) * GraphNumVertices(g));
	p.pred = malloc(sizeof(int) * GraphNumVertices(g));
	for (int i = 0; i < GraphNumVertices(g); i++) {
		p.dist[i] = INFINITY;
		p.pred[i] = -1;
	}

	// visited array
	int *vSet = calloc(GraphNumVertices(g), sizeof(int));
	// keep track of number of vertices visited
	int vCount = 0;

	p.dist[source] = 0;

	while (vCount < GraphNumVertices(g)) {
		// find v in vSet that has min dist[v]
		Weight minDist = INFINITY;
		int minVertex = -1;
		for (int i = 0; i < GraphNumVertices(g); i++) {
			if (vSet[i] == 0 && p.dist[i] < minDist) {
				minDist = p.dist[i];
				minVertex = i;
			}
		}

		// all vertices have been visited
		if (minVertex == -1) break;

		for (int i = 0; i < GraphNumVertices(g); i++) {
			Weight weight = GraphIsAdjacent(g, minVertex, i);
			if (weight != -INFINITY) {
				if (p.dist[minVertex] + weight < p.dist[i]) {
					// edge relaxation
					p.dist[i] = p.dist[minVertex] + weight;
					p.pred[i] = minVertex;
				}
			}
		}

		// mark minVertex as 'visited'
		vSet[minVertex] = 1;
		vCount++;
	}

	free(vSet);

	return p;
}

/**
 * Free a path struct
 * 
 * @param p - Path struct to free
 */
void GraphFreePath(Path p) {
	free(p.dist);
	free(p.pred);
}

/**
 * display a graph by printing it to a certain FILE stream
 * 
 * @param g - Graph to display
 * @param fp - FILE stream to print graph display to
 */
void GraphDump(Graph g, FILE *fp) {
	assert(g != NULL);
	assert(fp != NULL);
	
	fprintf(fp, "\nGraph: nV = %d\n", g->nV);
	fprintf(fp, "Edges:\n");
	for (Vertex v = 0; v < g->nV; v++) {
		fprintf(fp, "%2d:", v);
		for (Vertex w = 0; w < g->nV; w++) {
			if (g->edges[v][w] >= 0) {
				fprintf(fp, " %d-%d (%.02lf)", v, w, g->edges[v][w]);
			}
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	for (Vertex v = 0; v < g->nV; v++) {
		for (Vertex w = 0; w < g->nV; w++) {
			fprintf(fp, " %.02lf |", g->edges[v][w]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
}

/**
 * checks if a given vertex is valid withint a graph
 * 
 * @param g - Graph to check
 * @param v - vertex to validate
 * @return true - Graph contains that vertex
 * @return false - Graph does not contain that vertex
 */
static bool validVertex(Graph g, Vertex v) {
	return (v >= 0 && v < g->nV);
}
