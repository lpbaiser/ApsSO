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
#include "server.h"
#include "workerThread.h"
#include "request.h"

List *createList() {
    return (List*) malloc(sizeof (List));
}

void initializeList(List *l) {
    l->size = 0;
    l->first = NULL;
    l->last = NULL;
}

Boolean addLastList(List *l, Request* e) {
    Node *n = (Node*) malloc(sizeof (Node));
    n->data = (Request*) malloc(sizeof(Request));
    memcpy(n->data, e, sizeof(Request));
    n->next = NULL;
    if (l->size == 0) {
        l->first = n;
        l->last = n;
    } else {
        l->last->next = n;
        l->last = n;
    }
    l->size++;
    return 1;
}

//Boolean removeList(List* l, int index, Request *e) {
//    
//    Node *aux = l->first;
//    Node *remove = (Node*) malloc(sizeof (Node));
//    if (index == 0) {
//        removeFirstList(l, e);
//    } 
//    *e = remove->data;
//    free(remove);
//    l->size--;
//    return true;
//}
//
//Boolean removeFirstList(List* l, Request *e) {
//    if (isEmptyList(l)) {
//        return false;
//    }
//    Node *remove = l->first;
//    l->first = NULL;
//    l->last = NULL;
//    return true;
//}

Boolean removeFirstList(List* l, Request *e) {
    if (isEmptyList(l)) {
        return false;
    }
    e = l->first->data;
    Node *node = (Node*) malloc(sizeof(Node));
    node = l->first;
    l->first = l->first->next;
    
    free(node);
    l->size--;
    return true;
}

Boolean isEmptyList(List* l) {
    return l->size == 0;
}
