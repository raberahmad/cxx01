#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "read_json_graph.h"

typedef struct {
    char *currentChar;
    int lineNum;
    int charNum;
    // filled in case of error:
    char expected;
} currentToken;

static char *buffer; // buffer to store the content of the file

static char *errorMessage[] =
{
    "OK\n",
    "Error at (%d:%d): found \'%c\' but expected \'%c\'.\n",
    "Error at (%d:%d): found \'%c\' but expected a boolean (true or false).\n",
    "Error at (%d:%d): found \'%c\' but expected a digit (0..9).\n",
    "Error at (%d:%d): found \'%c\' but expected a hexadecimal digit (0..9, a..f, A..F).\n",
    "Error at (%d:%d): expected \"x\", \"y\" or \"color\".\n",
    "Error at (%d:%d): expected \"weight\" or \"color\".\n"
};

static void whitespace(currentToken *t)
{
    while (*t->currentChar == ' ' || *t->currentChar == '\t' || *t->currentChar == '\r' || *t->currentChar == '\n')
    {
        if (*t->currentChar == ' ') t->charNum++;
        // assume tab size = 4
        if (*t->currentChar == '\t') t->charNum = ((t->charNum + 4) / 4) * 4;
        if (*t->currentChar == '\n')
        {
            t->charNum = 0;
            t->lineNum++;
        }
        t->currentChar++;
    }
}

static void nextchar(currentToken *t)
{
    t->currentChar++;
    t->charNum++;
}

static parseError literal(currentToken *t, char *s)
{
    whitespace(t);
    for (size_t i = 0; i < strlen(s); i++)
    {
        if (*t->currentChar != s[i])
        {
            t->expected = s[i];
            return ERR_CHAR;
        }
        nextchar(t);
    }
    return OK;
}

static parseError literal2(currentToken *t, char *s1, char *s2)
{
    parseError res;
    if ((res = literal(t, s1)) != OK) return res;
    return literal(t, s2);
}

// boolean ::= 'true' | 'false'
static parseError boolean(currentToken *t, void *b)
{
    parseError res;
    whitespace(t);
    switch (*t->currentChar)
    {
        case 't':
            if ((res = literal(t, "true")) != OK) return res;
            *(bool *)b = true;
            return OK;
        case 'f':
            if ((res = literal(t, "false")) != OK) return res;
            *(bool *)b = false;
            return OK;
    }
    return ERR_BOOL;
}

// integer ::= {-} digit + {digit}
// digit ::= '0' | .. | '9'
static void digit(currentToken *t, int *i)
{
    *i = 10 * *i + *t->currentChar - '0';
    nextchar(t);
}
static parseError integer(currentToken *t, void *i)
{
    bool isNegative = false;
    whitespace(t);
    if (*t->currentChar == '-')
    {
        nextchar(t); // ignore minus
        isNegative = true;
    }
    if (!isdigit(*t->currentChar)) return ERR_INT;
    int *pi = (int *)i;
    *pi = 0;
    digit(t, i);
    while (isdigit(*t->currentChar)) digit(t, i);
    if (isNegative) *pi = -*pi;
    return OK;
}

// label ::= '"' + string + '"'
// string ::= char + {char}
// char ::= '?' /* ? = any character except " */
static parseError label(currentToken *t, void *c)
{
    parseError res;
    if ((res = literal(t, "\"")) != OK) return res;
    *(char **)c = t->currentChar;
    while (*t->currentChar != '\"' && *t->currentChar != '\0') nextchar(t);
    if (*t->currentChar == '\"')
    {
        *t->currentChar = '\0';
        nextchar(t);
    }
    return OK;
}

// color ::= '"#' + hexdigit + {hexdigit} + '"'
// hexdigit ::= '0' | .. | '9' | 'A' | ... | 'F' | 'a' | ... | 'f'
static int hexvalue(char c)
{
    if (isdigit(c)) return c - '0';
    if (isupper(c)) return 10 + c - 'A';
    return 10 + c - 'a';
}
static void hexdigit(currentToken *t, int *i)
{
    *i = 16 * *i + hexvalue(*t->currentChar);
    nextchar(t);
}
static parseError color(currentToken *t, void *i)
{
    parseError res;
    currentToken lookahead = *t;
    if (literal(&lookahead, "null") == OK)
    {
        *(int *)i = 0x97C2FC; // default color see issue #4
        return literal(t, "null");
    }
    if ((res = literal(t, "\"#")) != OK) return res;
    if (!isxdigit(*t->currentChar)) return ERR_HEX;
    *(int *)i = 0;
    hexdigit(t, i);
    while (isxdigit(*t->currentChar)) hexdigit(t, i);
    if ((res = literal(t, "\"")) != OK) return res;
    return OK;
}

typedef parseError (*readValue)(currentToken *t, void *v);
static parseError readNameValue(currentToken *t, char *name, readValue rv, void *v)
{
    parseError res;
    if ((res = literal2(t, name, ":")) != OK) return res;
    if ((res = rv(t, v)) != OK) return res;
    return OK;
}

