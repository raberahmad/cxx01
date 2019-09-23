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
    return newNode;
}
DllNode *dllAddAfterTail(DoublyLinkedList *theList, void *theData)
{
    
    if(theList == NULL) return NULL;
    if(theData == NULL) return NULL;
    DllNode *newNode = malloc(sizeof(newNode));
    if (newNode == NULL) return NULL;
    
    newNode->data = theData;
    newNode->next = NULL;
    if(theList->head == NULL){
        theList->head = newNode;
        newNode->previous=NULL;
    }
    else{
        theList->tail->next=newNode;
        newNode->previous=theList->tail;
       
        }
     theList->tail=newNode;
    return newNode;
}
DllNode *dllAddBefore(DoublyLinkedList *theList, DllNode *theNode, void *theData)
{
    return NULL;

}
DllNode *dllAddAfter(DoublyLinkedList *theList, DllNode *theNode, void *theData)
{
    return NULL;

}
void dllDeleteNode(DoublyLinkedList *theList, DllNode* theNode)
{   
    
    if (theList != NULL && theNode != NULL) {
        int size=dllNumberOfElements(theList);

        

    }
    
}
DllNode *dllFindFirst(DoublyLinkedList *theList, bool (*predicate)(void *d1, void *d2), void *theData)
{
    return NULL;

}
DllNode *dllFindLast(DoublyLinkedList *theList, bool (*predicate)(void *d1, void *d2), void *theData)
{
    return NULL;

}
DllNode *dllFindAfter(DoublyLinkedList *theList, DllNode *theNode, bool (*predicate)(void *d1, void *d2), void *theData){
    return NULL;

}
DllNode *dllFindBefore(DoublyLinkedList *theList, DllNode *theNode, bool (*predicate)(void *d1, void *d2), void *theData)
{
    return NULL;

}
size_t dllNumberOfElements(DoublyLinkedList *theList)
{
    int size = 0;
    
    if (theList == NULL)
    {
        return NULL;
    }
    else if (theList->head != NULL && theList->tail != NULL) {
        
        DllNode *tmpNode = malloc(sizeof(tmpNode));
        tmpNode = theList->head;
        while (tmpNode) {
            tmpNode=tmpNode->next;
            size=size+1;
        }
        
        free(tmpNode);
        tmpNode=NULL;     
    }
    return size;
}
