#ifndef DATA_TYPES_H
#define DATA_TYPES_H

/*
    Módulo de cabeçalho apenas para definição de tipos abstratos de dados comuns em estruturas de dados.
*/

/*
    Item é um tipo abstrato de dado que representa um elemento genérico de armazenagem de uma
    estrutura de dados, é o "conteúdo". Pode ser qualquer tipo de dado, contudo este será operado
    mediante as funções de cada estrutura de dados, isto é, respeitará as regras de cada estrutura,
    como em uma lista ou em uma fila.
*/
typedef void * Item;

#endif