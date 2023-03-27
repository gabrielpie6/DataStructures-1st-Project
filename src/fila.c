#include "fila.h"

#include <stdlib.h>

struct FilaType {
    int inicio;
    int fim;
    int tamanho;
    Item * stack;
};

// Cria uma fila com espaço para N elementos
Fila createFila(int N)
{
    struct FilaType *p;
    p = (struct FilaType *) malloc (sizeof(struct FilaType));

    p->stack = malloc(sizeof(Item) * N);
    p->tamanho = N;
    p->inicio = 0;
    p->fim = -1;

    return p;
}

// Insere um elemento na fila
void insertFila(Fila fila, Item item)
{
    // pré-condição: fila não deve estar cheia. Caso seja, fazer nada.
    if (isFilaFull(fila) == 0)
    {
        struct FilaType *p = (struct FilaType *) fila;

        int indice = (p->fim + 1) % (p->tamanho);
        p->stack[indice] = item;
        p->fim = indice;
    }
}

// Retira um elemento da fila
Item popFila(Fila fila)
{
    // pré-condição de execução: fila não deve ser vazia. Caso seja, retorna (Item) NULL
    if (isFilaEmpty(fila) == 0)
    {
        struct FilaType *p = (struct FilaType *) fila;

        // valor = primeiro elemento da fila
        Item item = p->stack[p->inicio];

        if (p->inicio == p->fim)
        {
            // Fila AGORA está vazia, então reiniciar a fila com valores iniciais
            p->fim = -1;
            p->inicio = 0;
        }
        else
        {
            // Fila AINDA possui elemento(s), então atualizar índice de início
            p->inicio = (p->inicio + 1) % (p->tamanho);
        }

        return item;
    }
    else
        return NULL;
}

// Verificar se a fila está vazia
bool isFilaEmpty(Fila fila)
{
    struct FilaType *p = (struct FilaType *) fila;

    if (p->fim == -1)
        return 1;
    else
        return 0;
}

// Verificar se a fila está cheia
bool isFilaFull(Fila fila)
{
    struct FilaType *p = (struct FilaType *) fila;

    // SE índice de fim for imeditamente anterior ao índice ínicio quando analisados
    // em formato polar (relógio).
    int valor = p->inicio - 1;
    if (valor < 0)
       valor += p->tamanho; 
    if (p->fim == (p->inicio - 1) % (p->tamanho) && p->fim >= 0)
        return 1;
    else
        return 0;
}

// Conta quantos elementos existem na fila
int countFila(Fila fila)
{
    struct FilaType *p = (struct FilaType *) fila;
    int valor;
    
    if (p->fim < 0)
        return 0;
    
    if (p->fim > p->inicio)
        valor = p->fim - p->inicio;
    else
        valor = p->fim - p->inicio + (p->tamanho);

    return ((valor % (p->tamanho)) + 1);
}

int getFilaInicio (Fila fila)
{
    struct FilaType *p = (struct FilaType *) fila;
    return p->inicio;
}

int getFilaFim (Fila fila)
{
    struct FilaType *p = (struct FilaType *) fila;
    return p->fim;
}

int getFilaLength (Fila fila)
{
    struct FilaType *p = (struct FilaType *) fila;
    return p->tamanho;
}

void removeFila(Fila fila)
{
    struct FilaType *p = (struct FilaType *) fila;
    free(p->stack);
    free(p);
}