#ifndef FILA_H
#define FILA_H

#include "dataTypes.h"
#include <stdbool.h>

/*
    Módulo para operar filas estáticas circulares.
*/

typedef void * Fila;

/*
    Cria uma fila com capacidade para N elementos e a retorna.
    Pré-condição: N deve ser maior que 0.
*/
Fila createFila(int N);

/*
    Insere o elemento item no fim da fila fornecida.
    Pré-condição: a fila não deve estar cheia. Caso estiver, não executa nenhuma operação.
*/
void insertFila(Fila fila, Item item);

/*
    Remove o elemento do início da fila fornecida e o retorna. Índices da fila são atualizados.
    Pré-condição: a fila não deve estar vazia. Caso estiver, retorna NULL.
*/
Item popFila(Fila fila);

/*
    Verifica se a fila está vazia, retorna (true) 1 se estiver e (false) 0 caso contrário.
*/
bool isFilaEmpty(Fila fila);

/*
    Verifica se a fila está cheia, retorna (true) 1 se estiver e (false) 0 caso contrário.
*/
bool isFilaFull(Fila fila);

/*
    Conta quantos elementos existem na fila fornecida e retorna um inteiro que representa a quantidade.
    Pré-condição: a fila não deve estar vazia. Caso estiver, retorna 0.
*/
int countFila(Fila fila);

/*
    Retorna o índice no círculo da fila, em sentido horário, que está o elemento do início da fila.
*/
int getFilaInicio(Fila fila);

/*
    Retorna o índice no círculo da fila, em sentido horário, que está o elemento do fim da fila.
*/
int getFilaFim(Fila fila);

/*
    Retorna o tamanho estático da fila fornecida.
*/
int getFilaLength(Fila fila);

#endif