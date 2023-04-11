#ifndef ACTIONS_H
#define ACTIONS_H

#include "lista.h"
#include "entity.h"
#include "cmdsFiles.h"
#include "drawSvg.h"


#define DEFAULT_BUFFER_SIZE 500
#define SHORT_PARAMETER_SIZE 50
#define SIMPLE_PARAMETER_SIZE 100
#define MEDIUM_PARAMETER_SIZE 250



///////////////////////////////
// OUTPUT ACTIONS
//
void     WriteEntListInSvg             (ArqSvg SVG, Lista L, Style style, double dx, double dy);
void     WriteGeoListInSvg             (ArqSvg SVG, Lista L, Style style, double dx, double dy);
void     writeEntInSVG                 (Entity ent, Clausura c);
void     writeGeoInSVG                 (Geometry element, Clausura c);
///////////////////////////////

///////////////////////////////
// UTILS ACTIONS
//
Entity   copyEntity                    (Entity ent);
double   scoreEnt                      (Entity ent);
double   scorePicture                  (Picture pic);

double * PictureBoundingBox            (Picture pic);
void     ajustElementsToRelativePicPos (Entity balloon, Lista elements);
void     defineFrame                   (Entity balloon, double * xi, double * yi, double * xf, double * yf);
bool     isEntinFrame                  (Entity ent, Entity balloon);

void     removeEntbyIDinLst            (Entity ent, Lista L);
///////////////////////////////

#endif