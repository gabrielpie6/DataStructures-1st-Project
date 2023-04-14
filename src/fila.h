#ifndef FILA_H
#define FILA_H

#include "dataTypes.h"
#include <stdbool.h>

/*
    Módulo para operar filas estáticas circulares. Possui funções básicas de operação,
    contagem e validação. Cada fila possui um tamanho estático N, definido na criação,
    pode-se inserir no máximo N elementos abstratos (Item) e também pode-se remover
    estes elementos, desde que a fila não esteja vazia.
    Ao atingir a capacidade máxima, a fila não pode mais receber novos elementos.

    DEFINIÇÃO:
        Uma fila é um conjunto de elementos ordenados que respeitam uma regra passa acesso, alteração e
        remoção. Ao ser criada, possui um tamanho máximo fixo. Para operar uma fila, é necessário tê-la criada.
        Para operar qualquer elemento de uma fila, é necessário que a fila não esteja vazia e também que o elemento
        (Item) desejado seja retirado da fila (popFila), pois a fila não permite acesso direto a seus elementos
        por índices. A fila é uma estrutura de dados do tipo FIFO (First In, First Out), ou seja, o primeiro
        elemento a entrar na fila é o primeiro a sair dela.

    (Item) referenciado em dataTypes.h
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

/*
    Remove toda a memória alocada pela fila fornecida.
*/
void removeFila(Fila fila);

#endif