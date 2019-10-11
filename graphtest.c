
#include "munit.h"
#include "graph.h"
#include "graphcursor.h"
#include <stdio.h>

MunitResult graphCreate_test(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;
    Graph *graph = createGraph();
    munit_assert_not_null(graph);
    munit_assert_not_null(graph->vertices);

    munit_assert_null(graph->vertices->head);
    munit_assert_null(graph->vertices->tail);

    graphDelete(&graph);

    return MUNIT_OK;
}

MunitResult graphDelete_empty(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;
    Graph *graph = createGraph();

    munit_assert_not_null(graph);

    graphDelete(&graph);

    munit_assert_null(graph);

    return MUNIT_OK;
}

MunitResult addVertex_test(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    Graph* graph1 = createGraph();
    Graph* graph2 = createGraph();

    int testdata = 1;
    Vertex* vertex1_1 = addVertex(graph1,"testname",NULL);
    Vertex* vertex1_2 = addVertex(graph1,"vertex2",&testdata);
    char* name = "test";
    Vertex* vertex1_3 = addVertex(graph1,name,NULL);
    munit_assert_not_null(vertex1_1);
    munit_assert_memory_equal(9, vertex1_1->name, (void*)"testname");
    munit_assert_null(vertex1_1->data);
    munit_assert_not_null(vertex1_1->name);
    munit_assert_not_null(vertex1_1->edges);

    munit_assert_not_null(vertex1_2);
    munit_assert_memory_equal(8, vertex1_2->name, (void*)"vertex2");
    munit_assert_not_null(vertex1_2->name);
    munit_assert_not_null(vertex1_2->edges);
    munit_assert_ptr_equal(&testdata,vertex1_2->data);

    munit_assert_ptr_not_equal(vertex1_3->name,name);
    munit_assert_not_null(vertex1_3->ptrToNode);
    munit_assert_not_null(vertex1_3->edges);


    graphDelete(&graph1);
    graphDelete(&graph2);

    return MUNIT_OK;
}

