// IMPLEMETAÇÃO UTILIZANDO void * attributes


#include "geometry.h"

#include <stdlib.h>

// #define DEFAULT_TEXT_SIZE 500
// #define STRING_COLOR_SIZE 100

/////////////////////////////////////////////
// Implementação das ESTRUTURAS escolhidas
//
struct Circle {
    double radius;
};

struct Rectangle {
    double height;
    double weigth;
};

struct Line {
    double anchor_1[2];
    double anchor_2[2];
};

struct Text {
    char anchor;
    char * text;
};

struct TextStyle {
    char * font_family;
    char * font_weight;
    double font_size;
};

typedef struct Object {
    int id;
    double cords[2];
    double angle;
    char * colors[2];
    char class;
    void * attributes;
} object;
/////////////////////////////////////////////



/////////////////////////////////////////////
// FUNÇÕES DE PROCESSAMENTO
//

// mv
void Dislocate_Geo (Geometry geo, double dx, double dy)
{
    object * obj = (object *) geo;
    obj->cords[0] += dx;
    obj->cords[1] += dy; 
}

// g (apenas para texto)
void Rotate_Geo (Geometry geo, double angle)
{
    object * obj = (object *) geo;
    obj->angle += angle;
}
/////////////////////////////////////////////



/////////////////////////////////////////////
// FUNÇÕES DE CRIAÇÃO
//
Geometry createCircle (int id, double x, double y, double radius, char * colorBorder, char * colorFill)
{
    object * obj = malloc(sizeof(object));
    obj->id = id;
    obj->cords[0] = x;
    obj->cords[1] = y;
    obj->angle = 0;
    obj->colors[0] = colorBorder;
    obj->colors[1] = colorFill;

    obj->class = 'c';
    obj->attributes = malloc(sizeof(struct Circle));

    struct Circle * circulo = (struct Circle *) obj->attributes;
    circulo->radius = radius;

    return (Geometry) obj;
}

Geometry createRectangle (int id, double x, double y, double weigth, double height, char * colorBorder, char * colorFill)
{
    object * obj = malloc(sizeof(object));
    obj->id = id;
    obj->cords[0] = x;
    obj->cords[1] = y;
    obj->angle = 0;
    obj->colors[0] = colorBorder;
    obj->colors[1] = colorFill;

    obj->class = 'r';
    obj->attributes = malloc(sizeof(struct Rectangle));

    struct Rectangle * retangulo = (struct Rectangle *) obj->attributes;
    retangulo->weigth = weigth;
    retangulo->height = height;

    return (Geometry) obj;
}

Geometry createLine (int id, double x1, double y1, double x2, double y2, char * colorFill)
{
    object * obj = malloc(sizeof(object));
    obj->id = id;
    obj->cords[0] = x1;
    obj->cords[1] = y1;
    obj->angle = 0;
    
    obj->colors[0] = NULL;
    obj->colors[1] = colorFill;

    obj->class = 'l';
    obj->attributes = malloc(sizeof(struct Line));

    struct Line * linha = (struct Line *) obj->attributes;
    linha->anchor_1[0] = x1;
    linha->anchor_1[1] = y1;
    linha->anchor_2[0] = x2;
    linha->anchor_2[1] = y2;

    return (Geometry) obj;
}

Geometry createText (int id, double x, double y, char * colorBorder, char * colorFill, char anchor, char * text)
{
    object * obj = malloc(sizeof(object));
    obj->id = id;
    obj->cords[0] = x;
    obj->cords[1] = y;
    obj->angle = 0;
    obj->colors[0] = colorBorder;
    obj->colors[1] = colorFill;

    obj->class = 't';
    obj->attributes = malloc(sizeof(struct Text));

    struct Text * texto = (struct Text *) obj->attributes;
    texto->anchor = anchor;
    texto->text = text;

    return (Geometry) obj;
}

Style createTextStyle (char * fontFamily, char * fontWeigth, double fontSize)
{
    struct TextStyle * style = malloc(sizeof(struct TextStyle));
    style->font_family = fontFamily;
    style->font_weight = fontWeigth;
    style->font_size   = fontSize;

    return (Style) style;
}
/////////////////////////////////////////////



