#include "entity.h"

#include <stdlib.h>

struct Common {
    Geometry geo;
};

// Cada balão deve armazenar 10 filas de fotos. A implementação da fila deve ser circular, estática.
struct Balloon {
    Geometry geo;
    double radius;
    double depth;
    double height;
    Lista picsList;
};

struct Warplane {
    Geometry geo;
    int shots;
    Lista targets;
};

// CONVENÇÃO DE TIPOS
/*
    Common:
        'c' : circle
        'r' : rectangle
        'l' : line
        't' : text
    Balloon:
        'b' : balloon
    Warplane:
        'd' : warplane
*/
// Formato de entidade genérica
typedef struct Object {
    int id;
    char class;
    union Attributes {
        struct Common   * common;
        struct Balloon  * balloon;
        struct Warplane * warplane;
    } attributes;
} object;




/////////////////////////////////////////////
// CREATION FUNCTIONS
//
Entity createCommon(Geometry geo, int id)
{
    object * e =  malloc(sizeof(object));
    e->id = id;
    e->class = getGeoClass(geo);
    e->attributes.common = (struct Common *) malloc(sizeof(struct Common));
    e->attributes.common->geo = geo;
    return (Entity) e;
}
//
// arrumar a inicialização de 10 filas dentro da lista
Entity createBalloon(Geometry geo, int id)
{
    object * e =  malloc(sizeof(object));
    e->id = id;
    e->class = 'b';
    e->attributes.balloon = (struct Balloon *) malloc(sizeof(struct Balloon));
    e->attributes.balloon->geo = geo;
    e->attributes.balloon->radius = 0;
    e->attributes.balloon->depth = 0;
    e->attributes.balloon->height = 0;
    e->attributes.balloon->picsList = createLst(10);
    return (Entity) e;
}
//
Entity createWarplane(Geometry geo, int id)
{
    object * e =  malloc(sizeof(object));
    e->id = id;
    e->class = 'd';
    e->attributes.warplane = (struct Warplane *) malloc(sizeof(struct Warplane));
    e->attributes.warplane->geo = geo;
    e->attributes.warplane->shots = 0;
    e->attributes.warplane->targets = createLst(-1);
    return (Entity) e;
}



/////////////////////////////////////////////
// PROCESSING FUNCTIONS
//
void removeEntity(Entity ent)
{
    object * e = (object *) ent;
    switch (e->class) 
    {
        case 'c':
        case 'r':
        case 'l':
        case 't':
            removeGeo(e->attributes.common->geo);
            free(e->attributes.common);
            break;
        case 'b':
            removeGeo(e->attributes.balloon->geo);
            killLst(e->attributes.balloon->picsList);
            free(e->attributes.balloon);
            break;
        case 'd':
            removeGeo(e->attributes.warplane->geo);
            killLst(e->attributes.warplane->targets);
            free(e->attributes.warplane);
            break;
    }
    free(e);
}
//
/*
    Busca por uma forma geométrica armazenada como item dentro de uma lista L, dado um id válido.
    DEVE haver alguma forma com este id buscado. A função retorna a geometria com o ID desejado.
*/
Geometry searchGeobyIDinLst (Lista L, int id)
{
    Iterador it = createIterador(L, false);
    for (setIteratorPosition(L, it, getFirstLst(L)); getEntID(getIteratorItem(L, it)) != id; getIteratorNext(L, it))
    {} // Ao sair do for, it aponta para o elemento com o id desejado.
    Geometry element = getEntGeo((Geometry) getIteratorItem(L, it));
    killIterator(L, it);
    return element;
};
/////////////////////////////////////////////



/////////////////////////////////////////////
// GENERAL FUNCTIONS
//
int getEntID(Entity ent)
{
    object * e = (object *) ent;
    return e->id;
}
//
char getEntType(Entity ent)
{
    object * e = (object *) ent;
    return e->class;
}
//
Geometry getEntGeo(Entity ent)
{
    object * e = (object *) ent;
    switch (e->class) 
    {
        case 'c':
        case 'r':
        case 'l':
        case 't':
            return e->attributes.common->geo;
        case 'b':
            return e->attributes.balloon->geo;
        case 'd':
            return e->attributes.warplane->geo;
    }
}
/////////////////////////////////////////////




/////////////////////////////////////////////
// BALLON FUNCTIONS
// Getters and Setters
void setEntDepth (Entity ent, double depth)
{
    object * e = (object *) ent;
    e->attributes.balloon->depth = depth;
}
double getEntDepth (Entity ent)
{
    object * e = (object *) ent;
    return e->attributes.balloon->depth;
}
void setEntHeight (Entity ent, double height)
{
    object * e = (object *) ent;
    e->attributes.balloon->height = height;
}
double getEntHeight (Entity ent)
{
    object * e = (object *) ent;
    return e->attributes.balloon->height;
}
void setEntRadius (Entity ent, double radius)
{
    object * e = (object *) ent;
    e->attributes.balloon->radius = radius;
}
double getEntRadius (Entity ent)
{
    object * e = (object *) ent;
    return e->attributes.balloon->radius;
}
//
// Balloon's pictures
//
void addEntPicture (Entity ent, Picture pic)
{
    //printf("funcao a implementar: addEntPicture\n");
}
Picture popEntPicture (Entity ent)
{
    //printf("funcao a implementar: popEntPicture\n");
}
/////////////////////////////////////////////



/////////////////////////////////////////////
// WARPLANE FUNCTIONS
// Warplane's actions
void incrementEntShots (Entity ent)
{
    object * e = (object *) ent;
    e->attributes.warplane->shots++;
}
//
void addEntTargetID (Entity ent, int targetID)
{
    object * e = (object *) ent;
    Lista lst = e->attributes.warplane->targets;
    int * id = (int *) malloc(sizeof(int));
    *id = targetID;
    insertLst(lst, (Item) id);
}
int popEntTargetID (Entity ent)
{
    object * e = (object *) ent;
    Lista lst = e->attributes.warplane->targets;
    int * id = (int *) getLst(lst, getFirstLst(lst));
    int targetID = *id;

    free(id);
    removeLst(lst, getFirstLst(lst));
    return targetID;
}
/////////////////////////////////////////////