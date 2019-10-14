#include "FileToGraph.h"

void printNodes(nodeInfo *n)
{
    if (n->next != 0) printNodes(n->next);
    else printf("Nodes:\n");
    printf("id = %d", n->id);
    printf(", label = %s", n->label);
    if (n->hasColor) printf(", color = #%06X", n->color);
    printf("\n");
}

void printEdges(edgeInfo *e)
{
    if (e->next != 0) printEdges(e->next);
    else printf("Edges:\n");
    printf("from = %d", e->from);
    printf(", to = %d", e->to);
    if (e->hasWeight) printf(", weight = %d", e->weight);
    if (e->hasColor) printf(", color = #%06X", e->color);
    printf("\n");
}

parseError testParse(char *filename)
{
    printf("\nParsing %s\n", filename);
    graphInfo gi;
    parseError res = parse(filename, &gi);
    // You have to create your own graph here using variable gi.
    // In this program the graph information is only printed.
    printf("directed = %d\n", gi.isDirected);
    printf("weighted = %d\n", gi.isWeighted);
    if (gi.nodeStack != 0) printNodes(gi.nodeStack);
    if (gi.edgeStack != 0) printEdges(gi.edgeStack);
    // Free the memory allocated by the parser by calling freeGraphInfo.
    freeGraphInfo(&gi);
    return res;
}
 bool intEqual(void *d1, void *d2)
 {
    if (d1 == 0 || d2 == 0) return d1 == 0 && d2 == 0;
    return *(int*)(((Vertex*)d1)->data) == *(int*)d2;
 }
Graph* loadGraphFromFile(char* filename)
{
    printf("\nParsing %s\n", filename);
    graphInfo gi;
    parseError res = parse(filename, &gi);

    // You have to create your own graph here using variable gi.
    // In this program the graph information is only printed.
    Graph* graph = createGraph();

    nodeInfo* currentNode = gi.nodeStack;
    while(currentNode != NULL)
    {
        int* nodeId = malloc(sizeof (int));
        *nodeId = currentNode->id;
        addVertex(graph,"",nodeId);
        currentNode = currentNode->next;
    }

    edgeInfo* currentEdge = gi.edgeStack;
    while(currentEdge != NULL)
    {
        DllNode* sourceNode = dllFindFirst(graph->vertices,intEqual, &currentEdge->from);
        DllNode* destinationNode = dllFindFirst(graph->vertices,intEqual, &currentEdge->to);
        if((sourceNode == NULL)||(destinationNode == NULL))
        {
            printf("error connecting edge\n");
            graphDelete(&graph);
            return NULL;
        }

        createEdge(sourceNode->data, destinationNode->data, UNDIRECTED);

        currentEdge = currentEdge->next;
    }

    printf("directed = %d\n", gi.isDirected);
    printf("weighted = %d\n", gi.isWeighted);
    if (gi.nodeStack != 0) printNodes(gi.nodeStack);
    if (gi.edgeStack != 0) printEdges(gi.edgeStack);
    // Free the memory allocated by the parser by calling freeGraphInfo.
    freeGraphInfo(&gi);
    return graph;
}
int testGraphRead(void)
{
    int res = 0;
    res += testParse("json/circleOfThree.json");
//    res += testParse("json/circleOfThreeSolved.json");
//    res += testParse("json/cities.json");
//    res += testParse("json/citiesColor.json");
//    res += testParse("json/citiesShortestPath.json");
//    res += testParse("json/provincesNetherlands.json");
//    res += testParse("json/weightedDiGraph.json");
//    res += testParse("json/testUnweightedColored.json");
//    res += testParse("json/testUnweightedColoredXY.json");
//    res += testParse("json/citiesColorXY.json");
//    res += testParse("json/colorNULL.json");
//    res += testParse("json/testNegativeWeighted.json");
    return res;
}
