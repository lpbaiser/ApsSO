/* 
 * File:   main.c
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on 3 de Novembro de 2015, 09:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <dynamicList.h>

/*
 * 
 */
int main(int argc, char** argv) {

       List *l = createList();
    initializeList(l);
    ItemType e = 123;
    Boolean b;
    addList(l, 123, 0);
    addList(l, 456, 1);
    addList(l, 789, 2);
    addLastList(l, 10);
    printList(l);
        removeList(l, 3, &e);
        removeList(l, 0, &e);
        removeList(l, 2, &e);
    //    b = containsList(l, &e);
    //    printBoolean(&b);
//    removeLastList(l, &e);
//    removeLastList(l, &e);
//    removeLastList(l, &e);
//    removeLastList(l, &e);
    //    getList(l, 1, &e);
    //    printf("GET: %d\n", e);
    //    setList(l, 1, 854);
    //    getList(l, 1, &e);
    //    printf("GET: %d\n", e);
    printList(l);
}

