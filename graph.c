#include "graph.h"


Graph* createGraph(void){
    Graph *newGraph = malloc(sizeof(Graph));
    if (newGraph == NULL) return NULL;
    DoublyLinkedList *dllist = dllCreate();
  //  newGraph->vertices = dllist;

    
}

void graphDelete(Graph** ptrToDeleteGraph){

}

Vertex* addVertex(char* name, void* data){
    return NULL;
}

void deleteVertex(Vertex** ptrToDeleteVertex){
    
}

size_t numberOfVertexs(Graph* graph){
    return NULL;
}

Edge* createEdge(Vertex* from, Vertex* destination, bool unDirected){
    return NULL;
}

Edge* createEdgeWithWeight(Vertex* from, Vertex* destination,int weight, bool unDirected){
    return NULL;
}

Edge* deleteEdge(Edge *toDeleteEdge, Vertex* connectedVertex){
    return NULL;
}

void printConnections(Vertex* pointOfView){

}
Vertex* searchVertexByName(char* name){
    return NULL;
}
