#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "lib/munit/munit.h"
#include "lib/graph/graph.h"
#include "lib/cursor/graphcursor.h"

#include "FileToGraph.h"


void bellmanFordAlg(Graph* graphToSearch, Vertex* start, Vertex* destination){
    if(graphToSearch == NULL) return;
    if(start == NULL) return;
    if(destination == NULL) return;

    //assigning infinity to all other vertexes excluding start vertex
    DllNode* vertexLoop = graphToSearch->vertices->head;
    int* pathValues = malloc(sizeof(int));
    while (vertexLoop)
    {
        if(start == vertexLoop){          
            vertexLoop->data=0;
       }
       else if(destination == vertexLoop){
           vertexLoop->data=NULL;
       }
        vertexLoop->data=INT_MAX;
        vertexLoop=vertexLoop->next;
    }

    //relaxing the edges
    vertexLoop = start;
    int aantalVertices = numberOfVertexs(graphToSearch);
    int teller = 0;
    while(vertexLoop){

        //do stuff with edge

        if(vertexLoop= graphToSearch->vertices->tail && teller < aantalVertices-1){
            vertexLoop=graphToSearch->vertices->head;
        }
        if(teller = aantalVertices){
            break;
        }

        vertexLoop=vertexLoop->next;
        teller= teller+1;
    }




}

typedef struct EdgeIteratorData
{
    DllNode* currentVertex;
    DllNode* currentEdge;
}EdgeIteratorData;

Edge* setEdgeIterator(EdgeIteratorData* edgeIteratorData, Vertex* startVertex)
{
    edgeIteratorData->currentVertex = startVertex->ptrToNode;
    edgeIteratorData->currentEdge = startVertex->edges->head;
    return (Edge*)edgeIteratorData->currentEdge->data;
}
Edge* nextEdge(EdgeIteratorData* edgeIteratorData)
{
    edgeIteratorData->currentEdge = edgeIteratorData->currentEdge->next;
    if(edgeIteratorData->currentEdge == NULL)
    {
        edgeIteratorData->currentVertex = edgeIteratorData->currentVertex->next;
        if(edgeIteratorData->currentVertex == NULL)
        {
            return NULL;
        }
        edgeIteratorData->currentEdge = ((Vertex*)edgeIteratorData->currentVertex->data)->edges->head;
    }
    return (Edge*)edgeIteratorData->currentEdge->data;
}
int main(int argc, char *argv[])
{
    Graph* graph = loadGraphFromFile("json/citiesShortestPath.json");
    if(graph == NULL) return 0;


    EdgeIteratorData edgeIteratorData;
    Edge* currentEdge = setEdgeIterator(&edgeIteratorData,graph->vertices->head->data);

    while(currentEdge)
    {
        printf("%d %s\n",currentEdge->weight,currentEdge->destination->name);
        currentEdge = nextEdge(&edgeIteratorData);
    }

    return 0;
}
