#include "graphcursor.h"


GraphCursor *createCursor()
{
    GraphCursor* cursor = malloc(sizeof (GraphCursor));
    cursor->graph = NULL;
    cursor->currentVertex = NULL;
    return cursor;
}

GraphCursor *copyGraphCursor(GraphCursor *cursor)
{
    GraphCursor* copy = malloc(sizeof (GraphCursor));
    copy->graph = cursor->graph;
    copy->currentVertex = cursor->currentVertex;
    return copy;
}

void cursorSetCurrentVertex(GraphCursor *cursor, Graph *graph, Vertex *vertex)
{
    if(graph == NULL) return;
    if(vertex == NULL) return;
    if(cursor == NULL) return;

    cursor->graph = graph;
    cursor->currentVertex = vertex;
}

void deleteCursor(GraphCursor **ptrToCursor)
{
    if(ptrToCursor == NULL)return;
    if(*ptrToCursor == NULL)return;
    free(*ptrToCursor);
}

int cursorAvailable(GraphCursor *cursor)
{
    if(cursor == NULL)return 0;
    if(cursor->currentVertex == NULL)return 0;

    return dllNumberOfElements(cursor->currentVertex->edges);
}

Vertex *cursorAt(GraphCursor *cursor, int index)
{
    if(cursor == NULL)return 0;
    if(cursor->currentVertex == NULL)return 0;

    DllNode* node = cursor->currentVertex->edges->head;

    int i = 0;
    while(node)
    {
        if(i == index)
        {
            return ((Edge*)node->data)->destination;
        }
        i++;
        node = node->next;
    }
    return NULL;
}
Edge *cursorEdgeAt(GraphCursor *cursor, int index)
{
    if(cursor == NULL)return 0;
    if(cursor->currentVertex == NULL)return 0;

    DllNode* node = cursor->currentVertex->edges->head;

    int i = 0;
    while(node)
    {
        if(i == index)
        {
            return ((Edge*)node->data);
        }
        i++;
        node = node->next;
    }
    return NULL;
}

void cursorMoveInto(GraphCursor *cursor, int index)
{
    if(cursor == NULL)return;
    if(cursor->currentVertex == NULL)return;

    DllNode* node = cursor->currentVertex->edges->head;

    int i = 0;
    while(node)
    {
        if(i == index)
        {
            cursor->currentVertex = ((Edge*)node->data)->destination;
            return;
        }
        i++;
        node = node->next;
    }
}

Vertex *cursorGetCurrentVertex(GraphCursor *cursor)
{
    if(cursor == NULL) return NULL;
    return cursor->currentVertex;
}

void* cursorGetCurrentData(GraphCursor *cursor)
{
    if(cursor == NULL) return NULL;
    return cursor->currentVertex->data;
}


void cursorDeleteCurrentVertex(GraphCursor *cursor)
{
    if(cursor == NULL) return;
    if(cursor->currentVertex == NULL)return;

    deleteVertex(cursor->graph, &cursor->currentVertex);
    cursor->currentVertex = NULL;
}

void cursorDeleteEdgeAt(GraphCursor *cursor, int index)
{
    if(cursor == NULL)return;
    if(cursor->currentVertex == NULL)return;

    DllNode* node = cursor->currentVertex->edges->head;

    int i = 0;
    while(node)
    {
        if(i == index)
        {
            deleteEdge(cursor->graph, (Edge*)node->data, cursor->currentVertex);
        }
        i++;
        node = node->next;
    }
}
