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

List *createList() {
    return (List*) malloc(sizeof (List));
}

void initializeList(List *l) {
    l->size = 0;
    l->first = NULL;
    l->last = NULL;
}

Boolean addLastList(List *l, Request e) {
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
    return 1;
}


Boolean removeFirstList(List* l, Request e) {
    if (isEmptyList(l)) {
        return false;
    }
    Node *remove = l->first;
    e = l->first->data;
    l->first = NULL;
    l->last = NULL;
    return true;
}

Boolean isEmptyList(List* l) {
    return l->size == 0;
}
