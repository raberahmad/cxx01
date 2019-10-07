#include "graph.h"


Graph* createGraph(void){
    Graph *newGraph = malloc(sizeof(Graph));
    if (newGraph == NULL) return NULL;
    
    DoublyLinkedList *dllist = dllCreate();
    newGraph->vertices = dllist;

    if (dllist == NULL) return NULL;
    if (newGraph->vertices == NULL) return NULL;

    return newGraph;
}

void graphDelete(Graph** ptrToDeleteGraph){
    //todelete
}

Vertex* addVertex(Graph *graph, char* name, void* data){

    if (graph == NULL) return NULL;
    if (name == NULL) return NULL;
    if (data == NULL) return NULL;

    Vertex *newVertex = malloc(sizeof(Vertex));
    newVertex->data = data;
    newVertex->name = name;
    DoublyLinkedList *vdlist = dllCreate();
    dllAddAfterTail(graph->vertices, newVertex);
    
    return newVertex;
}

void deleteVertex(Vertex** ptrToDeleteVertex){
    
}

size_t numberOfVertexs(Graph* graph){
    if (graph == NULL) return NULL;
    return dllNumberOfElements(graph->vertices);
}

Edge* createEdge(Vertex* from, Vertex* destination, bool unDirected){
    if (from == NULL) return NULL;
    if (destination == NULL) return NULL; 
    Edge *edge= malloc(sizeof(Edge)); 
    edge->destination=destination;
    edge->weight=NULL;
    
    dllAddAfterTail(from->edges, edge);
    
    if (unDirected == true){
        Edge *edge2= malloc(sizeof(Edge));
        edge->destination=from;
        edge->weight=NULL;

        dllAddAfterTail(destination->edges, edge2);
    }
    return edge;
}

Edge* createEdgeWithWeight(Graph* graph, Vertex* from, Vertex* destination,int weight, bool unDirected){
    return NULL;
}

Edge* deleteEdge(Graph* graph, Edge *toDeleteEdge, Vertex* connectedVertex){
    return NULL;
}

void printConnections(Graph* graph, Vertex* pointOfView){

}
Vertex* searchVertexByName(Graph* graph, char* name){
    return NULL;
}
