#ifndef QRY_FILE_H
#define QRY_FILE_H

#include "actions.h"

#include <stdio.h>

///////////////////////////////
// .qry ACTIONS
//
/*
    Lê um arquivo .qry e executa todas as ações contidas no arquivo, então retorna true.
    Se não for possível ler o arquivo, ou haver comandos desconhecidos no arquivo, retorna false.
*/
bool   ReadQryFile          (Lista L, char * qryPath, char * outputPath, char * geo_qryCombination, Style style);

void   moveEntity           (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile);
void   rotateEntity         (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile);
void   setPictureFocus      (ArqCmds QryFile, Lista L, char * lineBuffer);
void   takePicture          (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile);
void   downloadPictures     (ArqCmds QryFile, Lista L, char * lineBuffer, char * outputPath, char * geo_qryCombination, Style style, FILE * TXTFile);
void   detonateBomb         (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile);

#endif