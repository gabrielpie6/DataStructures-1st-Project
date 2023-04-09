#include "actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///////////////////////////////
// OUTPUT ACTIONS
//
void writeGeoInSVG(Entity ent, Clausura c)
{
    void ** clausure =  (void   **) c;
    ArqSvg  SVG      =  (ArqSvg   ) clausure[0];
    Style   style    =  (Style    ) clausure[1];
    double  dx       = *((double *) clausure[2]);
    double  dy       = *((double *) clausure[3]);

    Geometry element = getEntGeo(ent);
    char deco[DEFAULT_BUFFER_SIZE];
    char font_size[SHORT_PARAMETER_SIZE];
    char text_anchor[20];
    switch (getGeoClass(element))
    {
        case 'c':
        {
            getGeoCords(element)[0] += dx;
            getGeoCords(element)[1] += dy;
            preparaDecoracao(SVG, deco, DEFAULT_BUFFER_SIZE, getGeoBorder_color(element), getGeoFill_color(element), "1", 1, 1, 1);
            escreveCirculoSvg(SVG, getGeoCords(element)[0], getGeoCords(element)[1], getGeoRadius(element), deco);
            break;
        };
        case 'r':
        {
            getGeoCords(element)[0] += dx;
            getGeoCords(element)[1] += dy;
            preparaDecoracao(SVG, deco, DEFAULT_BUFFER_SIZE, getGeoBorder_color(element), getGeoFill_color(element), "1", 1, 1, 1);
            escreveRetanguloSvg(SVG, getGeoCords(element)[0], getGeoCords(element)[1], getGeoWidth(element), getGeoHeight(element), deco);
            break;
        };
        case 'l':
        {
            getGeoAnchor_1(element)[0] += dx;
            getGeoAnchor_1(element)[1] += dy;
            getGeoAnchor_2(element)[0] += dx;
            getGeoAnchor_2(element)[1] += dy;
            preparaDecoracao(SVG, deco, DEFAULT_BUFFER_SIZE, getGeoBorder_color(element), getGeoFill_color(element), "1", 1, 1, 1);
            escreveLinhaSvg(SVG, getGeoAnchor_1(element)[0], getGeoAnchor_1(element)[1], getGeoAnchor_2(element)[0], getGeoAnchor_2(element)[1], deco);
            break;
        };
        case 't':
        {
            getGeoCords(element)[0] += dx;
            getGeoCords(element)[1] += dy;
            switch(getGeoAnchor(element))
            {
                case 'i':
                    strcpy(text_anchor, "start");
                    break;
                case 'm':
                    strcpy(text_anchor, "middle");
                    break;
                case 'f':
                    strcpy(text_anchor, "end");
                    break;
            }
            style = getGeoStyle(element);
            sprintf(font_size, "%lf", getStyleFontSize(style));
            preparaDecoracaoTexto(SVG, deco, DEFAULT_BUFFER_SIZE, getStyleFontFamily(style), text_anchor, getStyleFontWeight(style), font_size, getGeoFill_color(element), getGeoBorder_color(element), text_anchor);
            applyRotation(deco, DEFAULT_BUFFER_SIZE, getGeoAngle(element), getGeoCords(element)[0], getGeoCords(element)[1]);
            escreveTextoSvg(SVG, getGeoCords(element)[0], getGeoCords(element)[1], getGeoText(element), text_anchor, deco);
            break;
        };
    }
}

void WriteEntListInSvg(ArqSvg SVG, Lista L, Style style, double dx, double dy)
{
    void * clausure[4];
    clausure[0] = (void *) SVG;
    clausure[1] = (void *) style;
    clausure[2] = (void *) &dx;
    clausure[3] = (void *) &dy;
    fold(L, writeGeoInSVG, clausure);
}
///////////////////////////////




