// #include "munit.h"
// #include "doublyLinkedList.h"
// #include <stdio.h>

// /* For dynamic tests */
// #define MAX_LIST_LENGTH 12
// typedef struct
// {
//    DoublyLinkedList *dll;
//    DllNode *nodes[MAX_LIST_LENGTH+1];
// } t_list;
// static int listData[MAX_LIST_LENGTH] = {4, 7, -6, 3, 9, 7, 18, 112, 5, 8, -2, 5};

// /* Predicate functions to test the find functions */
// bool intGreatherThan(void *d1, void *d2)
// {
//    if (d1 == 0 || d2 == 0) return false;
//    return *(int*)d1 > *(int*)d2;
// }

// bool doubleGreatherThan(void *d1, void *d2)
// {
//    if (d1 == 0 || d2 == 0) return false;
//    return *(double*)d1 > *(double*)d2;
// }

// bool intLessThan(void *d1, void *d2)
// {
//    if (d1 == 0 || d2 == 0) return false;
//    return *(int*)d1 < *(int*)d2;
// }

// bool intEqual(void *d1, void *d2)
// {
//    if (d1 == 0 || d2 == 0) return d1 == 0 && d2 == 0;
//    return *(int*)d1 == *(int*)d2;
// }

// bool isAlwaysFalse(void *d1, void *d2)
// {
//    (void)d1; // parameter not used (prevent warning)
//    (void)d2;
//    return false;
// }

// /* Dynamically create a list */
// static void* createTestList(const MunitParameter params[], void* data)
// {
//    (void)data; // parameter not used (prevent warning)
//    t_list *list = malloc(sizeof(t_list));

//    if(list == NULL)
//    {
//        return NULL;
//    }

//    list->dll = dllCreate();

//    size_t length = (size_t)(atoi(munit_parameters_get(params, "listlength")));

//    if(length > MAX_LIST_LENGTH)
//    {
//        length = MAX_LIST_LENGTH;
//    }

//    size_t i = 0;
//    for(i = 0; i < length; i++)
//    {
//        list->nodes[i] = dllAddAfterTail(list->dll, (void*)&listData[i]);
//    }
//    list->nodes[i] = NULL;

//    return (void*)list;
// }

// /* Cleanup list */
// static void destroyTestList(void* list)
// {
//    DoublyLinkedList *lst = ((t_list *)list)->dll;
//    if(lst != NULL)
//    {
//        dllDelete(&lst);
//    }
//    free((t_list *)list);
// }

// MunitResult dllCreate_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    munit_assert_not_null(lst);
//    munit_assert_null(lst->head);
//    munit_assert_null(lst->tail);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllDelete_empty(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    munit_assert_not_null(lst);

//    dllDelete(&lst);

//    munit_assert_null(lst);

//    return MUNIT_OK;
// }

// MunitResult dllDelete_filled(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    t_list* testlist = (t_list*)data;
//    dllDelete(&(testlist->dll));

//    munit_assert_null(testlist->dll);

//    return MUNIT_OK;
// }

// MunitResult dllAddBeforeHead_first(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lsta = dllCreate();
//    DllNode *a = dllAddBeforeHead(lsta, (void*)"a");
//    DoublyLinkedList *lstb = dllCreate();
//    DllNode *b = dllAddBeforeHead(lstb, (void*)"b");

//    munit_assert_not_null(a);
//    munit_assert_memory_equal(2, a->data, (void*)"a");
//    munit_assert_not_null(lsta->head);
//    munit_assert_not_null(lsta->tail);
//    munit_assert_null(a->next);
//    munit_assert_null(a->previous);
//    munit_assert_ptr_equal(lsta->head, a);
//    munit_assert_ptr_equal(lsta->tail, a);
//    munit_assert_ptr_equal(lsta->head, lsta->tail);

