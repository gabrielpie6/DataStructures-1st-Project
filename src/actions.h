#ifndef ACTIONS_H
#define ACTIONS_H

#include "lista.h"
#include "entity.h"
#include "geometry.h"
#include "cmdsFiles.h"
#include "analyticGeometry.h"
#include "drawSvg.h"


#define DEFAULT_BUFFER_SIZE 500
#define SHORT_PARAMETER_SIZE 50
#define SIMPLE_PARAMETER_SIZE 100
#define MEDIUM_PARAMETER_SIZE 250



///////////////////////////////
// OUTPUT ACTIONS
//
void writeGeoInSVG(Entity ent, Clausura c);
void WriteEntListInSvg(ArqSvg SVG, Lista L, Style style, double dx, double dy);
///////////////////////////////

///////////////////////////////
// UTILS ACTIONS
//
Entity copyEntity (Entity ent);
double scoreEnt             (Entity ent);
double scorePicture         (Picture pic);
///////////////////////////////

#endif