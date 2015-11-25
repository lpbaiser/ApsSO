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

#include "requestHandler.h"
#include "request.h"

//typedef Request ItemType;

typedef struct node {
    Request data;
    struct node *next;
} Node;

typedef struct {
    Node *first;
    Node *last;
    int size;
} List;

typedef enum {
    false, true
} Boolean;

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
Boolean addLastList(List *l, Request e);

/*
        Retorna true quando um ItemType foi removido da primeira posição 
        ou retorna false se não foi possivél remover.
 */
Boolean removeFirstList(List* l, Request e);

/*
        Retorna true se a lista estiver vazia ou false se conter elemento(s).
 */
Boolean isEmptyList(List* l);

#endif	/* DYNAMICLIST_H */

