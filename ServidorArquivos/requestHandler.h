/* 
 * File:   request.h
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 17, 2015, 1:40 PM
 */

#ifndef REQUESTHANDLER_H
#define	REQUESTHANDLER_H

#include "connection.h"
#include "request.h"
#include "dynamicList.h"
#include "server.h"

/* Aguarda que o usuário digite alguma coisa,
 * depois manda o buffer para o resquest que verifica
 * a requisição digitada
 */
void* aguardaRequisicao(void* args);
void* addList(Request *req);

#endif