// node ::= '{' + '"id"' + ':' + id + ',' + '"label"' + ':' + label + [',' + '"x" + ':' + x + ',' + '"y" + ':' + y] + [',' + '"color" + ':' + color] + '}'
static parseError readNode(currentToken *t, void **n)
{
    parseError res;
    nodeInfo *newNode = malloc(sizeof(nodeInfo));
    if (newNode == 0) exit(-1);
    newNode -> next = *(nodeInfo **)n;
    *n = newNode;
    if ((res = literal(t, "{")) != OK) return res;
    if ((res = readNameValue(t, "\"id\"", &integer, &newNode->id)) != OK) return res;
    if ((res = literal(t, ",")) != OK) return res;
    if ((res = readNameValue(t, "\"label\"", &label, &newNode->label)) != OK) return res;
    newNode->hasColor = false;
    while ((res = literal(t, ",")) == OK)
    {
        currentToken lookahead = *t;
        if (readNameValue(&lookahead, "\"color\"", &color, &newNode->color) == OK)
        {
            readNameValue(t, "\"color\"", &color, &newNode->color);
            newNode->hasColor = true;
        }
        else
        {
            currentToken lookahead = *t;
            int dummy;
            if (readNameValue(&lookahead, "\"x\"", &integer, &dummy) == OK)
                readNameValue(t, "\"x\"", &integer, &dummy);
            else
            {
                currentToken lookahead = *t;
                if (readNameValue(&lookahead, "\"y\"", &integer, &dummy) == OK)
                    readNameValue(t, "\"y\"", &integer, &dummy);
                else return ERR_NODE;
            }
        }
    }
    if ((res = literal(t, "}")) != OK) return res;
    return OK;
}

static parseError readEdge(currentToken *t, void **e)
{
    parseError res;
    edgeInfo *newEdge = malloc(sizeof(edgeInfo));
    if (newEdge == 0) exit(-1);
    newEdge -> next = *e;
    *e = newEdge;
    if ((res = literal(t, "{")) != OK) return res;
    if ((res = readNameValue(t, "\"from\"", &integer, &newEdge->from)) != OK) return res;
    if ((res = literal(t, ",")) != OK) return res;
    if ((res = readNameValue(t, "\"to\"", &integer, &newEdge->to)) != OK) return res;
    newEdge->hasWeight = false;
    newEdge->hasColor = false;
    while ((res = literal(t, ",")) == OK)
    {
        currentToken lookahead = *t;
        if (readNameValue(&lookahead, "\"weight\"", &integer, &newEdge->weight) == OK)
        {
            readNameValue(t, "\"weight\"", &integer, &newEdge->weight);
            newEdge->hasWeight = true;
        }
        else
        {
            currentToken lookahead = *t;
            if (readNameValue(&lookahead, "\"color\"", &color, &newEdge->color) == OK)
            {
                readNameValue(t, "\"color\"", &color, &newEdge->color);
                newEdge->hasColor = true;
            }
            else return ERR_EDGE;
        }
    }
    if ((res = literal(t, "}")) != OK) return res;
    return OK;
}

// nodelist ::= '"nodes"'+ ':' + '[' + node + {',' + node} + ']'
// edgelist ::= '"edges"'+ ':' + '[' + edge + {',' + edge} + ']'
typedef parseError (*readElement)(currentToken *t, void **info);
static parseError readList(currentToken *t, char *name, readElement re, void **n)
{
    parseError res;
    if ((res = literal2(t, name, ":")) != OK) return res;
    if ((res = literal(t, "[")) != OK) return res;
    *n = 0;
    do
    {
        if ((res = re(t, n)) != OK) return res;
    }
    while ((res = literal(t, ",")) == OK);
    if ((res = literal(t, "]")) != OK) return res;
    return OK;
}

// graph ::= '{' + nodelist + ',' + edgelist + ',' + directed + ',' + weighted + '}'
static parseError graph(currentToken *t, graphInfo *g)
{
    parseError res;
    if ((res = literal(t, "{")) != OK) return res;
    if ((res = readList(t, "\"nodes\"", &readNode ,(void**)&g->nodeStack)) != OK) return res;
    if ((res = literal(t, ",")) != OK) return res;
    if ((res = readList(t, "\"edges\"", &readEdge ,(void**)&g->edgeStack)) != OK) return res;
    if ((res = literal(t, ",")) != OK) return res;
    if ((res = readNameValue(t, "\"directed\"", &boolean, &g->isDirected)) != OK) return res;
    if ((res = literal(t, ",")) != OK) return res;
    if ((res = readNameValue(t, "\"weighted\"", &boolean, &g->isWeighted)) != OK) return res;
    if ((res = literal(t, "}")) != OK) return res;
    return OK;
}

static char *file2string(char *filename)
{
    char *buffer = 0;
    long length;
    FILE * f = fopen(filename, "rb");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }
    return buffer;
}

parseError parse(char *filename, graphInfo *info)
{
    currentToken c;
    c.lineNum = 1;
    c.charNum = 1;
    c.currentChar = buffer = file2string(filename);
    if (c.currentChar == 0)
    {
        fprintf(stderr, "Error reading file %s.\n", filename);
        exit(-1);
    }
    parseError res = graph(&c, info);
    if (res != OK)
    {
        fprintf(stderr, errorMessage[res], c.lineNum, c.charNum, *c.currentChar, c.expected);
    }
    return res;
}

void freeGraphInfo(graphInfo *info)
{
    while (info->edgeStack != 0)
    {
        edgeInfo *e = info->edgeStack->next;
        free(info->edgeStack);
        info->edgeStack = e;
    }
    while (info->nodeStack != 0)
    {
        nodeInfo *n = info->nodeStack->next;
        free(info->nodeStack);
        info->nodeStack = n;
    }
    free(buffer);
}
