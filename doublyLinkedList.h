#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct DllNodeTag
{
    void *data;
    struct DllNodeTag *next;
    struct DllNodeTag *previous;
} DllNode;

typedef struct
{
    DllNode *head ;
    DllNode *tail;
} DoublyLinkedList;

DoublyLinkedList *dllCreate(void);
void dllDelete(DoublyLinkedList **ptrTheList);
DllNode *dllAddBeforeHead(DoublyLinkedList *theList, void *theData);
DllNode *dllAddAfterTail(DoublyLinkedList *theList, void *theData);
DllNode *dllAddBefore(DoublyLinkedList *theList, DllNode *theNode, void *theData);
DllNode *dllAddAfter(DoublyLinkedList *theList, DllNode *theNode, void *theData);
void dllDeleteNode(DoublyLinkedList *theList, DllNode* theNode);
DllNode *dllFindFirst(DoublyLinkedList *theList, bool (*predicate)(void *d1, void *d2), void *theData);
DllNode *dllFindLast(DoublyLinkedList *theList, bool (*predicate)(void *d1, void *d2), void *theData);
DllNode *dllFindAfter(DoublyLinkedList *theList, DllNode *theNode, bool (*predicate)(void *d1, void *d2), void *theData);
DllNode *dllFindBefore(DoublyLinkedList *theList, DllNode *theNode, bool (*predicate)(void *d1, void *d2), void *theData);
size_t dllNumberOfElements(DoublyLinkedList *theList);

#endif
