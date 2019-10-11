#include "graph.h"


Graph* createGraph(void){
    Graph *newGraph = malloc(sizeof(Graph));
    if (newGraph == NULL) return NULL;

    newGraph->vertices = dllCreate();

    if (newGraph->vertices == NULL) return NULL;

    return newGraph;
}

void graphDelete(Graph** ptrToDeleteGraph){
    if(ptrToDeleteGraph == NULL)return;
    if(*ptrToDeleteGraph == NULL)return;
    clear(*ptrToDeleteGraph);

    free((*ptrToDeleteGraph)->vertices);
    free(*ptrToDeleteGraph);
    *ptrToDeleteGraph = NULL;

}

Vertex* addVertex(Graph *graph, char* name, void* data){

    if (graph == NULL) return NULL;
    if (name == NULL) return NULL;

    Vertex *newVertex = malloc(sizeof(Vertex));
    newVertex->data = data;

    //copy the name to give the owernership to the graph library
    newVertex->name  = malloc(strlen(name)+1);
    strcpy(newVertex->name, name);

    newVertex->ptrToNode = dllAddAfterTail(graph->vertices, newVertex);

    newVertex->edges = dllCreate();

    return newVertex;
}

void deleteVertex(Graph *graph, Vertex** ptrToDeleteVertex){
    if(graph == NULL)return;
    if(ptrToDeleteVertex == NULL)return;
    if(*ptrToDeleteVertex == NULL)return;


    free((*ptrToDeleteVertex)->name);
    dllDelete(&(*ptrToDeleteVertex)->edges);

    if((*ptrToDeleteVertex)->data != NULL)
    {
        free((*ptrToDeleteVertex)->data);//who is the owner of data?
    }

    dllDeleteNode(graph->vertices, (*ptrToDeleteVertex)->ptrToNode);
    (*ptrToDeleteVertex)->ptrToNode = NULL;

    free(*ptrToDeleteVertex);
    *ptrToDeleteVertex = NULL;
}

size_t numberOfVertexs(Graph* graph){
    if (graph == NULL) return 0;
    return dllNumberOfElements(graph->vertices);
}

Edge* createEdge(Vertex* from, Vertex* destination, bool directed){
    return createEdgeWithWeight(from, destination, 0, directed);
}

Edge* createEdgeWithWeight(Vertex* from, Vertex* destination,int weight, bool directed){
    if (from == NULL) return NULL;
    if (destination == NULL) return NULL;
    Edge *edge= malloc(sizeof(Edge));
    edge->destination=destination;
    edge->weight=weight;

    dllAddAfterTail(from->edges, edge);

    if (directed == UNDIRECTED){
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
    toDeleteEdge->weight = 0;
    dllDeleteNode(connectedVertex, toDeleteEdge);
    free(toDeleteEdge);
}

void vertexPrintConnections(Graph* graph, Vertex* pointOfView){
    if (graph == NULL) return;
    if (pointOfView->edges->head == NULL) return;
    
    DllNode* node = pointOfView->edges->head;
    while (node)
    {
        printf("Connected vertexes %s", ((Edge*)node->data)->destination->name);
        node = node->next;
    } 
}


Vertex* searchVertexByName(Graph* graph, char* name){
    if(name == NULL) return NULL;
    if(graph == NULL) return NULL;

    DllNode* tmp = graph->vertices->head;
   while (tmp)
   {
       if(strcmp(name, ((Vertex*)tmp->data)->name) == 0){          
            return (Vertex*)tmp->data;
       tmp=tmp->next;
   }

    return NULL;
}

void clear(Graph *graph)
{
    if(graph == NULL) return;


    
    
}

void clearFloatingVertexes(Graph* graph)
{
    if(graph == NULL) return;

}
