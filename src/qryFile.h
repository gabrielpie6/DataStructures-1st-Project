#ifndef QRY_FILE_H
#define QRY_FILE_H

#include "actions.h"

#include <stdio.h>

/*
    Módulo que provê as oito funções essencias para a leitura de arquivos *.qry e interpretação de suas linhas,
    juntamente à função geral que realiza o processamento da leitura e redirecionamento para as funções específicas.

    ORGANIZAÇÃO DO ARQUIVO *.qry: é organizado em linhas, onde cada linha é uma ação a ser realizada.
        Cada ação é representada por uma letra, seguida de parâmetros que variam de acordo com a ação, como nos seguintes
        exemplos:
            "mv [id] [x] [y]"
            "g [id] [rotação em graus (sentido horário)]"
            "ff [id] [raio] [profundidade] [altura]"
            "tf [id] [índice da fila]"
            "df [id] [índice da fila] [sufixo]"
            "d [id] [capacidade de explosão] [distância de explosão] [valor inicial do índice de clones] [deslocamento dx]"
            "b?"
            "c?"
*/


///////////////////////////////
// .qry ACTIONS
//
/*
    Realiza a leitura de um arquivo *.qry localizado em qryPath e interpreta todas as linhas de comandos contidas nele.
    Pode ser necessário gerar novos arquivos de saída, para isto, o caminho de saída é passado por outputPath e geo_qryCombination
    é uma string que contém o nome do arquivo geo e qry, sem extensão ambos, concatenados respectivamente com um hífen.
    O estilo de textos corrente é passado por style, e a lista de decorações que podem ser atribuidas
    para escrita no SVG final é passada por Decos.
    Retorna true se a leitura e interpretação do arquivo *.qry foi realizada com sucesso, false caso contrário.
    Pré-condição: L é uma lista válida, qryPath é um caminho válido para um arquivo *.qry, outputPath é um caminho válido para um diretório,
                  geo_qryCombination é uma string válida, style é um estilo válido, Decos é uma lista válida.
*/
bool   ReadQryFile          (Lista L, char * qryPath, char * outputPath, char * geo_qryCombination, Style style, Lista Decos);


/*
    Realiza a interpretação de uma linha lineBuffer que se sabe ser referente à operação de movimentação de uma entidade
    a partir de um arquivo de comandos QryFile, sob uma lista de entidade L. Após a operação, o arquivo TXTFile é atualizado
    com novas informações relatando o resultado da operação sob a entidade.
    Pré-condição: QryFile é um arquivo válido, L é uma lista válida, lineBuffer é uma string válida, TXTFile é um arquivo válido.
*/
void   moveEntity           (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile);

/*
    Realiza a interpretação de uma linha lineBuffer que se sabe ser referente à operação de rotação de uma entidade
    a partir de um arquivo de comandos QryFile, sob uma lista de entidade L. Após a operação, o arquivo TXTFile é atualizado
    com novas informações relatando o resultado da operação sob a entidade.
    Pré-condição: QryFile é um arquivo válido, L é uma lista válida, lineBuffer é uma string válida, TXTFile é um arquivo válido.
*/
void   rotateEntity         (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile);

/*
    Realiza a interpretação de uma linha lineBuffer que se sabe ser referente à operação de focalização de captura de fotos de um balão
    a partir de um arquivo de comandos QryFile, sob uma lista de entidade L.
    Pré-condição: QryFile é um arquivo válido, L é uma lista válida, lineBuffer é uma string válida.
*/
void   setPictureFocus      (ArqCmds QryFile, Lista L, char * lineBuffer);

/*
    Realiza a interpretação de uma linha lineBuffer que se sabe ser referente à operação de captura de foto por um balão
    a partir de um arquivo de comandos QryFile, sob uma lista de entidade L. Após a operação, o arquivo TXTFile é atualizado
    com novas informações relatando o resultado da operação de captura, reportando todas as entidades fotografadas.
    Pré-condição: QryFile é um arquivo válido, L é uma lista válida, lineBuffer é uma string válida, TXTFile é um arquivo válido.
*/
void   takePicture          (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile, Lista Decos);

/*
    Realiza a interpretação de uma linha lineBuffer que se sabe ser referente à operação de baixar fotos de um balão para a base
    conforme convenção de pontuações definida em actions.h, a partir de um arquivo de comandos QryFile, sob uma lista de entidade L.
    Um arquivo SVG é gerado com o nome de geo_qryCombination e salvo em outputPath, contendo todas as fotos baixadas em sequência.
        Após a operação, o arquivo TXTFile é atualizado com novas informações relatando o resultado da operação de baixar fotos.
    Pré-condição: QryFile é um arquivo válido, L é uma lista válida, lineBuffer é uma string válida, TXTFile é um arquivo válido,
                  outputPath é um caminho válido para um diretório, geo_qryCombination é uma string válida.

*/
void   downloadPictures     (ArqCmds QryFile, Lista L, char * lineBuffer, char * outputPath, char * geo_qryCombination, Style style, FILE * TXTFile);

/*
    Realiza a interpretação de uma linha lineBuffer que se sabe ser referente à operação de detonação de uma bomba
    a partir de um arquivo de comandos QryFile, sob uma lista de entidade L. Todas as entidades que foram detonadas geram
    uma nova forma geométrica de texto "X" em vermelho (#FF0000) com centro nas coordenadas da entidade atingida, então esta é
    inserida na lista Decos, e, ao final, as entidades atingidas são removidas da lista L. (ver actions.h).
        Após a operação, o arquivo TXTFile é atualizado com novas informações relatando o resultado da operação de detonação,
    reportando todas as entidades atingidas.
    Pré-condição: QryFile é um arquivo válido, L é uma lista válida, lineBuffer é uma string válida, TXTFile é um arquivo válido.
*/
void   detonateBomb         (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile, Lista Decos);

/*
    Realiza a interpretação de uma linha lineBuffer que se sabe ser referente à operação de reportar dados de balões
    a partir de um arquivo de comandos QryFile, sob uma lista de entidade L. Após a operação, o arquivo TXTFile é atualizado
    com novas informações relatando o resultado da operação de reportar dados de balões, reportando todas as informações
    de todos os balões presentes na lista L e informações específicas de cada balão.
    Pré-condição: QryFile é um arquivo válido, L é uma lista válida, lineBuffer é uma string válida, TXTFile é um arquivo válido.
*/
void   reportBalloonsData   (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile);

/*
    Realiza a interpretação de uma linha lineBuffer que se sabe ser referente à operação de reportar dados de caças
    a partir de um arquivo de comandos QryFile, sob uma lista de entidade L. Após a operação, o arquivo TXTFile é atualizado
    com novas informações relatando o resultado da operação de reportar dados de caças, reportando todas as informações
    de todos os caças presentes na lista L e informações específicas de cada caça.
    Pré-condição: QryFile é um arquivo válido, L é uma lista válida, lineBuffer é uma string válida, TXTFile é um arquivo válido.
*/
void   reportWarplanesData  (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile);

#endif