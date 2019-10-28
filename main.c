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

int main(int argc, char *argv[])
{
    Graph* graph = loadGraphFromFile("json/citiesShortestPath.json");
    
    if(graph == NULL) return 0;

    GraphCursor* cursor = createCursor();
    cursorSetCurrentVertex(cursor, graph, graph->vertices->head->data);



    return 0;
}

