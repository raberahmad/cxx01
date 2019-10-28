#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lib/munit/munit.h"
#include "lib/graph/graph.h"
#include "lib/cursor/graphcursor.h"

#include "FileToGraph.h"

int main(int argc, char *argv[])
{
    Graph* graph = loadGraphFromFile("json/citiesShortestPath.json");
    if(graph == NULL) return 0;

    GraphCursor* cursor = createCursor();
    cursorSetCurrentVertex(cursor, graph, graph->vertices->head->data);



    return 0;
}

