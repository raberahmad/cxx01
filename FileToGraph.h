#include <stdio.h>
#include <stdbool.h>
#include "read_json_graph.h"
#include "lib/graph/graph.h"
void printNodes(nodeInfo *n);

void printEdges(edgeInfo *e);


parseError testParse(char *filename);

int testGraphRead(void);

Graph* loadGraphFromFile(char* filePath);
