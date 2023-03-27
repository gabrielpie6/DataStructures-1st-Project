#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef void * Geometry;
typedef void * Style;

#define COLOR_STRING_SIZE 100

// Processing functions
void      Dislocate_Geo      (Geometry geo, double dx, double dy);
void      Rotate_Geo         (Geometry geo, double angle);
void      removeGeo          (Geometry geo);


// Create functions
Geometry  createCircle       (int id, double x, double y, double radius, char * colorBorder, char * colorFill);
Geometry  createRectangle    (int id, double x, double y, double width, double height, char * colorBorder, char * colorFill);
Geometry  createLine         (int id, double x1, double y1, double x2, double y2, char * colorFill);
Geometry  createText         (int id, double x, double y, char * colorBorder, char * colorFill, char anchor, char * text);
Style     createTextStyle    (char * fontFamily, char * fontWeight, double fontSize);

/// General functions
//  Getters
double *  getGeoCords        (Geometry geo);
double    getGeoAngle        (Geometry geo);
char      getGeoClass        (Geometry geo);
char   *  getGeoBorder_color (Geometry geo);
char   *  getGeoFill_color   (Geometry geo);
//
//  Setters
void      setGeoCords        (Geometry geo, double x, double y);
void      setGeoAngle        (Geometry geo, double angle);
void      setGeoClass        (Geometry geo, char class);
void      setGeoBorder_color (Geometry geo, char * color);
void      setGeoFill_color   (Geometry geo, char * color);


// Circle functions
double    getGeoRadius       (Geometry geo);
void      setGeoRadius       (Geometry geo, double radius);

// Rectangle functions
double    getGeoWidth        (Geometry geo);
double    getGeoHeight       (Geometry geo);
void      setGeoWidth        (Geometry geo, double width);
void      setGeoHeight       (Geometry geo, double height);

// Line functions
double  * getGeoAnchor_1     (Geometry geo);
double  * getGeoAnchor_2     (Geometry geo);
void      setGeoAnchor_1     (Geometry geo, double x, double y);
void      setGeoAnchor_2     (Geometry geo, double x, double y);

// Text functions
char      getGeoAnchor       (Geometry geo);
char    * getGeoText         (Geometry geo);
Style     getGeoStyle        (Geometry geo);
void      setGeoAnchor       (Geometry geo, char anchor);
void      setGeoText         (Geometry geo, char * text);
void      setGeoStyle        (Geometry geo, Style style);

// Style functions
void      removeStyle        (Style style);
char    * getStyleFontWeight (Style style);
char    * getStyleFontFamily (Style style);
double    getStyleFontSize   (Style style);
void      setStyleFontWeight (Style style, char * fontWeight);
void      setStyleFontFamily (Style style, char * fontFamily);
void      setStyleFontSize   (Style style, double fontSize);

#endif