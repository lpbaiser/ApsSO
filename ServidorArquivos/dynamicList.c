/* 
 * File:   request.h
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 17, 2015, 1:40 PM
 */
#include "request.h"
#include <stdio.h>
#include <stdlib.h>

#define ItemType request



typedef enum {
    false, true
} Boolean;

List *createList();
void initializeList(List *l);
Boolean addLastList(List *l, ItemType e);
Boolean addList(List* l, ItemType e, int index);
Boolean removeList(List* l, int index, ItemType *e);
Boolean removeFirstList(List* l, ItemType* e);
Boolean removeLastList(List* l, ItemType* e);
Boolean getList(List* l, int index, ItemType* e);
Boolean setList(List* l, int index, ItemType e);
int indexOfList(List* l, ItemType* e);
Boolean containsList(List* l, ItemType *e);
Boolean isEmptyList(List* l);
void printList(List* l);
void printBoolean(Boolean *b);



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

Boolean addList(List* l, ItemType e, int index) {
    Node *n = (Node*) malloc(sizeof (Node));
    n->data = e;
    if ((l->size == 0) || (l->size == index)) {
        addLastList(l, e);
        return true;
    } else if ((index > l->size) || (index < 0)) {
        return false;
    } else {
        int i;
        Node *aux = l->first;
        for (i = 0; i < index - 1; i++) {
            aux = aux->next;
        }
        n->next = aux->next;
        aux->next = n;
        l->size++;
        return true;
    }
}

Boolean removeList(List* l, int index, ItemType *e) {
    if (!containsList(l, e)) {
        return false;
    }
    Node *aux = l->first;
    Node *remove = (Node*) malloc(sizeof (Node));
    if (index == 0) {
        removeFirstList(l, e);
    } else if ((index + 1) == l->size) {
        removeLastList(l, e);
    } else {
        int i;
        for (i = 0; i < index - 1; i++) {
            aux = aux->next;
        }
        remove = aux->next;
        aux->next = aux->next->next;
    }
    *e = remove->data;
    free(remove);
    l->size--;
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

Boolean removeLastList(List* l, ItemType *e) {
    if (isEmptyList(l)) {
        return false;
    }
    Node *remove = (Node*) malloc(sizeof (Node));
    if (l->size == 1) {
        removeFirstList(l, e);
    } else {
        int i;
        Node *aux = l->first;
        for (i = 0; i < l->size - 2; i++) {
            aux = aux->next;
        }
        remove = l->last;
        aux->next = NULL;
        l->last = aux;
    }
    *e = remove->data;
    free(remove);
    l->size--;

    return true;
}

Boolean getList(List* l, int index, ItemType* e) {
    if (l->size == 0) {
        return true;
    }
    int i;
    Node *get = l->first;
    for (i = 0; i < index; i++) {
        get = get->next;
    }
    *e = get->data;
    return false;
}

Boolean setList(List* l, int index, ItemType e) {
    if (l->size == 0) {
        return false;
    }
    int i;
    Node *set = l->first;
    for (i = 0; i < index; i++) {
        set = set->next;
    }
    set->data = e;
    return true;
}

int indexOfList(List* l, ItemType* e) {
    if (isEmptyList(l)) {
        return -1;
    }
    int i = 0;
    Node *aux = l->first;
    for (i = 0; i < l->size; i++) {
        if (aux->data == *e) {
            return i;
        }
        aux = aux->next;
    }
    return -1;
}

Boolean containsList(List* l, ItemType *e) {
    if (isEmptyList(l)) {
        return false;
    }
    int i = indexOfList(l, e);
    if (i != -1) {
        return true;
    }
    return false;
}

Boolean isEmptyList(List* l) {
    return l->size == 0;
}

void printList(List* l) {
    Node *i = l->first;
    printf("- - - - print - - - - \n");
    while (i != NULL) {
        printf("%d\n", i->data);
        i = i->next;
    }
    printf("\n- - - - end print - - - - \n");
}

void printBoolean(Boolean *b) {
    if (*b == 1) {
        printf("true;\n");
    } else {
        printf("false;\n");
    }
}
