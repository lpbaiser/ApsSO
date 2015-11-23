/* 
 * File:   request.h
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 17, 2015, 1:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "connection.h"
#include "requestHandler.h"

#include "dynamicList.h"

//#define ItemType requestHandler
//#define ItemType requestHandler




//
//List *createList();
//void initializeList(List *l);
//Boolean addLastList(List *l, ItemType e);
//Boolean addList(List* l, ItemType e, int index);
//Boolean removeList(List* l, int index, ItemType *e);
//Boolean removeFirstList(List* l, ItemType* e);
//Boolean removeLastList(List* l, ItemType* e);
//Boolean getList(List* l, int index, ItemType* e);
//Boolean setList(List* l, int index, ItemType e);
//int indexOfList(List* l, ItemType* e);
//Boolean containsList(List* l, ItemType *e);
//Boolean isEmptyList(List* l);
//void printList(List* l);
//void printBoolean(Boolean *b);

List *createList() {
    return (List*) malloc(sizeof (List));
}

void initializeList(List *l) {
    l->size = 0;
    l->first = NULL;
    l->last = NULL;
}

Boolean addLastList(List *l, ItemType e) {
    Node *n = (Node*) malloc(sizeof (Node));
    n->data = e;
    n->next = NULL;
    if (l->size == 0) {
        l->first = n;
        l->last = n;
    } else {
        l->last->next = n;
        l->last = n;
    }
    l->size++;
    return true;
}


Boolean removeFirstList(List* l, ItemType *e) {
    if (isEmptyList(l)) {
        return false;
    }
    Node *remove = l->first;
    l->first = NULL;
    l->last = NULL;
    return true;
}

Boolean isEmptyList(List* l) {
    return l->size == 0;
}
