#ifndef GRAPH_JRB_H
#define GRAPH_JRB_H

#include "dllist.h"
#include "fields.h"
#include "jval.h"
#include "jrb.h"

#define true 1
#define false 0
#define UNDIRECTED 0
#define DIRECTED 1
#define INT_MAX 2147483647
#define INFINITIVE_VALUE 10000000
#define max 1000
#define sizemax 1000

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();

void addVertex(Graph graph, int id, char *name);
void addEdge(Graph graph, int v1, int v2, double weight);
void *getVertex(Graph graph, int id);
int getNumOfV(Graph graph);

double getEdgeValue(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int getNumOfEdge(Graph graph);

int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);

// return 0: co chu trinh
// return 1: khong co chu trinh
int DAG(Graph graph);
int DFS_DAG(Graph graph, int start);

int topologicalSort(Graph graph, int *output);

int DFS(Graph graph, int start, int stop, int *path);
//BFS
int shortest_noWeight_path(Graph graph, int start, int stop, int *path);

//Dijisktra
double shortestPath(Graph graph, int start, int stop, int *path, int *numVertices);

void dropGraph(Graph graph);

//buslib
void addVertexbus(Graph graph, char *name, char *busLine);
void addEdgebus(Graph graph, char *v1, char *v2);
int indegreebus(Graph graph, char *v, char *output[]);
int outdegreebus(Graph graph, char *v, char *output[]);
int shortest_bus(Graph graph, char *s, char *t, char *path[]);

#endif /* GRAPH_JRB_H */
