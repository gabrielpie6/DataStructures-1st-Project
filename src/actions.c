#include "actions.h"

#include "analyticGeometry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///////////////////////////////
// OUTPUT ACTIONS
//
void writeEntInSVG(Entity ent, Clausura c)
{
    Geometry element = getEntGeo(ent);
    writeGeoInSVG(element, c);
}
void writeGeoInSVG(Geometry element, Clausura c)
{
    void ** clausure =  (void   **) c;
    ArqSvg  SVG      =  (ArqSvg   ) clausure[0];
    Style   style    =  (Style    ) clausure[1];
    double  dx       = *((double *) clausure[2]);
    double  dy       = *((double *) clausure[3]);

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
    fold(L, writeEntInSVG, clausure);
}
void WriteGeoListInSvg (ArqSvg SVG, Lista L, Style style, double dx, double dy)
{
    void * clausure[4];
    clausure[0] = (void *) SVG;
    clausure[1] = (void *) style;
    clausure[2] = (void *) &dx;
    clausure[3] = (void *) &dy;
    fold(L, writeGeoInSVG, clausure);
}
//
void writeEntAttributesInTXT (FILE * TXTFile, Entity ent)
{
    Geometry geo;
    geo = getEntGeo(ent);
    switch(getEntType(ent))
    {
        case 'c':
        {
            // id, centro, raio, cor de borda, cor de preenchimento
            fprintf(TXTFile, "\t[id: %d] - tipo: circulo, centro: (%.2lf, %.2lf), cor de borda: %s, cor de preenchimento: %s\n", getEntID(ent), getGeoCords(geo)[0], getGeoCords(geo)[1], getGeoBorder_color(geo), getGeoFill_color(geo));
            break;
        }
        case 'r':
        {
            // id, ancora, largura, altura, cor de borda, cor de preenchimento
            fprintf(TXTFile, "\t[id: %d] - tipo: retangulo, ancora: (%.2lf, %.2lf), largura: %.2lf, altura: %.2lf, cor de borda: %s, cor de preenchimento: %s\n", getEntID(ent), getGeoCords(geo)[0], getGeoCords(geo)[1], getGeoWidth(geo), getGeoHeight(geo), getGeoBorder_color(geo), getGeoFill_color(geo));
            break;
        }
        case 'l':
        {
            // id, ancoras, cor de borda
            fprintf(TXTFile, "\t[id: %d] - tipo: linha, ancoras: [(%.2lf, %.2lf), (%.2lf, %.2lf)], cor de borda: %s\n", getEntID(ent), getGeoAnchor_1(geo)[0], getGeoAnchor_1(geo)[1], getGeoAnchor_2(geo)[0], getGeoAnchor_2(geo)[1], getGeoBorder_color(geo));
            break;
        }
        case 't':
        {
            // id, ancora, pos. da ancora, cor de borda, cor de preenchimento
            fprintf(TXTFile, "\t[id: %d] - tipo: texto, ancora: (%.2lf, %.2lf), pos. da ancora: %c, cor de borda: %s, cor de preenchimento: %s\n", getEntID(ent), getGeoCords(geo)[0], getGeoCords(geo)[1], getGeoAnchor(geo), getGeoBorder_color(geo), getGeoFill_color(geo));
            break;
        }
        case 'b':
        {
            // id, ancora, cor de borda, cor de preenchimento
            fprintf(TXTFile, "\t[id: %d] - tipo: balao, ancora: (%.2lf, %.2lf), cor de borda: %s, cor de preenchimento: %s\n", getEntID(ent), getGeoCords(geo)[0], getGeoCords(geo)[1], getGeoBorder_color(geo), getGeoFill_color(geo));
            break;
        }
        case 'd':
        {
            // id, ancora, disparos realizados, alvos atingidos, cor de borda, cor de preenchimento
            fprintf(TXTFile, "\t[id: %d] - tipo: caca, ancora: (%.2lf, %.2lf), disparos realizados: %d, alvos atingidos: %d, cor de borda: %s, cor de preenchimento: %s\n", getEntID(ent), getGeoCords(geo)[0], getGeoCords(geo)[1], getEntShots(ent), lengthLst(getEntTargetsID(ent)), getGeoBorder_color(geo), getGeoFill_color(geo));
            break;
        }
    }
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
            break;
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
            for (int i = 0; i < getEntShots(ent); i++)
                incrementEntShots(newEnt);
            // copia a lista de ids dos alvos atingidos
            setEntTargetsID(newEnt, getEntTargetsID(ent));
            break;
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
            if (strcmp(borderColor, "#FFFFFF") == 0 && strcmp(fillColor, "#FFFF00") == 0)
                pontuacao += (area/2) * 8;
            else
            if (strcmp(borderColor, "#D45500") == 0 && strcmp(fillColor, "#FF7F2A") == 0)
                pontuacao += (area/2) * 2;
            else
            if (strcmp(borderColor, "#AA0000") == 0 && strcmp(fillColor, "#DE8787") == 0)
                pontuacao += (area/2) * 4;
            else
            if (strcmp(borderColor, "#AA0000") == 0 && strcmp(fillColor, "#DE8787") == 0)
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
            // 11/04/2023 - foi definido que é 800080
            pontuacao += area / 4;
            if (strcmp(borderColor, "#800080") == 0) pontuacao += 10; else
            if (strcmp(borderColor, "#AA0088") == 0) pontuacao += 15; else
            if (strcmp(fillColor,   "#008033") == 0) pontuacao += 20; else
            if (strcmp(fillColor,   "#FFCC00") == 0) pontuacao += 30;
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

            if (strcmp(borderColor, "#FFFF00") == 0) pontuacao += length * 3; else
            if (strcmp(borderColor, "#DDFF55") == 0) pontuacao += length * 2; else
            if (strcmp(borderColor, "#0000FF") == 0) pontuacao += length * 4; else
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


void aux_scorePicture(Entity ent, Clausura clausura)
{
    double * pontuacao = (double *) clausura;
    *pontuacao += scoreEnt(ent);
}
double scorePicture(Picture pic)
{
    double pontuacao = 0;
    Lista elements = getPictureElements(pic);
    fold(elements, aux_scorePicture, (Clausura) &pontuacao);
    return pontuacao;
}


double * PictureBoundingBox (Picture pic)
{
    double leftLimit = 0;
    double rightLimit = getPictureRadius(pic) * 2;
    double topLimit = 0;
    double bottomLimit = getPictureHeight(pic);

    Lista elements = getPictureElements(pic);
    Posic p = getFirstLst(elements);
    Entity ent;
    Geometry geo;
    double value;

    for (int i = 0; i < lengthLst(elements); i++)
    {
        ent = getLst(elements, p);
        geo = getEntGeo(ent);
        switch(getGeoClass(geo))
        {
            case 'c':
            {
                value = getGeoCords(geo)[0] - getGeoRadius(geo);
                if (value < leftLimit) leftLimit = value;
                value = getGeoCords(geo)[0] + getGeoRadius(geo);
                if (value > rightLimit) rightLimit = value;
                value = getGeoCords(geo)[1] - getGeoRadius(geo);
                if (value < topLimit) topLimit = value;
                value = getGeoCords(geo)[1] + getGeoRadius(geo);
                if (value > bottomLimit) bottomLimit = value;
                break;
            }
            case 'r':
            {
                value = getGeoCords(geo)[0];
                if (value < leftLimit) leftLimit = value;
                value = getGeoCords(geo)[0] + getGeoWidth(geo);
                if (value > rightLimit) rightLimit = value;
                value = getGeoCords(geo)[1];
                if (value < topLimit) topLimit = value;
                value = getGeoCords(geo)[1] + getGeoHeight(geo);
                if (value > bottomLimit) bottomLimit = value;
                break;
            }
            case 'l':
            {
                if (getGeoAnchor_1(geo)[0] < getGeoAnchor_2(geo)[0])
                {
                    value = getGeoAnchor_1(geo)[0];
                    if (value < leftLimit) leftLimit = value;
                    value = getGeoAnchor_2(geo)[0];
                    if (value > rightLimit) rightLimit = value;
                }
                else
                {
                    value = getGeoAnchor_2(geo)[0];
                    if (value < leftLimit) leftLimit = value;
                    value = getGeoAnchor_1(geo)[0];
                    if (value > rightLimit) rightLimit = value;
                }
                break;
            }
            case 't':
            {
                // Não é preciso fazer nada
                break;
            }
        }
        p = getNextLst(elements, p);
    }
    double * limits = malloc(sizeof(double) * 4);
    limits[0] = leftLimit;
    limits[1] = rightLimit;
    limits[2] = topLimit;
    limits[3] = bottomLimit;
    return limits;
}
//
void ajustEntInFrame(Entity ent, Clausura c)
{
    void ** clausures =  (void **  ) c;
    double  xi        = *((double *) clausures[0]);
    double  yi        = *((double *) clausures[1]);
    double  xf        = *((double *) clausures[2]);
    double  yf        = *((double *) clausures[3]);
    
    Geometry eGeo = getEntGeo(ent);
    switch(getGeoClass(eGeo))
    {
        case 'c':
        {
            getGeoCords(eGeo)[0] -= xi;
            getGeoCords(eGeo)[1] -= yi;
            break;
        }
        case 'r':
        {
            getGeoCords(eGeo)[0] -= xi;
            getGeoCords(eGeo)[1] -= yi;
            break;
        }
        case 'l':
        {
            getGeoAnchor_1(eGeo)[0] -= xi;
            getGeoAnchor_1(eGeo)[1] -= yi;
            getGeoAnchor_2(eGeo)[0] -= xi;
            getGeoAnchor_2(eGeo)[1] -= yi;
            break;
        }
        case 't':
        {
            getGeoCords(eGeo)[0] -= xi;
            getGeoCords(eGeo)[1] -= yi;
            break;
        }
    }
    
}
//
void ajustElementsToRelativePicPos (Picture pic)
{
    // Ajuste das coordenadas das entidades para posição relativa ao frame da foto
    double xi, yi, xf, yf;
    xi = getPictureCords(pic)[0];
    yi = getPictureCords(pic)[1];
    xf = getPictureCords(pic)[0] + getPictureRadius(pic) * 2;
    yf = getPictureCords(pic)[1] + getPictureHeight(pic);
    void * clausures[4];
    clausures[0] = (void *) &xi;
    clausures[1] = (void *) &yi;
    clausures[2] = (void *) &xf;
    clausures[3] = (void *) &yf;
    Lista elements = getPictureElements(pic);
    fold(elements, ajustEntInFrame, (Clausura) clausures);
}
void defineFrame (Entity balloon, double * xi, double * yi, double * xf, double * yf)
{
    Geometry ballonGeo = getEntGeo(balloon);
    double middleAnchor[2];
    double r, d, h;

    r = getEntRadius (balloon);
    d = getEntDepth  (balloon);
    h = getEntHeight (balloon);
    switch (getGeoAnchor(ballonGeo))
    {
        case 'i':
        {
            middleAnchor[0] = getGeoCords(ballonGeo)[0]; // é preciso de alguma variável para ajustar o centro do balão
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
            middleAnchor[0] = getGeoCords(ballonGeo)[0]; // é preciso de alguma variável para ajustar o centro do balão
            middleAnchor[1] = getGeoCords(ballonGeo)[1];
            break;
        }
    }
    
    *xi = middleAnchor[0] - r;
    *yi = middleAnchor[1] + d;

    *xf = middleAnchor[0] + r;
    *yf = middleAnchor[1] + d + h;
}
bool isEntinFrame(Entity ent, Entity balloon)
{
    Geometry eGeo = getEntGeo(ent);
    double xi, yi, xf, yf;
    defineFrame(balloon, &xi, &yi, &xf, &yf);
    
    // Analisar se geometria está dentro do quadro da foto
    switch (getEntType(ent))
    {
        case 'c':
        {
            if (isCircleInsideRectangle(getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoRadius(eGeo), xi, yi, xf, yf))
            {
                // Ajustar as coordenadas da forma geométrica para posição relativa da foto
                return true;
            }
            else
                return false;
            break;
        }
        case 'r':
        {
            if (isRectangleInsideRectangle(
                getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], 
                getGeoCords(eGeo)[0] + getGeoWidth(eGeo), getGeoCords(eGeo)[1] + getGeoHeight(eGeo),
                xi, yi, xf, yf)) // Coordenadas do retângulo da foto
            {
                return true;
            } 
            else
                return false;
            break;
        }
        case 'l':
        {
            if (isLineInsideRectangle(
                getGeoAnchor_1(eGeo)[0], getGeoAnchor_1(eGeo)[1],
                getGeoAnchor_2(eGeo)[0], getGeoAnchor_2(eGeo)[1],
                xi, yi, xf, yf)) // Coordenadas do retângulo da foto
            {
                // Ajustar as coordenadas da forma geométrica para posição relativa da foto
                return true;
            }
            else
                return false;
            break;
        }
        case 'b':
        case 'd':
        case 't':
        {   
            if (getGeoCords(eGeo)[0] >= xi && getGeoCords(eGeo)[0] <= xf && getGeoCords(eGeo)[1] >= yi && getGeoCords(eGeo)[1] <= yf)
            {
                // Ajustar as coordenadas da forma geométrica para posição relativa da foto
                return true;
            }    
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
///////////////////////////////