///////////////////////////////
// UTILS ACTIONS
//
Entity copyEntity (Entity ent)
{
    Entity newEnt;
    Geometry eGeo;
    switch (getEntType(ent))
    {
        case 'c':
        {
            eGeo = getEntGeo(ent);
            double theta = getGeoAngle(eGeo);
            eGeo = createCircle(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoRadius(eGeo), getGeoBorder_color(eGeo), getGeoFill_color(eGeo));
            setGeoAngle(eGeo, theta);
            newEnt = createCommon(eGeo, getEntID(ent));
            break;
        }
        case 'r':
        {
            eGeo = getEntGeo(ent);
            double theta = getGeoAngle(eGeo);
            eGeo = createRectangle(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoWidth(eGeo), getGeoHeight(eGeo), getGeoBorder_color(eGeo), getGeoFill_color(eGeo));
            setGeoAngle(eGeo, theta);
            newEnt = createCommon(eGeo, getEntID(ent));
            break;
        }
        case 'l':
        {
            eGeo = getEntGeo(ent);
            double theta = getGeoAngle(eGeo);
            eGeo = createLine(getEntID(ent), getGeoAnchor_1(eGeo)[0], getGeoAnchor_1(eGeo)[1], getGeoAnchor_2(eGeo)[0], getGeoAnchor_2(eGeo)[1], getGeoBorder_color(eGeo));
            setGeoAngle(eGeo, theta);
            newEnt = createCommon(eGeo, getEntID(ent));
            break;
        }
        case 't':
        {
            eGeo = getEntGeo(ent);
            Style style = getGeoStyle(eGeo);
            double theta = getGeoAngle(eGeo);
            eGeo = createText(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoBorder_color(eGeo), getGeoFill_color(eGeo), getGeoAnchor(eGeo), getGeoText(eGeo));
            setGeoStyle(eGeo, style);
            setGeoAngle(eGeo, theta);
            newEnt = createCommon(eGeo, getEntID(ent));
            break;
        }
        case 'b':
        {
            eGeo = getEntGeo(ent);
            Style style = getGeoStyle(eGeo);
            double theta = getGeoAngle(eGeo);
            eGeo = createText(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoBorder_color(eGeo), getGeoFill_color(eGeo), getGeoAnchor(eGeo), getGeoText(eGeo));
            setGeoStyle(eGeo, style);
            setGeoAngle(eGeo, theta);
            newEnt = createBalloon(eGeo, getEntID(ent));
        }
        case 'd':
        {
            eGeo = getEntGeo(ent);
            Style style = getGeoStyle(eGeo);
            double theta = getGeoAngle(eGeo);
            eGeo = createText(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoBorder_color(eGeo), getGeoFill_color(eGeo), getGeoAnchor(eGeo), getGeoText(eGeo));
            setGeoStyle(eGeo, style);
            setGeoAngle(eGeo, theta);
            newEnt = createWarplane(eGeo, getEntID(ent));
        }
    }
    return newEnt;
}


double scoreEnt(Entity ent)
{
    Geometry geo;

    int charLenght;
    double area, length, x1, y1, x2, y2, pontuacao = 0;
    char * borderColor;
    char * fillColor;
    switch(getEntType(ent))
    {
        case 'c':
        {
            geo = getEntGeo(ent);
            area = circleArea(getGeoRadius(geo));
            borderColor = getGeoBorder_color(geo);
            fillColor = getGeoFill_color(geo);
            if (strcmp(borderColor, "FFFFFF") == 0 && strcmp(fillColor, "FFFF00") == 0)
                pontuacao += (area/2) * 8;
            else
            if (strcmp(borderColor, "D45500") == 0 && strcmp(fillColor, "FF7F2A") == 0)
                pontuacao += (area/2) * 2;
            else
            if (strcmp(borderColor, "AA0000") == 0 && strcmp(fillColor, "DE8787") == 0)
                pontuacao += (area/2) * 4;
            else
            if (strcmp(borderColor, "AA0000") == 0 && strcmp(fillColor, "DE8787") == 0)
                pontuacao += (area/2) * 0;
            else
                pontuacao += (area/2);
            break;
        }
        case 'r':
        {
            geo = getEntGeo(ent);
            area = rectangleArea(getGeoWidth(geo), getGeoHeight(geo));
            borderColor = getGeoBorder_color(geo);
            fillColor = getGeoFill_color(geo);

            // Falta um dígito em 80080?
            pontuacao += area / 4;
            if (strcmp(borderColor, "80080") == 0) pontuacao += 10; else
            if (strcmp(borderColor, "AA0088") == 0) pontuacao += 15; else
            if (strcmp(fillColor,   "008033") == 0) pontuacao += 20; else
            if (strcmp(fillColor,   "FFCC00") == 0) pontuacao += 30;
            break;
        }
        case 'l':
        {
            geo = getEntGeo(ent);
            
            x1 = getGeoAnchor_1(geo)[0];
            y1 = getGeoAnchor_1(geo)[1];
            x2 = getGeoAnchor_2(geo)[0];
            y2 = getGeoAnchor_2(geo)[1];
            length = distance(x1, y1, x2, y2);
            borderColor = getGeoBorder_color(geo);

            if (strcmp(borderColor, "FFFF00") == 0) pontuacao += length * 3; else
            if (strcmp(borderColor, "DDFF55") == 0) pontuacao += length * 2; else
            if (strcmp(borderColor, "0000FF") == 0) pontuacao += length * 4; else
            pontuacao += length;
            
            break;
        }
        case 'b':
        case 't':
        {
            geo = getEntGeo(ent);
            charLenght = strlen(getGeoText(geo));
            pontuacao += charLenght;
            break;
        }
        case 'd':
        {
            pontuacao += 100;
            break;
        }
    }
    return pontuacao;
}


double scorePicture(Picture pic)
{
    double pontuacao = 0;
    Entity ent = popEntPicture(pic);
    while (ent != NULL)
    {
        pontuacao += scoreEnt(ent);
        ent = popEntPicture(pic);
    }
    return pontuacao;
}
///////////////////////////////