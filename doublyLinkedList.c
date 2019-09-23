#include "doublyLinkedList.h"

DoublyLinkedList *dllCreate(void)
{
    DoublyLinkedList* newList = malloc(sizeof(newList));
    if(newList == NULL) return NULL;
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}
void dllDelete(DoublyLinkedList **ptrTheList)
{
    //todo: delete items
    if(*ptrTheList)
    {
       // free(*ptrTheList);
    }
    *ptrTheList = NULL;
}
DllNode *dllAddBeforeHead(DoublyLinkedList *theList, void *theData)
{
    if(theList == NULL) return NULL;
    if(theData == NULL) return NULL;
    DllNode* newNode = malloc(sizeof(newNode));
    if(newNode == NULL) return NULL;

    newNode->data = theData;

    newNode->previous = NULL;
    if(theList->head)
    {
        newNode->next = theList->head;
        newNode->next->previous = newNode;
    }
    else {
        newNode->next = NULL;
        theList->tail = newNode;
    }
    theList->head = newNode;
    char* a = "a";

}
DllNode *dllAddAfterTail(DoublyLinkedList *theList, void *theData)
{

}
DllNode *dllAddBefore(DoublyLinkedList *theList, DllNode *theNode, void *theData)
{

}
DllNode *dllAddAfter(DoublyLinkedList *theList, DllNode *theNode, void *theData)
{

}
void dllDeleteNode(DoublyLinkedList *theList, DllNode* theNode)
{

}
DllNode *dllFindFirst(DoublyLinkedList *theList, bool (*predicate)(void *d1, void *d2), void *theData)
{

}
DllNode *dllFindLast(DoublyLinkedList *theList, bool (*predicate)(void *d1, void *d2), void *theData)
{

}
DllNode *dllFindAfter(DoublyLinkedList *theList, DllNode *theNode, bool (*predicate)(void *d1, void *d2), void *theData){

}
DllNode *dllFindBefore(DoublyLinkedList *theList, DllNode *theNode, bool (*predicate)(void *d1, void *d2), void *theData)
{

}
size_t dllNumberOfElements(DoublyLinkedList *theList)
{

}
