#ifndef ENTITY_H
#define ENTITY_H

#include "geometry.h"
#include "lista.h"
#include "fila.h"

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
Picture   createPicture         (double radius, double height, double depth, void * optional_list_of_elements);
Bomb      defineBomb            (char capacityType, double Ox, double Oy, double distance, double theta);

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
void      defineFrame           (Entity balloon, double * xi, double * yi, double * xf, double * yf);
bool      isEntinFrame          (Entity ent, Entity balloon);
void      removePicture         (Picture pic);
double    getPictureRadius      (Picture pic);
double    getPictureHeight      (Picture pic);
double    getPictureDepth       (Picture pic);
Lista     getPictureElements    (Picture pic);
void      addEntPicture         (Entity ent, Picture pic);
Entity    popEntPicture         (Picture pic);
void      addPictureInFila      (Entity balloon, Picture pic, int index);
Picture   popPictureInFila      (Entity balloon, int index);
Fila      getFilaOfPictures     (Entity balloon, int index);

// WARPLANE FUNCTIONS
// Warplane's actions
void      removeBomb            (Bomb bomb);
bool      throwBomb             (Entity ent, Bomb bomb);
void      incrementEntShots     (Entity ent);
void      addEntTargetID        (Entity ent, Entity warplane);
int     * popEntTargetID        (Entity ent);
void      removeEntbyIDinLst    (Entity ent, Lista L);


// BOMB FUNCTIONS
// Getters and Setters
double   getBombRadius         (Bomb bomb);
double * getBombOriginCord     (Bomb bomb);
double * getBombTargetCords    (Bomb bomb);

#endif