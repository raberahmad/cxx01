#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <doublyLinkedList.h>


typedef struct
{
char* name;
void* data;
DoublyLinkedList edges; 
} Vertex;

typedef struct
{
Vertex* destination; 
int weight;
} Edge;


typedef struct
{
DoublyLinkedList vertices;
} Graph;


Graph* createGraph(void);
void graphDelete(Graph** ptrToDeleteGraph);
Vertex* addVertex(char* name, void* data);
void deleteVertex(Vertex** ptrToDeleteVertex);
size_t numberOfVertexs(Graph* graph);
Edge* createEdge(Vertex* from, Vertex* destination, bool unDirected);
Edge* createEdge(Vertex* from, Vertex* destination,int weight, bool unDirected);
Edge* deleteEdge(Edge *toDeleteEdge, Vertex* connectedVertex);
void printConnections(Vertex* pointOfView);
Vertex* searchVertexByName(char* name);


#endif