//    munit_assert_not_null(b);
//    munit_assert_memory_equal(2, b->data, (void*)"b");
//    munit_assert_not_null(lstb->head);
//    munit_assert_not_null(lstb->tail);
//    munit_assert_null(a->next);
//    munit_assert_null(a->previous);
//    munit_assert_ptr_equal(lstb->head, b);
//    munit_assert_ptr_equal(lstb->tail, b);
//    munit_assert_ptr_equal(lstb->head, lstb->tail);

//    munit_assert_ptr_not_equal(a, b);
//    munit_assert_ptr_not_equal(lsta->head, lstb->head);
//    munit_assert_ptr_not_equal(lsta->tail, lstb->tail);

//    dllDelete(&lsta);
//    dllDelete(&lstb);

//    return MUNIT_OK;
// }

// MunitResult dllAddBeforeHead_second(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddBeforeHead(lst, (void*)"a");
//    DllNode *b = dllAddBeforeHead(lst, (void*)"b");
//    munit_assert_not_null(b);
//    munit_assert_memory_equal(2, b->data, (void*)"b");
//    munit_assert_not_null(lst->head);
//    munit_assert_not_null(lst->tail);
//    munit_assert_null(a->next);
//    munit_assert_null(b->previous);
//    munit_assert_ptr_equal(lst->head, b);
//    munit_assert_ptr_equal(lst->tail, a);
//    munit_assert_ptr_equal(b->next, a);
//    munit_assert_ptr_equal(a->previous, b);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddBeforeHead_third(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddBeforeHead(lst, (void*)"a");
//    DllNode *b = dllAddBeforeHead(lst, (void*)"b");
//    DllNode *c = dllAddBeforeHead(lst, (void*)"c");
//    munit_assert_not_null(c);
//    munit_assert_memory_equal(2, c->data, (void*)"c");
//    munit_assert_not_null(lst->head);
//    munit_assert_not_null(lst->tail);
//    munit_assert_null(a->next);
//    munit_assert_null(c->previous);
//    munit_assert_ptr_equal(lst->head, c);
//    munit_assert_ptr_equal(lst->tail, a);
//    munit_assert_ptr_equal(c->next, b);
//    munit_assert_ptr_equal(b->next, a);
//    munit_assert_ptr_equal(a->previous, b);
//    munit_assert_ptr_equal(b->previous, c);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddBeforeHead_null(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddBeforeHead(lst, (void*)"a");
//    DllNode *b = dllAddBeforeHead(lst, 0);
//    DllNode *c = dllAddBeforeHead(lst, (void*)"c");
//    munit_assert_not_null(c);
//    munit_assert_memory_equal(2, c->data, (void*)"c");
//    munit_assert_not_null(lst->head);
//    munit_assert_not_null(lst->tail);
//    munit_assert_null(a->next);
//    munit_assert_null(c->previous);
//    munit_assert_ptr_equal(lst->head, c);
//    munit_assert_ptr_equal(lst->tail, a);
//    munit_assert_ptr_equal(c->next, b);
//    munit_assert_ptr_equal(b->next, a);
//    munit_assert_ptr_equal(a->previous, b);
//    munit_assert_ptr_equal(b->previous, c);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddAfterTail_first(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddAfterTail(lst, (void*)"a");
//    munit_assert_not_null(a);
//    munit_assert_memory_equal(2, a->data, (void*)"a");
//    munit_assert_not_null(lst->head);
//    munit_assert_not_null(lst->tail);
//    munit_assert_null(a->next);
//    munit_assert_null(a->previous);
//    munit_assert_ptr_equal(lst->head, a);
//    munit_assert_ptr_equal(lst->tail, a);
//    munit_assert_ptr_equal(lst->head, lst->tail);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddAfterTail_second(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddAfterTail(lst, (void*)"a");
//    DllNode *b = dllAddAfterTail(lst, (void*)"b");
//    munit_assert_not_null(b);
//    munit_assert_memory_equal(2, b->data, (void*)"b");
//    munit_assert_not_null(lst->head);
//    munit_assert_not_null(lst->tail);
//    munit_assert_null(a->previous);
//    munit_assert_null(b->next);
//    munit_assert_ptr_equal(lst->tail, b);
//    munit_assert_ptr_equal(lst->head, a);
//    munit_assert_ptr_equal(b->previous, a);
//    munit_assert_ptr_equal(a->next, b);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddAfterTail_third(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddAfterTail(lst, (void*)"a");
//    DllNode *b = dllAddAfterTail(lst, (void*)"b");
//    DllNode *c = dllAddAfterTail(lst, (void*)"c");
//    munit_assert_not_null(c);
//    munit_assert_memory_equal(2, c->data, (void*)"c");
//    munit_assert_not_null(lst->head);
//    munit_assert_not_null(lst->tail);
//    munit_assert_null(c->next);
//    munit_assert_null(a->previous);
//    munit_assert_ptr_equal(lst->head, a);
//    munit_assert_ptr_equal(lst->tail, c);
//    munit_assert_ptr_equal(c->previous, b);
//    munit_assert_ptr_equal(a->next, b);
//    munit_assert_ptr_equal(b->next, c);
//    munit_assert_ptr_equal(b->previous, a);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddAfterTail_null(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddAfterTail(lst, (void*)"a");
//    DllNode *b = dllAddAfterTail(lst, 0);
//    DllNode *c = dllAddAfterTail(lst, (void*)"c");
//    munit_assert_not_null(c);
//    munit_assert_memory_equal(2, c->data, (void*)"c");
//    munit_assert_not_null(lst->head);
//    munit_assert_not_null(lst->tail);
//    munit_assert_null(c->next);
//    munit_assert_null(a->previous);
//    munit_assert_ptr_equal(lst->head, a);
//    munit_assert_ptr_equal(lst->tail, c);
//    munit_assert_ptr_equal(c->previous, b);
//    munit_assert_ptr_equal(a->next, b);
//    munit_assert_ptr_equal(b->next, c);
//    munit_assert_ptr_equal(b->previous, a);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddAfter_NodeNotInList(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();

