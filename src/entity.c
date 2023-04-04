#include "entity.h"
#include "fila.h"
#include "analyticGeometry.h"

#include <stdlib.h>
#include <stdio.h>

#define FILAS_AMOUNT 10
#define PICTURES_AMOUNT 15

struct Common {
    Geometry geo;
};

// Cada balão deve armazenar 10 filas de fotos. A implementação da fila deve ser circular, estática.
struct Balloon {
    Geometry geo;
    double radius;
    double depth;
    double height;
    Fila picsFila[FILAS_AMOUNT];
};

struct Warplane {
    Geometry geo;
    int shots;
    Lista targets;
};

typedef struct Explosive {
    char capacityType;
    double radius;
    double originCords[2];
    double targetCords[2];
} explosive;

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
    for (int i = 0; i < FILAS_AMOUNT; i++)
        e->attributes.balloon->picsFila[i] = createFila(PICTURES_AMOUNT);
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
    int i;
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
            for (i = 0; i < 10; i++)
                removeFila(e->attributes.balloon->picsFila[i]);
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
Entity searchEntbyIDinLst(Lista L, int id)
{
    Iterador it = createIterador(L, false);
    for (setIteratorPosition(L, it, getFirstLst(L)); getEntID(getIteratorItem(L, it)) != id; getIteratorNext(L, it))
    {} // Ao sair do for, it aponta para o elemento com o id desejado.
    Entity element = getIteratorItem(L, it);
    killIterator(L, it);
    return element;
}
//
/*
    Busca por uma forma geométrica armazenada como Entity dentro de uma lista L, dado um id válido.
    DEVE haver alguma forma com este id buscado. A função retorna a geometria com o ID desejado.
*/
Geometry searchGeobyIDinLst (Lista L, int id)
{
    Entity element = searchEntbyIDinLst(L, id);
    return getEntGeo(element);
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
void addEntPicture (Entity ent, Picture pic, int index)
{
    object * e = (object *) ent;
    insertFila(e->attributes.balloon->picsFila[index], (Item) pic);
}
Picture popEntPicture (Entity ent, int index)
{
    object * e = (object *) ent;
    Picture pic = (Picture) popFila(e->attributes.balloon->picsFila[index]);
    return pic;
}
/////////////////////////////////////////////



/////////////////////////////////////////////
// WARPLANE FUNCTIONS
// Warplane's actions
Bomb defineBomb (char capacityType, double Ox, double Oy, double distance, double theta)
{
    explosive * bomb = malloc(sizeof(explosive));
    bomb->capacityType = capacityType;
    bomb->originCords[0] = Ox;
    bomb->originCords[1] = Oy;
    switch (capacityType)
    {
        case 'a':
        case 'A':
            bomb->radius = BOMB_CAPACITY_A;
            break;
        case 'b':
        case 'B':
            bomb->radius = BOMB_CAPACITY_B;
            break;
        case 'c':
        case 'C':
            bomb->radius = BOMB_CAPACITY_C;
            break;
    }
    double * final = Translocation(Ox, Oy, distance, theta);
    bomb->targetCords[0] = final[0];
    bomb->targetCords[1] = final[1];
    return (Bomb) bomb;
}
void removeBomb (Bomb bomb)
{
    free((explosive *) bomb);
}
bool throwBomb (Entity ent, Bomb bomb)
{
    object * e = (object *) ent;
    Lista lst = e->attributes.warplane->targets;
    explosive * bb = (explosive *) bomb;
    Geometry geo = getEntGeo(ent);
    double Cx = bb->targetCords[0];
    double Cy = bb->targetCords[1];
    double radius = bb->radius;

    // Verificar se a entidade será atingida pela bomba
    switch (e->class)
    {
        case 'c':
        {
            // âncora do círculo está dentro da área da bomba -> destruir
            //return isPointInsideCircle(Cx, Cy, radius, getGeoCords(geo)[0], getGeoCords(geo)[1]);
            return isCircleInsideCircle(Cx, Cy, radius, getGeoCords(geo)[0], getGeoCords(geo)[1], getGeoRadius(geo));
            break;
        }
        case 'r':
        {
            return isCircleInsideRectangle(Cx, Cy, radius, 
                                           getGeoCords(geo)[0], getGeoCords(geo)[1],
                                           getGeoCords(geo)[0] + getGeoWidth(geo), getGeoCords(geo)[1] + getGeoHeight(geo)
                                           );
            break;
        }
        case 'l':
        {
            return isLineInsideCircle(getGeoAnchor_1(geo)[0], getGeoAnchor_1(geo)[1],
                                      getGeoAnchor_2(geo)[0], getGeoAnchor_2(geo)[1],
                                      Cx, Cy, radius);
            break;
        }

        case 'b':
        case 'd':
        case 't':
        {
            return isPointInsideCircle(Cx, Cy, radius, getGeoCords(geo)[0], getGeoCords(geo)[1]);
            break;
        }
    }
}
void incrementEntShots (Entity ent)
{
    object * e = (object *) ent;
    e->attributes.warplane->shots++;
}
//
void addEntTargetID (Entity ent, Entity warplane)
{
    object * e = (object *) warplane;
    Lista lst = e->attributes.warplane->targets;
    int * id = (int *) malloc(sizeof(int));
    *id = getEntID(ent);
    insertLst(lst, (Item) id);
}
int * popEntTargetID (Entity ent)
{
    object * e = (object *) ent;
    Lista lst = e->attributes.warplane->targets;
    if (isEmptyLst(lst))
        return NULL;
    else
    {
        static int targetID;
        targetID = *((int *) getLst(lst, getFirstLst(lst)));

        removeLst(lst, getFirstLst(lst));
        return &targetID;
    }
}
//
bool isEntinPicture(Entity ent, Entity balloon)
{
    object * bal = (object *) balloon;
    Geometry ballonGeo = bal->attributes.balloon->geo;
    object * e   = (object *) ent;
    Geometry eGeo = e->attributes.common->geo;
    double middleAnchor[2];
    double xi, yi, xf, yf;
    double r, d, h;

    r = getEntRadius (balloon);
    d = getEntDepth  (balloon);
    h = getEntHeight (balloon);
    switch (getGeoAnchor(ballonGeo))
    {
        case 'i':
        {
            middleAnchor[0] = getGeoCords(ballonGeo)[0]; // é preciso de uma constante para ajusat o centro do balão
            middleAnchor[1] = getGeoCords(ballonGeo)[1];
            break;
        }
        case 'm':
        {
            middleAnchor[0] = getGeoCords(ballonGeo)[0];
            middleAnchor[1] = getGeoCords(ballonGeo)[1];
            break;
        }
        case 'f':
        {
            middleAnchor[0] = getGeoCords(ballonGeo)[0]; // é preciso de uma constante para ajusat o centro do balão
            middleAnchor[1] = getGeoCords(ballonGeo)[1];
            break;
        }
    }
    
    xi = middleAnchor[0] - r;
    yi = middleAnchor[1] + d;

    xf = middleAnchor[0] + r;
    yf = middleAnchor[1] + d + h;
    
    // Analisar se geometria está dentro do quadro da foto
    switch (getEntType(ent))
    {
        case 'c':
        {
            return isCircleInsideRectangle(getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoRadius(eGeo), xi, yi, xf, yf);
            break;
        }
        case 'r':
        {
            return isRectangleInsideRectangle(
                getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], 
                getGeoCords(eGeo)[0] + getGeoWidth(eGeo), getGeoCords(eGeo)[1] + getGeoHeight(eGeo),
                xi, yi, xf, yf); // Coordenadas do retângulo da foto
            break;
        }
        case 'l':
        {
            return isLineInsideRectangle(
                getGeoAnchor_1(eGeo)[0], getGeoAnchor_1(eGeo)[1],
                getGeoAnchor_2(eGeo)[0], getGeoAnchor_2(eGeo)[1],
                xi, yi, xf, yf); // Coordenadas do retângulo da foto
            break;
        }
        case 'b':
        case 'd':
        case 't':
        {   
            if (getGeoCords(eGeo)[0] >= xi && getGeoCords(eGeo)[0] <= xf && getGeoCords(eGeo)[1] >= yi && getGeoCords(eGeo)[1] <= yf)
                return true;
            else
                return false;
            break;
        }
    }
}

void removeEntbyIDinLst (Entity ent, Lista L)
{
    int id = getEntID(ent);

    Iterador it = createIterador(L, false);
    for (setIteratorPosition(L, it, getFirstLst(L)); getEntID(getIteratorItem(L, it)) != id; getIteratorNext(L, it))
    {} // Ao sair do for, it aponta para o elemento com o id desejado.
    Posic pos = getIteratorPosic(L, it);
    killIterator(L, it);
    removeLst(L, pos);
}
/////////////////////////////////////////////



/////////////////////////////////////////////
// BOMB FUNCTIONS
double   getBombRadius         (Bomb bomb)
{
    explosive * bb = (explosive *) bomb;
    return bb->radius;
}
double * getBombOriginCord     (Bomb bomb)
{
    explosive * bb = (explosive *) bomb;
    return &bb->originCords[0];
}
double * getBombTargetCords    (Bomb bomb)
{
    explosive * bb = (explosive *) bomb;
    return &bb->targetCords[0];
}
/////////////////////////////////////////////