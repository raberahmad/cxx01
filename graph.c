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

    Vertex *newVertex = malloc(sizeof(Vertex));
    newVertex->data = data;
    newVertex->name = name;
    dllAddAfterTail(graph->vertices, newVertex);
    
    return newVertex;
}

void deleteVertex(Graph *graph, Vertex** ptrToDeleteVertex){
    if (graph != NULL && ptrToDeleteVertex != NULL){
        dllDeleteNode(graph, *ptrToDeleteVertex);
        free(*ptrToDeleteVertex);
        *ptrToDeleteVertex = NULL;
    }
}

size_t numberOfVertexs(Graph* graph){
    if (graph == NULL) return NULL;
    return dllNumberOfElements(graph->vertices);
}

Edge* createEdge(Vertex* from, Vertex* destination, bool unDirected){
    createEdgeWithWeight(from, destination, NULL, unDirected);
}

Edge* createEdgeWithWeight(Vertex* from, Vertex* destination,int weight, bool unDirected){
    if (from == NULL) return NULL;
    if (destination == NULL) return NULL; 
    Edge *edge= malloc(sizeof(Edge)); 
    edge->destination=destination;
    edge->weight=weight;
    
    dllAddAfterTail(from->edges, edge);
    
    if (unDirected == true){
        Edge *edge2= malloc(sizeof(Edge));
        edge->destination=from;
        edge->weight=weight;

        dllAddAfterTail(destination->edges, edge2);
    }
    return edge;
}

void deleteEdge(Graph* graph, Edge *toDeleteEdge, Vertex* connectedVertex){
    if (graph == NULL) return ;
    if (toDeleteEdge == NULL) return;
    if (connectedVertex == NULL) return;

    toDeleteEdge->destination = NULL;
    toDeleteEdge->weight=NULL;
    dllDeleteNode(connectedVertex, toDeleteEdge);
    free(toDeleteEdge);
}

void printConnections(Graph* graph, Vertex* pointOfView){
    //
}


Vertex* searchVertexByName(Graph* graph, char* name){
    return NULL;
}
