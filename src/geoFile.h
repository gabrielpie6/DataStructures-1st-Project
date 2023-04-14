#ifndef GEO_FILE_H
#define GEO_FILE_H

#include "actions.h"

/*
    Módulo que provê as cinco funções essencias para a leitura de arquivos *.geo e interpretação de suas linhas,
    juntamente à função geral que realiza o processamento da leitura e redirecionamento para as funções específicas.

    ORGANIZAÇÃO DO ARQUIVO *.geo: é organizado em linhas, onde cada linha é uma ação a ser realizada.
        Cada ação é representada por uma letra, seguida de parâmetros que variam de acordo com a ação, como nos seguintes
        exemplos:
            "c [id] [x] [y] [r] [cor da borda] [cor do preenchimento]"
            "r [id] [x] [y] [largura] [altura] [cor da borda] [cor do preenchimento]"
            "l [id] [x1] [y1] [x2] [y2] [cor]"
            "t [id] [x] [y] [cor da borda] [cor do preenchimento] [caractere de controle da âncora] [texto (até o fim da linha)]"
            "ts [família do texto] [peso do texto] [tamanho do texto]"
*/


///////////////////////////////
// .geo ACTIONS
//
/*
    Realiza a leitura de um arquivo *.geo localizado em geoPath e retorna uma lista com todas as
    entidades lidas e interpretadas. Um estilo padrão de texto defaultStyle é passado para evitar
    casos onde o usuário não define um estilo de textos para ser usado.
    Pré-condição: geoPath é um caminho válido para um arquivo *.geo.
*/
Lista  ReadGeoFile          (char * geoPath, Style defaultStyle);

/*
    Realiza a interpretação de uma linha que se sabe ser referente a uma ação de criação de um círculo
    a partir de um arquivo de comandos GeoFile. lineBuffer é uma string que contém a linha a ser interpretada.
    Retorna a entidade criada.
    Pré-condição: GeoFile é um arquivo de comandos *.geo com instruções válidas, lineBuffer é uma string que contém
                  uma linha válida.
*/
Entity readActCircle        (ArqCmds GeoFile, char * lineBuffer);

/*
    Realiza a interpretação de uma linha que se sabe ser referente a uma ação de criação de um retângulo
    a partir de um arquivo de comandos GeoFile. lineBuffer é uma string que contém a linha a ser interpretada.
    Retorna a entidade criada.
    Pré-condição: GeoFile é um arquivo de comandos *.geo com instruções válidas, lineBuffer é uma string que contém
                  uma linha válida.
*/
Entity readActRectangle     (ArqCmds GeoFile, char * lineBuffer);

/*
    Realiza a interpretação de uma linha que se sabe ser referente a uma ação de criação de uma linha
    a partir de um arquivo de comandos GeoFile. lineBuffer é uma string que contém a linha a ser interpretada.
    Retorna a entidade criada.
    Pré-condição: GeoFile é um arquivo de comandos *.geo com instruções válidas, lineBuffer é uma string que contém
                  uma linha válida.
*/
Entity readActLine          (ArqCmds GeoFile, char * lineBuffer);

/*
    Realiza a interpretação de uma linha que se sabe ser referente a uma ação de criação de um texto
    a partir de um arquivo de comandos GeoFile. lineBuffer é uma string que contém a linha a ser interpretada.
    Associa o estilo de texto previamente cirado style à entidade criada.
    Retorna a entidade criada.
    Pré-condição: GeoFile é um arquivo de comandos *.geo com instruções válidas, lineBuffer é uma string que contém
                  uma linha válida, style é um estilo de texto válido.
*/
Entity readActText          (ArqCmds GeoFile, char * lineBuffer, Style style);

/*
    Realiza a interpretação de uma linha que se sabe ser referente a uma ação de criação de um estilo de texto
    a partir de um arquivo de comandos GeoFile. lineBuffer é uma string que contém a linha a ser interpretada.
    O novo estilo de texto alterado sob um estilo de texto criado previamente createedStyle.
    Pré-condição: GeoFile é um arquivo de comandos *.geo com instruções válidas, lineBuffer é uma string que contém
                  uma linha válida, createdStyle é um estilo de texto válido.
*/
void   readActTextStyle     (ArqCmds GeoFile, char * lineBuffer, Style createdStyle);

#endif