//    DllNode b;
//    DllNode *a = dllAddAfter(lst, &b, (void*)"a");
//    munit_assert_null(lst->head);
//    munit_assert_null(lst->tail);
//    munit_assert_null(a);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddAfter_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();

//    /* a */
//    DllNode *a = dllAddAfterTail(lst, 0);

//    /* a --> b */
//    DllNode *b = dllAddAfter(lst, a, 0);

//    /* a --> c --> b */
//    DllNode *c = dllAddAfter(lst, a, 0);

//    /* a --> c --> b --> d */
//    DllNode *d = dllAddAfter(lst, b, 0);

//    /* a --> c --> e --> b --> d */
//    DllNode *e = dllAddAfter(lst, c, 0);

//    munit_assert_ptr_equal(lst->head, a);
//    munit_assert_ptr_equal(a->next, c);
//    munit_assert_ptr_equal(c->next, e);
//    munit_assert_ptr_equal(e->next, b);
//    munit_assert_ptr_equal(b->next, d);
//    munit_assert_null(d->next);
//    munit_assert_ptr_equal(lst->tail, d);
//    munit_assert_ptr_equal(d->previous, b);
//    munit_assert_ptr_equal(b->previous, e);
//    munit_assert_ptr_equal(e->previous, c);
//    munit_assert_ptr_equal(c->previous, a);
//    munit_assert_null(a->previous);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddBefore_NodeNotInList(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();

//    DllNode b;
//    DllNode *a = dllAddBefore(lst, &b, (void*)"a");
//    munit_assert_null(lst->head);
//    munit_assert_null(lst->tail);
//    munit_assert_null(a);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllAddBefore_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();

//    /* a */
//    DllNode *a = dllAddBeforeHead(lst, 0);

//    /* b --> a */
//    DllNode *b = dllAddBefore(lst, a, 0);

//    /* b --> c --> a */
//    DllNode *c = dllAddBefore(lst, a, 0);

//    /* d --> b --> c --> a */
//    DllNode *d = dllAddBefore(lst, b, 0);

