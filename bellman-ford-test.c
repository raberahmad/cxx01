// #include "lib/munit/munit.h"
// #include "lib/graph/graph.h"
// #include "lib/cursor/graphcursor.h"
// #include <stdio.h>

// MunitResult jsonToGraph_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    GraphCursor* cursor = createCursor();
//    Graph* graph = loadGraphFromFile("json/citiesShortestPath2.json");
//    munit_assert_not_null(graph);

//    munit_assert_true(numberOfVertexs(graph) == 11);

//    //pick a random vertex to test its connections
//    Vertex* vertex = searchVertexByName(graph,"Amsterdam");
//    munit_assert_not_null(vertex);

//    cursorSetCurrentVertex(cursor, graph, vertex);
//    munit_assert_true(cursorAvailable(cursor) == 2);

//    munit_assert_true(cursorEdgeAt(cursor,0)->weight == 690 || cursorEdgeAt(cursor,1)->weight == 690);

//    vertex = cursorAt(cursor,1);
//    munit_assert_true(strcmp(cursorAt(cursor,0)->name,"Berlin") || strcmp(cursorAt(cursor,1)->name,"Berlin"));

//    deleteCursor(&cursor);
//    graphDelete(&graph);

//    return MUNIT_OK;
// }
// /* These tests contain only valid operations. These should always succeed. */
// MunitTest tests_valid[] =
// {
//    /* {name, testfunction, setupfunction, teardownfunction, options, parameters} */
//    {"/graphCreate", jsonToGraph_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

//    /* Mark the end of the array with an entry where the test function is NULL */
//    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
// };

// /* These tests contain invalid operations. These tests are allowed to fail or result in a crash. */
// MunitTest tests_invalid[] =
// {
//    /* {name, testfunction, setupfunction, teardownfunction, options, parameters} */
//    //{"/dllAddAfter illegal Operations", dllAddAfter_NodeNotInList, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

//    /* Mark the end of the array with an entry where the test function is NULL */
//    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
// };

// static const MunitSuite suite_legal =
// {
//    "DLL", /* name */
//    tests_valid, /* tests */
//    NULL, /* suites */
//    1, /* iterations */
//    MUNIT_SUITE_OPTION_NONE /* options */
// };

// static const MunitSuite suite_illegal =
// {
//    "DLL_INV", /* name */
//    tests_invalid, /* tests */
//    NULL, /* suites */
//    1, /* iterations */
//    MUNIT_SUITE_OPTION_NONE /* options */
// };

// #define RUN_SUITE_ILLEGAL 0
// int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
// {
//    int ret = munit_suite_main(&suite_legal, (void*) "graph", argc, argv);
//    #if RUN_SUITE_ILLEGAL == 1
//    // The tests in suite_illegal are allowed to fail or the crash the program.
//    printf("\n\n");
//    munit_suite_main(&suite_illegal, (void*) "DLL_INV", argc, argv);
//    #else
//    (void)suite_illegal; // variable not used (prevents warning)
//    #endif

//    return ret;
// }
