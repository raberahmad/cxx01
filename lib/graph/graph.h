#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../dll/doublyLinkedList.h"

#define UNDIRECTED 0
#define DIRECTED 1
typedef struct
{
    char* name;
    void* data;
    DoublyLinkedList *edges;
    DllNode* ptrToNode;
} Vertex;

typedef struct
{   
    Vertex* destination;
    int weight;
    DllNode* ptrToNode;
} Edge;

typedef struct
{
    DoublyLinkedList *vertices;
} Graph;

//create a new graph object
Graph* createGraph(void);

//delete a given graph object and all its children and set the pointer to NULL
void graphDelete(Graph** ptrToDeleteGraph);

//add a vertex(node) to a graph
Vertex* addVertex(Graph *graph, char *name, void* data);

//delete a vertex and set the pointer to NULL
void deleteVertex(Graph *graph,Vertex** ptrToDeleteVertex);

//returns the number of vertexes in a given graph
size_t numberOfVertexs(Graph* graph);

//creates a edge(connection) between vertexes, which can bo both directed or undirected
Edge* createEdge(Vertex* from, Vertex* destination, bool directed);

//creates a edge(connection) between vertexes, which can bo both directed or undirected. also a weight is added
Edge* createEdgeWithWeight(Vertex* from, Vertex* destination,int weight, bool directed);

//delete a edge
void deleteEdge(Graph* graph, Edge *toDeleteEdge, Vertex* connectedVertex);

//print a vertex and its connections
void vertexPrintConnections(Graph* graph, Vertex* pointOfView);

//returns the first vertex with the given name, if it don't exist it will return NULL
Vertex* searchVertexByName(Graph* graph, char* name);

//delete all vertexes and edges
void clear(Graph* graph);

//clear all vertexes that are not connected
void clearFloatingVertexes(Graph* graph);
#endif