//    /* d --> b --> e --> c --> a */
//    DllNode *e = dllAddBefore(lst, c, 0);

//    munit_assert_ptr_equal(lst->head, d);
//    munit_assert_ptr_equal(d->next, b);
//    munit_assert_ptr_equal(b->next, e);
//    munit_assert_ptr_equal(e->next, c);
//    munit_assert_ptr_equal(c->next, a);
//    munit_assert_null(a->next);
//    munit_assert_ptr_equal(lst->tail, a);
//    munit_assert_ptr_equal(a->previous, c);
//    munit_assert_ptr_equal(c->previous, e);
//    munit_assert_ptr_equal(e->previous, b);
//    munit_assert_ptr_equal(b->previous, d);
//    munit_assert_null(d->previous);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllDeleteNode_one(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddAfterTail(lst, (void*)"a");

//    dllDeleteNode(lst, a);

//    munit_assert_null(lst->head);
//    munit_assert_null(lst->tail);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllDeleteNode_two(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddAfterTail(lst, (void*)"a");
//    DllNode *b = dllAddAfterTail(lst, (void*)"b");

//    dllDeleteNode(lst, a);

//    munit_assert_ptr_equal(lst->head, b);
//    munit_assert_ptr_equal(lst->tail, b);
//    munit_assert_null(b->next);
//    munit_assert_null(b->previous);

//    dllDelete(&lst);

//    lst = dllCreate();
//    a = dllAddAfterTail(lst, (void*)"a");
//    b = dllAddAfterTail(lst, (void*)"b");

//    dllDeleteNode(lst, b);

//    munit_assert_ptr_equal(lst->head, a);
//    munit_assert_ptr_equal(lst->tail, a);
//    munit_assert_null(a->next);
//    munit_assert_null(a->previous);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllDeleteNode_three(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddAfterTail(lst, (void*)"a");
//    DllNode *b = dllAddAfterTail(lst, (void*)"b");
//    DllNode *c = dllAddAfterTail(lst, (void*)"c");

//    dllDeleteNode(lst, b);

//    munit_assert_ptr_equal(lst->head, a);
//    munit_assert_ptr_equal(lst->tail, c);
//    munit_assert_ptr_equal(a->next, c);
//    munit_assert_ptr_equal(c->previous, a);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllDeleteNode_null(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode *a = dllAddAfterTail(lst, (void*)"a");
//    DllNode *b = dllAddAfterTail(lst, 0);
//    DllNode *c = dllAddAfterTail(lst, (void*)"c");

//    dllDeleteNode(lst, b);

//    munit_assert_ptr_equal(lst->head, a);
//    munit_assert_ptr_equal(lst->tail, c);
//    munit_assert_ptr_equal(a->next, c);
//    munit_assert_ptr_equal(c->previous, a);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllFindFirst_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    int intList[6] = {7, -5, 8, -1, 7, 9};
//    DllNode *nodeList[6];

//    DoublyLinkedList *lst = dllCreate();
//    for(int i = 0; i < 6; i++)
//    {
//        nodeList[i] = dllAddAfterTail(lst, &intList[i]);
//    }

//    int ci = 7;
//    DllNode *found = dllFindFirst(lst, &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[2], found);

//    ci = 6;
//    found = dllFindFirst(lst, &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[0], found);

//    ci = 8;
//    found = dllFindFirst(lst, &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[5], found);

//    ci = 0;
//    found = dllFindFirst(lst, &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[1], found);

//    found = dllFindFirst(lst, &isAlwaysFalse, &ci);
//    munit_assert_ptr_null(found);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllFindFirstNull_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    int intList[5] = {7, -5, 8, -1, 7};
//    DllNode *nodeList[6];

//    DoublyLinkedList *lst = dllCreate();
//    for(int i = 0; i < 5; i++)
//    {
//        nodeList[i] = dllAddAfterTail(lst, &intList[i]);
//    }
//    nodeList[5] = dllAddAfterTail(lst, 0);

//    int ci = 0;
//    DllNode *found = dllFindFirst(lst, &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[1], found);