/////////////////////////////////////////////
// GENERAL FUNCTIONS
// Getters
int getGeoID (Geometry geo)
{
    object * obj = (object *) geo;
    return obj->id;
}
double * getGeoCords (Geometry geo)
{
    object * obj = (object *) geo;
    return &obj->cords[0];
}
double getGeoAngle (Geometry geo)
{
    object * obj = (object *) geo;
    return obj->angle;
}
char getGeoClass (Geometry geo)
{
    object * obj = (object *) geo;
    return obj->class;
}
char * getGeoBorder_color (Geometry geo)
{
    object * obj = (object *) geo;
    return obj->colors[0];
}
char * getGeoFill_color (Geometry geo)
{
    object * obj = (object *) geo;
    return obj->colors[1];
}
//
// Setters
//
void setGeoID (Geometry geo, int id)
{
    object * obj = (object *) geo;
    obj->id = id;
}
void setGeoCords (Geometry geo, double x, double y)
{
    object * obj = (object *) geo;
    obj->cords[0] = x;
    obj->cords[1] = y;
}
void setGeoAngle (Geometry geo, double angle)
{
    object * obj = (object *) geo;
    obj->angle = angle;
}
void setGeoClass (Geometry geo, char class)
{
    object * obj = (object *) geo;
    obj->class = class;
}
void setGeoBorder_color (Geometry geo, char * color)
{
    object * obj = (object *) geo;
    obj->colors[0] = color;
}
void setGeoFill_color (Geometry geo, char * color)
{
    object * obj = (object *) geo;
    obj->colors[1] = color;
}
/////////////////////////////////////////////



/////////////////////////////////////////////
// GEOMETRY ATTRIBUTES FUNCTIONS
//
// Circle functions
//
double getGeoRadius (Geometry geo)
{
    object * obj = (object *) geo;
    struct Circle * circulo = (struct Circle *) obj->attributes;
    return circulo->radius;
}
void setGeoRadius (Geometry geo, double radius)
{
    object * obj = (object *) geo;
    struct Circle * circulo = (struct Circle *) obj->attributes;
    circulo->radius = radius;
}
//
// Rectangle functions
//
double getGeoWeigth (Geometry geo)
{
    object * obj = (object *) geo;
    struct Rectangle * retangulo = (struct Rectangle *) obj->attributes;
    return retangulo->weigth;
}
double getGeoHeight (Geometry geo)
{
    object * obj = (object *) geo;
    struct Rectangle * retangulo = (struct Rectangle *) obj->attributes;
    return retangulo->height;
}
void setGeoWeigth (Geometry geo, double weigth)
{
    object * obj = (object *) geo;
    struct Rectangle * retangulo = (struct Rectangle *) obj->attributes;
    retangulo->weigth = weigth;
}
void setGeoHeight (Geometry geo, double height)
{
    object * obj = (object *) geo;
    struct Rectangle * retangulo = (struct Rectangle *) obj->attributes;
    retangulo->height = height;
}
//
// Line functions
//
double * getGeoAnchor_1 (Geometry geo)
{
    object * obj = (object *) geo;
    struct Line * linha = (struct Line *) obj->attributes;
    return &linha->anchor_1[0];
}
double * getGeoAnchor_2 (Geometry geo)
{
    object * obj = (object *) geo;
    struct Line * linha = (struct Line *) obj->attributes;
    return &linha->anchor_2[0];
}
void setGeoAnchor_1 (Geometry geo, double x, double y)
{
    object * obj = (object *) geo;
    struct Line * linha = (struct Line *) obj->attributes;
    linha->anchor_1[0] = x;
    linha->anchor_1[1] = y;
}
void setGeoAnchor_2 (Geometry geo, double x, double y)
{
    object * obj = (object *) geo;
    struct Line * linha = (struct Line *) obj->attributes;
    linha->anchor_2[0] = x;
    linha->anchor_2[1] = y;
}
//
// Text functions
//
char getGeoAnchor (Geometry geo)
{
    object * obj = (object *) geo;
    struct Text * texto = (struct Text *) obj->attributes;
    return texto->anchor;
}
char * getGeoText (Geometry geo)
{
    object * obj = (object *) geo;
    struct Text * texto = (struct Text *) obj->attributes;
    return texto->text;
}
void setGeoAnchor (Geometry geo, char anchor)
{
    object * obj = (object *) geo;
    struct Text * texto = (struct Text *) obj->attributes;
    texto->anchor = anchor;
}
void setGeoText (Geometry geo, char * text)
{
    object * obj = (object *) geo;
    struct Text * texto = (struct Text *) obj->attributes;
    texto->text = text;
}
//
// Style functions
//
// Style functions
char * getStyleFontWeigth (Style style)
{
    struct TextStyle * textStyle = (struct TextStyle *) style;
    return textStyle->font_weight;
}
char * getStyleFontFamily (Style style)
{
    struct TextStyle * textStyle = (struct TextStyle *) style;
    return textStyle->font_family;
}
double getStyleFontSize (Style style)
{
    struct TextStyle * textStyle = (struct TextStyle *) style;
    return textStyle->font_size;
}
void removeStyle (Style style)
{
    struct TextStyle * textStyle = (struct TextStyle *) style;
    free(textStyle->font_family);
    free(textStyle->font_weight);
    //free(&textStyle->font_size);
    free(textStyle);
}
/////////////////////////////////////////////