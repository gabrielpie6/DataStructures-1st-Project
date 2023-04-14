#ifndef ACTIONS_H
#define ACTIONS_H

#include "lista.h"
#include "entity.h"
#include "cmdsFiles.h"
#include "drawSvg.h"

#include <stdio.h>

#define DEFAULT_BUFFER_SIZE 500
#define SHORT_PARAMETER_SIZE 50
#define SIMPLE_PARAMETER_SIZE 100
#define MEDIUM_PARAMETER_SIZE 250

/*
    Módulo destinado a prover funções de ações que podem ser executadas sob tipos de dados abstrato
    e arquivos SVG, TXT, de comandos e de dados relacionados. O módulo  compila operações de utilidade
    com múltiplas ações complexas sob os tipos de dados diferentes simultaneamente, de maneira a organizar,
    facilitar e tornar eficiente em invocações de diferentes locais, mas relacionados.

    Para TODAS as operações de escrita, além de respeitar as pré-condições de cada função, é necessário
    que suas respectivas entidades e/ou formas geométricas possuam atributos válidos para renderização
    em SVG, como CORES (borda e preenchimento) e ESTILOS DE TEXTOS (família da fonte, peso da fonte e tamanho da fonte).
    Caso contrário, o comportamento é indefinido.
*/



///////////////////////////////
// OUTPUT ACTIONS
//
/*
    Escreve uma dada lista de entidades L em um arquivo SVG válido, com um estilo de texto style a partir
    de uma posição (dx, dy) em relação ao canto superior esquerdo do arquivo SVG (origem).
    Pré-condição: L é uma lista de entidades válida, SVG é um arquivo SVG válido, style é um estilo de texto válido.
*/
void     WriteEntListInSvg             (ArqSvg SVG, Lista L, Style style, double dx, double dy);

/*
    Escreve uma dada lista de formas geométricas L em um arquivo SVG válido, com um estilo de texto style a partir
    de uma posição (dx, dy) em relação ao canto superior esquerdo do arquivo SVG (origem).
    Pré-condição: L é uma lista de formas geométricas válidas, SVG é um arquivo SVG válido, style é um estilo de texto válido.
*/
void     WriteGeoListInSvg             (ArqSvg SVG, Lista L, Style style, double dx, double dy);

/*
    Escreve uma entidade ent em um arquivo SVG válido, com um estilo de texto style a partir
    de uma posição (dx, dy) em relação ao canto superior esquerdo do arquivo SVG (origem). Para esta função,
    os parâmetros restantes passados devem estar organizado em clausura do seguinte formato:
        Clausura c[4];
        c[0] = SVG;
        c[1] = style;
        c[2] = dx;
        c[3] = dy;
    Pré-condição: ent é uma entidade válida e os parâmetros restantes devem respeitar a convenção
                  de clausura.
*/
void     writeEntInSVG                 (Entity ent, Clausura c);

/*
    Escreve uma forma geométrica element em um arquivo SVG válido, com um estilo de texto style a partir
    de uma posição (dx, dy) em relação ao canto superior esquerdo do arquivo SVG (origem). Para esta função,
    os parâmetros restantes passados devem estar organizados em clausura do seguinte formato:
        Clausura c[4];
        c[0] = SVG;
        c[1] = style;
        c[2] = dx;
        c[3] = dy;
    Pré-condição: element é uma forma geométrica válida e os parâmetros restantes devem respeitar a convenção
                  de clausura.
*/
void     writeGeoInSVG                 (Geometry element, Clausura c);

/*
    Escreve apenas os atributos básicos de uma entidade ent em um arquivo TXT TXTFile.
    Pré-condição: ent é uma entidade válida e TXTFile é um arquivo TXT válido.
*/
void     writeEntAttributesInTXT       (FILE * TXTFile, Entity ent);
///////////////////////////////

///////////////////////////////
// UTILS ACTIONS
//
/*
    Retorna uma cópia de uma entidade ent alocada em uma nova região de memória.
    Pré-condição: ent é uma entidade válida.
*/
Entity   copyEntity                    (Entity ent);

