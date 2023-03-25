#ifndef FILA_H
#define FILA_H

/*
    Módulo para operar filas estáticas circulares, sejam elas de qualquer tipo.
*/

typedef void * Item;
typedef void * Fila;

// Cria uma fila com espaço para N elementos
Fila createFila(int N);

// Insere um elemento na fila
void insertFila(Fila fila, Item item);

// Retira um elemento da fila
Item popFila(Fila fila);

// Verificar se a fila está vazia
int isFilaEmpty(Fila fila);

// Verificar se a fila está cheia
int isFilaFull(Fila fila);

// Conta quantos elementos existem na fila
int countFila(Fila fila);

// pegar inicio da fila
int getFilaInicio(Fila fila);

// pegar fim da fila
int getFilaFim(Fila fila);

// pegar tamanho da fila
int getFilaLength(Fila fila);

#endif