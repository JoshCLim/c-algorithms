// COMP2521 Assignment 2

// ADT adapted from COMP2521 graph breadth-first-search exercise
// https://webcms3.cse.unsw.edu.au/COMP2521/22T3/resources/80232
//
// Interface for a Weighted digraph ADT where vertices are identified
// by integers between 0 and N - 1, where N is the number of vertices.

// Written by: Josh Lim (z5422179)
// Date: 12 Nov 2022

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <math.h>
#include <stdio.h>

typedef int Vertex;
typedef double Weight;

typedef struct graph *Graph;

typedef struct path
{
    double *dist;
    int *pred;
} Path;

/**
 * Creates a new graph with the given number of vertices and no edges.
 *
 * @param nV - the number of vertices
 * @return Graph - new graph with nV vertices and no edges
 */
Graph GraphNew(int nV);

/**
 * Frees all the memory allocated for the given graph.
 *
 * @param g - graph to free
 */
void GraphFree(Graph g);

/**
 * find the number of vertices in a given graph
 *
 * @param g - graph to count number of vertices in
 * @return int - number of vertices in Graph g
 */
int GraphNumVertices(Graph g);

/**
 * Adds a directed, weighted edge between two vertices to the given graph. If
 * the edge already exists, this function does nothing. Assumes that v != w.
 *
 * @param g - graph to add edge to
 * @param v - vertex that the edge is coming from
 * @param w - vertex that the edge is directed to
 * @param weight - weight of edge
 */
void GraphAddEdge(Graph g, Vertex v, Vertex w, Weight weight);

/**
 * Removes a directed edge between two vertices from the given graph.
 * If the edge does not exist, this function does nothing. Assumes that
 * v != w.
 *
 * @param g - graph to remove edge from
 * @param v - vertex that the edge is coming from
 * @param w - vertex that th edge is directed to
 */
void GraphRemoveEdge(Graph g, Vertex v, Vertex w);

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
Weight GraphIsAdjacent(Graph g, Vertex v, Vertex w);

/**
 * Finds the shortest path to all nodes in a graph from Vertex source.
 * Returns a predecessor and distance array.
 *
 * @param g - graph to find the shortest path within
 * @param source - source vertex to find the shortest path to every other vertex
 * @returns Path - a struct containing the resultant distance and
 *                 predecessor arrays
 */
Path GraphShortestPath(Graph g, Vertex source);

/**
 * Free a path struct
 *
 * @param p - Path struct to free
 */
void GraphFreePath(Path p);

/**
 * display a graph by printing it to a certain FILE stream
 *
 * @param g - Graph to display
 * @param fp - FILE stream to print graph display to
 */
void GraphDump(Graph g, FILE *fp);

#endif