/*
    Realiza o cálculo da pontuação de uma entidade ent conforme convenção:
        - Texto: base = [número de caracteres]
            - é um caça CAÇA -> base = 100
        - Linha: base = [comprimento]
            - cor: #FFFF00 -> base *= 3
            - cor: #DDFF55 -> base *= 2
            - cor: #0000FF -> base *= 4
        - Círculo: base = [area]/2
            - borda: #FFFFFF e preenchimento: #FFFF00 -> base *= 8
            - borda: #D45500 e preenchimento: #FF7F2A -> base *= 2
            - borda: #AA0000 e preenchimento: #DE8787 -> base *= 4
            - borda: #FFFFFF e preenchimento: #B3B3B3 -> base *= 0
        - Retângulo: base = [area]/4
            - borda: #800080         -> base += 10
            - borda: #AA0088         -> base += 15
            - preenchimento: #008033 -> base += 20
            - preenchimento: #FFCC00 -> base += 30
    Retorna o valor de base calculado como a pontuação da entidade.
    Pré-condição: ent é uma entidade válida.
*/
double   scoreEnt                      (Entity ent);

/*
    Realiza a soma da pontuação de todas as entidades presentes na lista de elementos capturados
    pela foto pic e então retorna.
    Pré-condição: pic é uma foto válida.
*/
double   scorePicture                  (Picture pic);

/*
    Calcula os limites efetivos (total) de uma foto pic, ou seja, percorre todos as entidades presentes
    na foto e verifica qual é o espaço total ocupado por todas as entidades enquadradas o conjunto de entidades
    em uma única caixa delimitadora retangular, isto é, realizar o BoundingBox do conjunto formado pelas entidades.
    Retorna um vetor de 4 posições: (x mínimo, x máximo, y mínimo, y máximo), as dimensões totais da foto.
    Pré-condição: pic é uma foto válida.
*/
double * PictureBoundingBox            (Picture pic);

/*
    Ajusta a posição de uma entidade ent para a posição relativa à area de captura de uma foto, formado pelas coordenadas
    do canto superior esquerdo (xi, yi) e canto inferior direito (xf, yf). Para esta função, os parâmetros restantes passados devem estar
    organizados em clausura do seguinte formato:
        Clausura c[4];
        c[0] = xi;
        c[1] = yi;
        c[2] = xf;
        c[3] = yf;
    Pré-condição: ent é uma entidade válida e os parâmetros restantes devem respeitar a convenção
                  de clausura.
*/
void     ajustEntInFrame               (Entity ent, Clausura c);

/*
    Ajusta a posição de todas as entidades presentes na lista de elementos capturados pela foto pic para a posição relativa
    à area de captura da foto.
    Pré-condição: pic é uma foto válida.
*/
void     ajustElementsToRelativePicPos (Picture pic);

/*
    Define a área de captura de uma foto pic, formado pelas coordenadas do canto superior esquerdo (xi, yi) e
    canto inferior direito (xf, yf), previamente alocados.
    Pré-condição: pic é uma foto válida e xi, yi, xf e yf já devem ter memória alocada.
*/
void     defineFrame                   (Entity balloon, double * xi, double * yi, double * xf, double * yf);

/*
    Verifica se uma entidade ent está dentro da área de captura de fotos atual de um balão balloon.
    Retorna true se estiver e false caso contrário.
    Pré-condição: ent é uma entidade válida e balloon um balão válido com todos os parâmetros de captura de fotos
                  já definidos.
*/
bool     isEntinFrame                  (Entity ent, Entity balloon);

/*
    Dado uma entidade ent, obtém-se seu identificador e o busca na lista L fornecida, então remove a primeira entidadade
    encontra com identificador corrspondente que está DENTRO da lista L.
    Pré-condição: ent é uma entidade válida, L uma lista válida e o identificador de ent deve se referir a também uma
                  entidade válida pertencente a L.
*/
void     removeEntbyIDinLst            (Entity ent, Lista L);
///////////////////////////////

#endif