//    found = dllFindFirst(lst, &intEqual, &ci);
//    munit_assert_ptr_null(found);

//    found = dllFindFirst(lst, &intEqual, 0);
//    munit_assert_ptr_equal(nodeList[5], found);

//    found = dllFindFirst(lst, &isAlwaysFalse, &ci);
//    munit_assert_ptr_null(found);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllFindFirstDouble_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    double intList[6] = {7.3, -5.3, 8.3, -1.3, 7.3, 9.3};
//    DllNode *nodeList[6];

//    DoublyLinkedList *lst = dllCreate();
//    for(int i = 0; i < 6; i++)
//    {
//        nodeList[i] = dllAddAfterTail(lst, &intList[i]);
//    }

//    double ci = 7.4;
//    DllNode *found = dllFindFirst(lst, &doubleGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[2], found);

//    ci = 6.3;
//    found = dllFindFirst(lst, &doubleGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[0], found);

//    ci = 8.31;
//    found = dllFindFirst(lst, &doubleGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[5], found);

//    ci = 100.2;
//    found = dllFindFirst(lst, &doubleGreatherThan, &ci);
//    munit_assert_ptr_null(found);

//    found = dllFindFirst(lst, &isAlwaysFalse, &ci);
//    munit_assert_ptr_null(found);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllFindLast_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    int intList[6] = {17, -5, 8, -1, 7, 9};
//    DllNode *nodeList[6];

//    DoublyLinkedList *lst = dllCreate();
//    for(int i = 0; i < 6; i++)
//    {
//        nodeList[i] = dllAddAfterTail(lst, &intList[i]);
//    }

//    int ci = 7;
//    DllNode *found = dllFindLast(lst, &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[5], found);

//    ci = 16;
//    found = dllFindLast(lst, &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[0], found);

//    ci = 8;
//    found = dllFindLast(lst, &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[4], found);

//    ci = 0;
//    found = dllFindLast(lst, &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[3], found);

//    found = dllFindLast(lst, &isAlwaysFalse, &ci);
//    munit_assert_ptr_null(found);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllFindBefore_NodeNotInList(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();

//    int ci = 7;
//    DllNode b;
//    DllNode *a = dllFindBefore(lst, &b, intEqual, &ci);
//    munit_assert_null(lst->head);
//    munit_assert_null(lst->tail);
//    munit_assert_null(a);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllFindBefore_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    int intList[6] = {7, -5, 8, -1, 7, 8};
//    DllNode *nodeList[6];

//    DoublyLinkedList *lst = dllCreate();
//    for(int i = 0; i < 6; i++)
//    {
//        nodeList[i] = dllAddAfterTail(lst, &intList[i]);
//    }

//    int ci = 7;
//    DllNode *found = dllFindBefore(lst, nodeList[5], &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[2], found);

//    found = dllFindBefore(lst, nodeList[2], &intGreatherThan, &ci);
//    munit_assert_ptr_null(found);

//    ci = 0;
//    found = dllFindBefore(lst, nodeList[3], &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[1], found);

//    found = dllFindBefore(lst, nodeList[5], &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[3], found);

//    ci = 8;
//    found = dllFindBefore(lst, nodeList[0], &intLessThan, &ci);
//    munit_assert_ptr_null(found);

//    found = dllFindBefore(lst, nodeList[1], &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[0], found);

//    found = dllFindBefore(lst, nodeList[2], &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[1], found);

//    found = dllFindBefore(lst, nodeList[3], &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[1], found);

//    found = dllFindBefore(lst, nodeList[4], &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[3], found);

//    found = dllFindBefore(lst, nodeList[5], &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[4], found);

//    found = dllFindBefore(lst, nodeList[1], &isAlwaysFalse, &ci);
//    munit_assert_ptr_null(found);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllFindAfter_NodeNotInList(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    DoublyLinkedList *lst = dllCreate();

