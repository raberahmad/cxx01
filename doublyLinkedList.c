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
       //**ptrTheList
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
    if (theData == NULL) return NULL;
    if (theNode == NULL) return NULL;
    if (theNode->previous==NULL)
    {
        return dllAddBeforeHead(theList, theData);
    }
    
    DllNode* newNode = malloc(sizeof(newNode));
    if(newNode == NULL) return NULL;

    newNode->data=theData;
    
    newNode->next=theNode;
    theNode->previous->next=newNode;
    
    newNode->previous=theNode->previous;
    theNode->previous=newNode;

    return newNode;
}
DllNode *dllAddAfter(DoublyLinkedList *theList, DllNode *theNode, void *theData)
{
    if (theData == NULL) return NULL;
    if (theNode == NULL) return NULL;
    if (theNode->next==NULL)
    {
        return dllAddAfterTail(theList, theData);
    }

    DllNode* newNode = malloc(sizeof(newNode));
    if(newNode == NULL) return NULL;

    newNode->data=theData;
    
    ///////// geeeeen ideeee of het werkt

    newNode->next = theNode->next; 

    theNode->next = newNode; 
  

    newNode->previous = theNode; 

    return newNode;
    
}
void dllDeleteNode(DoublyLinkedList *theList, DllNode* theNode)
{   
    
    if (theList != NULL && theNode != NULL) {
        
        if(dllNumberOfElements(theList)==1 && theList->head == theList && theList->tail == theNode){
            free(theList->head);
            free(theList->tail);
            theList->head = NULL;
            theList->head=NULL;
        }
        else
        {
            if (theNode->previous==NULL)
            {
                theList->head=theNode->next;
                theNode->next->previous=NULL;
                free(theNode);
            }
            if (theNode->next==NULL)
            {
                theList->tail=theNode->previous;
                theNode->previous->next=NULL;
            }
            else
            {
                theNode->previous->next=theNode->next;
                theNode->next->previous=theNode->previous;
                free(theNode);
            }       
        }         
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
