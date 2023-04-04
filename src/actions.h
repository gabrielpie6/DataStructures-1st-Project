#ifndef ACTIONS_H
#define ACTIONS_H

#include "lista.h"
#include "entity.h"
#include "geometry.h"
#include "cmdsFiles.h"


#define DEFAULT_BUFFER_SIZE 500
#define SHORT_PARAMETER_SIZE 50
#define SIMPLE_PARAMETER_SIZE 100
#define MEDIUM_PARAMETER_SIZE 250


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


///////////////////////////////



///////////////////////////////
// .qry ACTIONS
//
/*
    Lê um arquivo .qry e executa todas as ações contidas no arquivo, então retorna true.
    Se não for possível ler o arquivo, ou haver comandos desconhecidos no arquivo, retorna false.
*/
bool   ReadQryFile          (Lista L, char * qryPath);

void   moveEntity           (ArqCmds QryFile, Lista L, char * lineBuffer);
void   rotateEntity         (ArqCmds QryFile, Lista L, char * lineBuffer);
void   setPictureFocus      (ArqCmds QryFile, Lista L, char * lineBuffer);
void   takePicture          (ArqCmds QryFile, Lista L, char * lineBuffer);
void   downloadPictures     (ArqCmds QryFile, Lista L, char * lineBuffer);
void   detonateBomb         (ArqCmds QryFile, Lista L, char * lineBuffer);


///////////////////////////////



///////////////////////////////
// OUTPUT ACTIONS
//
void writeGeoInSVG(Entity ent, Clausura c);
void WriteInSvg(char * svgFilePath, Lista L, Style style);
///////////////////////////////

#endif