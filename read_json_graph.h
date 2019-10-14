#ifndef READ_JSON_GRAPH_H_
#define READ_JSON_GRAPH_H_
#include <stdbool.h>

typedef struct nodeInfo
{
    int id;
    char* label;
    bool hasColor;
    int color;
    struct nodeInfo *next;
} nodeInfo;

typedef struct edgeInfo
{
    int from;
    int to;
    bool hasWeight;
    int weight;
    bool hasColor;
    int color;
    struct edgeInfo *next;
} edgeInfo;

typedef struct
{
    nodeInfo* nodeStack;
    edgeInfo* edgeStack;
    bool isDirected;
    bool isWeighted;
} graphInfo;

typedef enum {OK, ERR_CHAR, ERR_BOOL, ERR_INT, ERR_HEX, ERR_NODE, ERR_EDGE} parseError;

parseError parse(char *filename, graphInfo *info);
void freeGraphInfo(graphInfo *info);
#endif