MunitResult deleteVertexTest(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    Graph* graph = createGraph();
    int testData = 1;
    Vertex* vertex1 = addVertex(graph, "testname",NULL);
    Vertex* vertex2 = addVertex(graph, "vertex2",&testData);
    munit_assert_true(numberOfVertexs(graph) == 2);

    munit_assert_not_null(vertex1);
    deleteVertex(graph,&vertex1);
    munit_assert_null(vertex1);
    munit_assert_true(numberOfVertexs(graph) == 1);

    munit_assert_not_null(vertex2);
    deleteVertex(graph,&vertex2);
    munit_assert_null(vertex2);
    munit_assert_true(numberOfVertexs(graph) == 0);

    graphDelete(&graph);

    return MUNIT_OK;
}
MunitResult numberOfVertices_test(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    Graph* graph = createGraph();

    munit_assert_true(numberOfVertexs(graph) == 0);

    int testData = 1;
    Vertex* vertex1 = addVertex(graph, "testname",NULL);
    Vertex* vertex2 = addVertex(graph, "vertex2",NULL);
    Vertex* vertex3 = addVertex(graph, "vertex3",NULL);
    munit_assert_true(numberOfVertexs(graph) == 3);

    deleteVertex(graph,&vertex1);
    deleteVertex(graph,&vertex3);

    munit_assert_true(numberOfVertexs(graph) == 1);

    deleteVertex(graph,&vertex2);

    munit_assert_true(numberOfVertexs(graph) == 0);

    graphDelete(&graph);

    return MUNIT_OK;
}
MunitResult createEdge_test(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    Graph* graph = createGraph();
    int testData = 1;
    Vertex* vertex1 = addVertex(graph, (void*)"vertex1", &testData);
    Vertex* vertex2 = addVertex(graph, "vertex2", NULL);
    Vertex* vertex3 = addVertex(graph, "vertex3", NULL);

    munit_assert_not_null(vertex1);
    munit_assert_not_null(vertex2);
    munit_assert_not_null(vertex3);

    createEdge(vertex1,vertex2, DIRECTED);
    munit_assert_true(dllNumberOfElements(vertex1->edges) == 1);
    munit_assert_true(((Edge*)vertex1->edges->head->data)->destination == vertex2);
    munit_assert_true(dllNumberOfElements( vertex2->edges) == 0);

    createEdge(vertex2,vertex1, UNDIRECTED);
    munit_assert_true(dllNumberOfElements(vertex2->edges) == 1);
    munit_assert_true(((Edge*)vertex1->edges->head->data)->destination == vertex2);
    munit_assert_true(((Edge*)vertex2->edges->head->data)->destination == vertex1);

//    //test double assignment
//    createEdge(vertex2,vertex1, DIRECTED);
//    munit_assert_true(dllNumberOfElements(vertex2->edges) == 1);

//    //test double assignment
//    createEdge(vertex2,vertex1, UNDIRECTED);
//    munit_assert_true(dllNumberOfElements(vertex2->edges) == 1);

    graphDelete(&graph);
}
MunitResult createEdgeWithWeight_test(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    Graph* graph = createGraph();
    int testData = 1;
    Vertex* vertex1 = addVertex(graph, "vertex1", &testData);
    Vertex* vertex2 = addVertex(graph, "vertex2", NULL);
    Vertex* vertex3 = addVertex(graph, "vertex3", NULL);

    munit_assert_not_null(vertex1);
    munit_assert_not_null(vertex2);
    munit_assert_not_null(vertex3);

    createEdgeWithWeight(vertex1,vertex2,10, DIRECTED);
    munit_assert_true(dllNumberOfElements(vertex1->edges) == 1);
    munit_assert_ptr_equal(((Edge*)vertex1->edges->head->data)->destination,vertex2);
    munit_assert_true(((Edge*)vertex1->edges->head->data)->weight == 10);

    createEdgeWithWeight(vertex2,vertex1,0, DIRECTED);
    munit_assert_true(dllNumberOfElements(vertex2->edges) == 1);
    munit_assert_true(((Edge*)vertex2->edges->head->data)->weight == 0);

    createEdgeWithWeight(vertex1,vertex3,100, UNDIRECTED);
    munit_assert_true(((Edge*)vertex3->edges->head->data)->weight == 100);
    munit_assert_true(((Edge*)vertex3->edges->head->data)->destination == vertex1);
    munit_assert_true(((Edge*)vertex1->edges->head->data)->destination == vertex3);


    graphDelete(&graph);
}
MunitResult deleteEdge_undirected_test(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    Graph* graph = createGraph();
    int testData = 1;
    Vertex* vertex1 = addVertex(graph, "vertex1", &testData);
    Vertex* vertex2 = addVertex(graph, "vertex2", NULL);
    Vertex* vertex3 = addVertex(graph, "vertex3", NULL);

    Edge* edge = createEdge(vertex1,vertex2, UNDIRECTED);
    deleteEdge(graph,edge, vertex1);
    //munit_assert_null(edge);
    munit_assert_true(dllNumberOfElements(vertex1->edges) == 0);

    //test null edge
    deleteEdge(graph,NULL, vertex1);
    //test null vertex
    deleteEdge(graph,edge, NULL);

    //test wrong vertex
    Edge* edge2 = createEdge(vertex1,vertex3, UNDIRECTED);
    deleteEdge(graph,edge2,vertex1);
    munit_assert_true(dllNumberOfElements(vertex1->edges) == 0);

    //test NULL graph
    deleteEdge(NULL,edge2,vertex1);

    graphDelete(&graph);
}
MunitResult deleteEdge_directed_test(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    Graph* graph = createGraph();
    int testData = 1;
    Vertex* vertex1 = addVertex(graph, "vertex1", &testData);
    Vertex* vertex2 = addVertex(graph, "vertex2", NULL);
    Vertex* vertex3 = addVertex(graph, "vertex3", NULL);

    Edge* edge = createEdge(vertex1,vertex2, DIRECTED);
    deleteEdge(graph,edge, vertex1);
    //munit_assert_null(edge);
    munit_assert_true(dllNumberOfElements(vertex1->edges) == 0);
    munit_assert_true(dllNumberOfElements(vertex2->edges) == 0);

    graphDelete(&graph);
}
MunitResult printConnections_test(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    //it's not possible to test the printed result so its only a crash test
    Graph* graph = createGraph();

    int testData = 1;
    Vertex* vertex1 = addVertex(graph, "vertex1", &testData);
    Vertex* vertex2 = addVertex(graph, "vertex2", NULL);
    Vertex* vertex3 = addVertex(graph, "vertex3", NULL);


    Edge* edge = createEdge(vertex1,vertex2, UNDIRECTED);
    Edge* edge2 = createEdge(vertex3,vertex1, DIRECTED);

    vertexPrintConnections(graph,vertex1);
    vertexPrintConnections(NULL,vertex1);
    vertexPrintConnections(graph,NULL);


    graphDelete(&graph);
}
MunitResult searchVectorByNameTest(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    //it's not possible to test the printed result so its only a crash test
    Graph* graph = createGraph();

    int testData = 1;
    Vertex* vertex1 = addVertex(graph, "vertex1", &testData);
    Vertex* vertex2 = addVertex(graph, "vertex2", NULL);
    Vertex* vertex3 = addVertex(graph, "vertex3", NULL);
    Edge* edge = createEdge(vertex1,vertex2, UNDIRECTED);
    Edge* edge2 = createEdge(vertex3,vertex1, DIRECTED);

    munit_assert_null(searchVertexByName(NULL,"vertex1"));
    munit_assert_null(searchVertexByName(graph, NULL));

    munit_assert_ptr_equal(searchVertexByName(graph,"vertex1"), vertex1);
    munit_assert_ptr_equal(searchVertexByName(graph,"vertex2"), vertex2);
    munit_assert_ptr_equal(searchVertexByName(graph,"vertex3"), vertex3);

    munit_assert_null(searchVertexByName(graph,"vertex"));



    graphDelete(&graph);
}
MunitResult graphClearTest(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    Graph* graph = createGraph();

    int testData = 1;
    Vertex* vertex1 = addVertex(graph, "vertex1", &testData);
    Vertex* vertex2 = addVertex(graph, "vertex2", NULL);
    Vertex* vertex3 = addVertex(graph, "vertex3", NULL);
    Edge* edge = createEdge(vertex1,vertex2, UNDIRECTED);
    Edge* edge2 = createEdge(vertex3,vertex1, DIRECTED);

    clear(graph);
    munit_assert_true(numberOfVertexs(graph) == 0);


    graphDelete(&graph);
}
MunitResult cursorTest(const MunitParameter params[], void *data)
{
    (void)params; // parameter not used (prevent warning)
    (void)data;

    Graph* graph = createGraph();

    int testData = 1;
    Vertex* vertex1 = addVertex(graph, "vertex1", &testData);
    Vertex* vertex2 = addVertex(graph, "vertex2", NULL);
    Vertex* vertex3 = addVertex(graph, "vertex3", NULL);
    Vertex* vertex4 = addVertex(graph, "vertex4", NULL);

    Edge* edge = createEdge(vertex1,vertex2, UNDIRECTED);
    Edge* edge2 = createEdge(vertex3,vertex1, DIRECTED);
    Edge* edge3 = createEdge(vertex3,vertex2, DIRECTED);
    Edge* edge4 = createEdge(vertex3,vertex4, DIRECTED);
    Edge* edge5 = createEdge(vertex1,vertex4, DIRECTED);

    GraphCursor* cursor = createCursor();
    cursorSetCurrentVertex(cursor, graph, vertex1);

    munit_assert_true(cursorAvailable(cursor) == 2);
    munit_assert_ptr_equal(cursorAt(cursor,0), vertex2);
    munit_assert_ptr_equal(cursorAt(cursor,1), vertex4);

    cursorMoveInto(cursor,0);
    munit_assert_ptr_equal(cursorGetCurrentVertex(cursor),vertex2);
    munit_assert_ptr_equal(cursorAt(cursor,0), vertex1);
    munit_assert_true(cursorAvailable(cursor) == 1);

    cursorSetCurrentVertex(cursor, graph, vertex3);
    munit_assert_true(cursorAvailable(cursor) == 3);

    deleteEdge(graph, cursorEdgeAt(cursor, 0), cursor->currentVertex);

    munit_assert_true(cursorAvailable(cursor) == 2);

    cursorDeleteCurrentVertex(cursor);
    munit_assert_true(cursorAvailable(cursor) == 0);
    munit_assert_true(numberOfVertexs(graph) == 3);


    graphDelete(&graph);
}/* These tests contain only valid operations. These should always succeed. */
MunitTest tests_valid[] =
{
    /* {name, testfunction, setupfunction, teardownfunction, options, parameters} */
    {"/graphCreate", graphCreate_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/graphDelete Empty List", graphDelete_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/addVertex test", addVertex_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/deleteVertex test", deleteVertexTest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/numberOfVertices test", numberOfVertices_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/createEdge test", createEdge_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/createEdge with weight test", createEdgeWithWeight_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/deleteEdge undirected test", deleteEdge_undirected_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/deleteEdge directed test", deleteEdge_directed_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/print connections test", printConnections_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/searchVertexByName test", searchVectorByNameTest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/graph clear test", graphClearTest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

    {"/full cursor test", cursorTest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

    /* Mark the end of the array with an entry where the test function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

/* These tests contain invalid operations. These tests are allowed to fail or result in a crash. */
MunitTest tests_invalid[] =
{
    /* {name, testfunction, setupfunction, teardownfunction, options, parameters} */
    //{"/dllAddAfter illegal Operations", dllAddAfter_NodeNotInList, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

    /* Mark the end of the array with an entry where the test function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite_legal =
{
    "DLL", /* name */
    tests_valid, /* tests */
    NULL, /* suites */
    1, /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

static const MunitSuite suite_illegal =
{
    "DLL_INV", /* name */
    tests_invalid, /* tests */
    NULL, /* suites */
    1, /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

#define RUN_SUITE_ILLEGAL 0
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    int ret = munit_suite_main(&suite_legal, (void*) "graph", argc, argv);
    #if RUN_SUITE_ILLEGAL == 1
    // The tests in suite_illegal are allowed to fail or the crash the program.
    printf("\n\n");
    munit_suite_main(&suite_illegal, (void*) "DLL_INV", argc, argv);
    #else
    (void)suite_illegal; // variable not used (prevents warning)
    #endif

    return ret;
}