//    int ci = 7;
//    DllNode b;
//    DllNode *a = dllFindAfter(lst, &b, intEqual, &ci);
//    munit_assert_null(lst->head);
//    munit_assert_null(lst->tail);
//    munit_assert_null(a);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllFindAfter_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;
//    int intList[6] = {7, -5, 8, -1, 7, 8};
//    DllNode *nodeList[6];

//    DoublyLinkedList *lst = dllCreate();
//    for(int i = 0; i < 6; i++)
//    {
//        nodeList[i] = dllAddAfterTail(lst, &intList[i]);
//    }

//    int ci = 7;
//    DllNode *found = dllFindAfter(lst, nodeList[0], &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[2], found);

//    found = dllFindAfter(lst, nodeList[1], &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[2], found);

//    found = dllFindAfter(lst, nodeList[2], &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[5], found);

//    found = dllFindAfter(lst, nodeList[3], &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[5], found);

//    found = dllFindAfter(lst, nodeList[4], &intGreatherThan, &ci);
//    munit_assert_ptr_equal(nodeList[5], found);

//    found = dllFindAfter(lst, nodeList[5], &intGreatherThan, &ci);
//    munit_assert_ptr_null(found);

//    ci = 0;
//    found = dllFindAfter(lst, nodeList[0], &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[1], found);

//    found = dllFindAfter(lst, nodeList[1], &intLessThan, &ci);
//    munit_assert_ptr_equal(nodeList[3], found);

//    found = dllFindAfter(lst, nodeList[3], &intLessThan, &ci);
//    munit_assert_ptr_null(found);

//    found = dllFindAfter(lst, nodeList[2], &isAlwaysFalse, &ci);
//    munit_assert_ptr_null(found);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllNumberOfElements_test(const MunitParameter params[], void *data)
// {
//    DoublyLinkedList *lst = ((t_list*)data)->dll;
//    munit_assert_not_null(lst);

//    size_t length = (size_t)(atoi(munit_parameters_get(params, "listlength")));
//    size_t listLength = dllNumberOfElements(lst);
//    munit_assert_size(length, ==, listLength);

//    return MUNIT_OK;
// }

// static char* length_params[] =
// {
//    "0", "1", "3", "12", NULL
// };

// static MunitParameterEnum listLength_params[] =
// {
//    {"listlength", length_params},
//    {NULL, NULL },
// };

// MunitResult dllTheListNull_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;

//    DoublyLinkedList *lst = NULL;
//    dllDelete(NULL);
//    dllDelete(&lst);
//    munit_assert_ptr_null(lst);

//    DllNode *node = dllAddBeforeHead(lst, NULL);
//    munit_assert_ptr_null(node);

//    node = dllAddAfterTail(lst, NULL);
//    munit_assert_ptr_null(node);

//    int ci = 13;
//    DoublyLinkedList *lst2 = dllCreate();
//    DllNode * a = dllAddAfterTail(lst2, &ci);

//    node = dllAddBefore(lst, a, NULL);
//    munit_assert_ptr_null(node);

//    node = dllAddAfter(lst, a, NULL);
//    munit_assert_ptr_null(node);

//    dllDeleteNode(lst, a);

//    node = dllFindFirst(lst, intEqual, &ci);
//    munit_assert_ptr_null(node);

//    node = dllFindLast(lst, intEqual, &ci);
//    munit_assert_ptr_null(node);

//    node = dllFindAfter(lst, a, intEqual, &ci);
//    munit_assert_ptr_null(node);

//    node = dllFindBefore(lst, a, intEqual, &ci);
//    munit_assert_ptr_null(node);

//    size_t s = dllNumberOfElements(lst);
//    munit_assert_size(0, ==, s);

//    dllDelete(&lst2);

//    return MUNIT_OK;
// }

// MunitResult dllTheNodeNull_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;

//    int ci = 13;
//    DoublyLinkedList *lst = dllCreate();

//    DllNode *node = dllAddBefore(lst, NULL, NULL);
//    munit_assert_ptr_null(node);

//    node = dllAddAfter(lst, NULL, NULL);
//    munit_assert_ptr_null(node);

