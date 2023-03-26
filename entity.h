#ifndef ENTITY_H
#define ENTITY_H

#include "geometry.h"
#include "lista.h"

typedef void * Entity;
typedef void * Picture;

// CREATION FUNCTIONS
Entity    createCommon          (Geometry geo, int id);
Entity    createBalloon         (Geometry geo, int id);
Entity    createWarplane        (Geometry geo, int id);

// PROCESSING FUNCTIONS
void      removeEntity          (Entity ent);
Entity    searchEntbyIDinLst    (Lista L, int id);
Geometry  searchGeobyIDinLst    (Lista L, int id);

// GENERAL FUNCTIONS
char      getEntType            (Entity ent);
int       getEntID              (Entity ent);
Geometry  getEntGeo             (Entity ent);

// BALLON FUNCTIONS
// Getters and Setters
void      setEntDepth           (Entity ent, double depth);
double    getEntDepth           (Entity ent);
void      setEntHeight          (Entity ent, double height);
double    getEntHeight          (Entity ent);
void      setEntRadius          (Entity ent, double radius);
double    getEntRadius          (Entity ent);
// Balloon's pictures
void      addEntPicture         (Entity ent, Picture pic, int index);
Picture   popEntPicture         (Entity ent, int index);

// WARPLANE FUNCTIONS
// Warplane's actions
void      incrementEntShots     (Entity ent);
void      addEntTargetID        (Entity ent, int targetID);
int       popEntTargetID        (Entity ent);
#endif