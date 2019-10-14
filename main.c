#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "FileToGraph.h"
#include "graph.h"
#include "graphcursor.h"

int main(int argc, char *argv[])
{
    Graph* graph = loadGraphFromFile("json/cities.json");
    if(graph == NULL) return 0;

    GraphCursor* cursor = createCursor();

    cursorSetCurrentVertex(cursor, graph, graph->vertices->head->data);

    return 0;
}

