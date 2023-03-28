#ifndef ENTITY_H
#define ENTITY_H

#include "geometry.h"
#include "lista.h"

typedef void * Entity;
typedef void * Picture;
typedef void * Bomb;

#define BOMB_CAPACITY_A 10
#define BOMB_CAPACITY_B 15
#define BOMB_CAPACITY_C 30

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
bool      isEntinPicture        (Entity ent, Entity balloon);
void      addEntPicture         (Entity ent, Picture pic, int index);
Picture   popEntPicture         (Entity ent, int index);

// WARPLANE FUNCTIONS
// Warplane's actions
Bomb      defineBomb            (char capacityType, double Ox, double Oy, double distance, double theta);
void      removeBomb            (Bomb bomb);
bool      throwBomb             (Entity ent, Bomb bomb);
void      incrementEntShots     (Entity ent);
void      addEntTargetID        (Entity ent, Entity warplane);
int       popEntTargetID        (Entity ent);
void      removeEntbyIDinLst    (Entity ent, Lista L);


// BOMB FUNCTIONS
// Getters and Setters
/*
char capacityType;
    double radius;
    double originCord[2];
    double targetCords[2];
*/
double   getBombRadius         (Bomb bomb);
double * getBombOriginCord     (Bomb bomb);
double * getBombTargetCords    (Bomb bomb);

#endif