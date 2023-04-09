#ifndef GEO_FILE_H
#define GEO_FILE_H

#include "actions.h"

///////////////////////////////
// .geo ACTIONS
//
/*
    Lê um arquivo .geo e retorna uma lista conténdo todas as entidades lidas pelo arquivo.
    Se não for possível ler o arquivo, ou haver comandos desconhecidos no arquivo, retorna NULL.
*/
Lista  ReadGeoFile          (char * geoPath, Style defaultStyle);

Entity readActCircle        (ArqCmds GeoFile, char * lineBuffer);
Entity readActRectangle     (ArqCmds GeoFile, char * lineBuffer);
Entity readActLine          (ArqCmds GeoFile, char * lineBuffer);
Entity readActText          (ArqCmds GeoFile, char * lineBuffer, Style style);
void   readActTextStyle     (ArqCmds GeoFile, char * lineBuffer, Style createdStyle);

#endif