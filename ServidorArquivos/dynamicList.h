/* 
 * File:   dynamicList.h
 * Cabeçalhos das funções implementadas no módulo dynamicList.c ,
 * que servem para construir, adicionar, remover e imprimir dados de uma,
 * lista dinâmica de encadeamento simples.
 *
 * Obs: ItemType é um inteiro (int) <dever ser modificado para uma struct>
 *
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on 3 de Novembro de 2015, 09:28
 */

#ifndef DYNAMICLIST_H
#define	DYNAMICLIST_H

#include "request.h"


#define ItemType request


typedef struct node {
    ItemType data;
    struct node *next;
} Node;

typedef struct {
    Node *first;
    Node *last;
    int size;
} List;

 /*
	Retorna a estrutura de uma lista com o espaço alocado
 */
List *createList();

/*
 	Inicializa a estrutura da lista com valores nulos
 */
void initializeList(List *l);

/*
	Retorna true quando um ItemType foi adicionado na ultima posição da lista
	ou retorna false se não foi possivél adicionar.
 */
Boolean addLastList(List *l, ItemType e);

/*
	Retorna true quando um ItemType foi adicionado na primeira posição da lista
	ou retorna false se não foi possivél adicionar.
 */
Boolean addList(List* l, ItemType e, int index);

/*
	Retorna true quando um ItemType foi removido da posição passada como parâmetro 
	ou retorna false se não foi possivél remover.
 */
Boolean removeList(List* l, int index, ItemType *e);

/*
	Retorna true quando um ItemType foi removido da primeira posição 
	ou retorna false se não foi possivél remover.
 */
Boolean removeFirstList(List* l, ItemType* e);

/*
	Retorna true quando um ItemType foi removido da útima posição
	ou retorna false se não foi possivél remover.
 */
Boolean removeLastList(List* l, ItemType* e);

/*
	<verificar o q faz>
 */
Boolean getList(List* l, int index, ItemType* e);


/*
	<verificar o q faz>
 */
Boolean setList(List* l, int index, ItemType e);


/*
	Retorna a posição de um ItemType na lista se existir ou retorna -1 caso não exista.
 */
int indexOfList(List* l, ItemType* e);


/*
	Retorna true se o ItemType está na lista ou retorna false se o elemento não existir.
 */
Boolean containsList(List* l, ItemType *e);


/*
	Retorna true se a lista estiver vazia ou false se conter elemento(s).
 */
Boolean isEmptyList(List* l);


/*
	Imprime a lista
 */
void printList(List* l);


/*
	Imprime 0 ou 1 de acordo com o valor do booleano.
 */
void printBoolean(Boolean *b);


#ifdef	__cplusplus
}
#endif

#endif	/* DYNAMICLIST_H */