//    node = dllFindAfter(lst, NULL, intEqual, &ci);
//    munit_assert_ptr_null(node);

//    node = dllFindBefore(lst, NULL, intEqual, &ci);
//    munit_assert_ptr_null(node);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// MunitResult dllPredicateNull_test(const MunitParameter params[], void *data)
// {
//    (void)params; // parameter not used (prevent warning)
//    (void)data;

//    int ci = 13;
//    DoublyLinkedList *lst = dllCreate();
//    DllNode * a = dllAddAfterTail(lst, &ci);

//    DllNode *node = dllFindFirst(lst, NULL, &ci);
//    munit_assert_ptr_null(node);

//    node = dllFindLast(lst, NULL, &ci);
//    munit_assert_ptr_null(node);

//    node = dllFindAfter(lst, a, NULL, &ci);
//    munit_assert_ptr_null(node);

//    node = dllFindBefore(lst, a, NULL, &ci);
//    munit_assert_ptr_null(node);

//    dllDelete(&lst);

//    return MUNIT_OK;
// }

// /* These tests contain only valid operations. These should always succeed. */
// MunitTest tests_valid[] =
// {
//    /* {name, testfunction, setupfunction, teardownfunction, options, parameters} */
//    {"/dllCreate", dllCreate_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllDelete Empty List", dllDelete_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddBeforeHead in empty list", dllAddBeforeHead_first, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddBeforeHead list 1 element", dllAddBeforeHead_second, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddBeforeHead list 2 elements", dllAddBeforeHead_third, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddBeforeHead list with NULL element", dllAddBeforeHead_null, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddAfterTail in empty list", dllAddAfterTail_first, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddAfterTail list 1 element", dllAddAfterTail_second, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddAfterTail list 2 elements", dllAddAfterTail_third, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddAfterTail list with NULL element", dllAddAfterTail_null, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddAfter Test", dllAddAfter_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddBefore Test", dllAddBefore_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllDeleteNode list 1 element", dllDeleteNode_one, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllDeleteNode list 2 elements", dllDeleteNode_two, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllDeleteNode list 3 elements", dllDeleteNode_three, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllDeleteNode with NULL element", dllDeleteNode_null, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllNumberOfElements", dllNumberOfElements_test, createTestList, destroyTestList, MUNIT_TEST_OPTION_NONE, listLength_params},
//    {"/dllFindFirst", dllFindFirst_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllFindFirstNULL", dllFindFirstNull_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllFindFirstDouble", dllFindFirstDouble_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllFindLast", dllFindLast_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllFindBefore", dllFindBefore_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllFindAfter", dllFindAfter_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllDelete Filled", dllDelete_filled, createTestList, destroyTestList, MUNIT_TEST_OPTION_NONE, listLength_params},
//    {"/dllTheListNull", dllTheListNull_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllTheNodeNull", dllTheNodeNull_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllPredicateNull", dllPredicateNull_test, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    /* Mark the end of the array with an entry where the test function is NULL */
//    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
// };

// /* These tests contain invalid operations. These tests are allowed to fail or result in a crash. */
// MunitTest tests_invalid[] =
// {
//    /* {name, testfunction, setupfunction, teardownfunction, options, parameters} */
//    {"/dllAddAfter illegal Operations", dllAddAfter_NodeNotInList, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllAddBefore illegal operations", dllAddBefore_NodeNotInList, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllFindAfter illegal operations", dllFindAfter_NodeNotInList, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
//    {"/dllFindBefore illegal operations", dllFindBefore_NodeNotInList, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
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
//    int ret = munit_suite_main(&suite_legal, (void*) "DLL", argc, argv);
//    #if RUN_SUITE_ILLEGAL == 1
//    // The tests in suite_illegal are allowed to fail or the crash the program.
//    printf("\n\n");
//    munit_suite_main(&suite_illegal, (void*) "DLL_INV", argc, argv);
//    #else
//    (void)suite_illegal; // variable not used (prevents warning)
//    #endif

//    return ret;
// }
