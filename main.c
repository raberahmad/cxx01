#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "lib/munit/munit.h"
#include "lib/graph/graph.h"
#include "lib/cursor/graphcursor.h"

#include "FileToGraph.h"

//this structure is made to access the edges like a continously linked list list
typedef struct EdgeIteratorData
{
    DllNode* currentVertex;
    DllNode* currentEdge;
}EdgeIteratorData;
//this method starts the EdgeIterator at a certain vertex
Edge* setEdgeIterator(EdgeIteratorData* edgeIteratorData, Vertex* startVertex)
{
    edgeIteratorData->currentVertex = startVertex->ptrToNode;
    edgeIteratorData->currentEdge = startVertex->edges->head;

    while(edgeIteratorData->currentEdge == NULL)
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
//this method returns the next edge
Edge* nextEdge(EdgeIteratorData* edgeIteratorData)
{
    edgeIteratorData->currentEdge = edgeIteratorData->currentEdge->next;
    while(edgeIteratorData->currentEdge == NULL)
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
typedef struct bellmanFordVertexData
{
    int distance;
    Vertex* previous;
}bellmanFordVertexData;

void bellmanFordAlg(Graph* graphToSearch, Vertex* start, Vertex* destination){
    if(graphToSearch == NULL) return;
    if(start == NULL) return;
    if(destination == NULL) return;

    //assigning infinity to all other vertexes excluding start vertex
    DllNode* vertexIterator = graphToSearch->vertices->head;
    while (vertexIterator)
    {
        Vertex* vertex = vertexIterator->data;
        vertex->data = malloc(sizeof(bellmanFordVertexData));
        if(start->ptrToNode == vertexIterator){
            ((bellmanFordVertexData*)vertex->data)->distance = 0;
            ((bellmanFordVertexData*)vertex->data)->previous = NULL;
        }
        else{
            ((bellmanFordVertexData*)vertex->data)->distance = INT_MAX;
            ((bellmanFordVertexData*)vertex->data)->previous = NULL;
        }
        vertexIterator = vertexIterator->next;
    }

    //relaxing the edges
    vertexIterator = graphToSearch->vertices->head;
    EdgeIteratorData edgeIteratorData;
    while(vertexIterator){
        Edge* currentEdge = setEdgeIterator(&edgeIteratorData,graphToSearch->vertices->head->data);

        while(currentEdge){
            Vertex* sourceVertex = ((Vertex*)edgeIteratorData.currentVertex->data);
            Vertex* destinationVertex = currentEdge->destination;
            bellmanFordVertexData* sourceData = sourceVertex->data;
            bellmanFordVertexData* destinationData = destinationVertex->data;

            int vertexDistance = sourceData->distance;
            int destinationVertexDistance = destinationData->distance;
            int tmpDistance = vertexDistance + currentEdge->weight;

            if(vertexDistance != INT_MAX)
            {
                if(tmpDistance < destinationVertexDistance){
                    destinationData->distance = tmpDistance;
                    destinationData->previous = sourceVertex;
                    printf("- %d %s  %s\n",currentEdge->weight,sourceVertex->name, destinationVertex->name);
                }
            }
            currentEdge = nextEdge(&edgeIteratorData);
        }
        vertexIterator = vertexIterator->next;
    }

    //negative loop check
    bool negativeCycleFound = false;
    Edge* currentEdge = setEdgeIterator(&edgeIteratorData,graphToSearch->vertices->head->data);

    while(currentEdge){
        Vertex* sourceVertex = ((Vertex*)edgeIteratorData.currentVertex->data);
        Vertex* destinationVertex = currentEdge->destination;
        bellmanFordVertexData* sourceData = sourceVertex->data;
        bellmanFordVertexData* destinationData = destinationVertex->data;

        if(sourceData->distance + currentEdge->weight < destinationData->distance)
        {
            printf("error the graph contains a negative cycle\n");
            negativeCycleFound = true;
            break;
        }

        currentEdge = nextEdge(&edgeIteratorData);
    }

    //print the results
    if(negativeCycleFound == false)
    {
        Vertex* resultPath = destination;
        while(resultPath)
        {
            printf("<- %s ",resultPath->name);
            resultPath = ((bellmanFordVertexData*)resultPath->data)->previous;
        }
    }


    //loop through the vertexes to free the used data
    vertexIterator = graphToSearch->vertices->head;
    while(vertexIterator){
        Vertex* vertex = vertexIterator->data;
        //printf("%s  %d\n",vertex->name,*((int*)vertex->data));
        free(vertex->data);
        vertexIterator = vertexIterator->next;
    }
}


int main(int argc, char *argv[])
{
    Graph* graph = loadGraphFromFile("json/citiesShortestPath2.json");
    if(graph == NULL) return 0;


    bellmanFordAlg(graph,searchVertexByName(graph,"Amsterdam"), searchVertexByName(graph,"Florence"));

    return 0;
}
