#ifndef GRAPHCURSOR_H
#define GRAPHCURSOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "doublyLinkedList.h"
#include "graph.h"

typedef struct
{
    Graph* graph;
    Vertex* currentVertex;
} GraphCursor;


GraphCursor* createCursor(void);

GraphCursor* copyGraphCursor(GraphCursor* cursor);

void deleteCursor(GraphCursor** ptrToCursor);

void cursorSetCurrentVertex(GraphCursor *cursor, Graph* graph, Vertex* vertex);

int cursorAvailable(GraphCursor* cursor);
Edge* cursorEdgeAt(GraphCursor* cursor, int index);
Vertex* cursorAt(GraphCursor* cursor, int index);
void cursorMoveInto(GraphCursor* cursor, int index);
Vertex* cursorGetCurrentVertex(GraphCursor* cursor);
void* cursorGetCurrentData(GraphCursor* cursor);

void cursorDeleteCurrentVertex(GraphCursor *cursor);
void cursorDeleteEdgeAt(GraphCursor *cursor, int index);

#endif // GRAPHCURSOR_H
