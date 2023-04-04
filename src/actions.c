#include "actions.h"

#include "drawSvg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lista ReadGeoFile (char * geoPath, Style defaultStyle)
{
    /////////////////////////////////////////////
    //       LEITURA DO ARQUIVO .geo           //
    /////////////////////////////////////////////
    ArqCmds   GeoFile      = abreArquivoCmd(geoPath);
    char    * geoFileName  = geoPath;
    Style     style        = defaultStyle;


    char buffer    [DEFAULT_BUFFER_SIZE];
    char parameter [SIMPLE_PARAMETER_SIZE];
    

    if (GeoFile == NULL)
    {
        printf("ERRO: [in: ReadGeoFile]: nao foi possivel abrir arquivo '%s'\n", geoFileName);
        return NULL;
    } else
    {
        Lista BD_Lst = createLst(-1);
        Entity entity;

        while (leLinha(GeoFile, buffer, DEFAULT_BUFFER_SIZE))
        {
            getParametroI(GeoFile, buffer, 0, parameter, SIMPLE_PARAMETER_SIZE);

            if (strcmp(parameter, "ts") == 0)
            {
                readActTextStyle(GeoFile, buffer, style);
            }
            else
            if (strcmp(parameter, "c") == 0)
            {
                entity = readActCircle(GeoFile, buffer);
                insertLst(BD_Lst, (Item) entity);
            }
            else
            if (strcmp(parameter, "r") == 0)
            {
                entity = readActRectangle(GeoFile, buffer);
                insertLst(BD_Lst, (Item) entity);   
            }
            else
            if (strcmp(parameter, "l") == 0)
            {
                entity = readActLine(GeoFile, buffer);
                insertLst(BD_Lst, (Item) entity);
            }
            else
            if (strcmp(parameter, "t") == 0)
            {
                entity = readActText(GeoFile, buffer, style);
                insertLst(BD_Lst, (Item) entity);
            }
            else
            {
                printf("ERRO: [in: ReadGeoFile]: comando '%s' nao reconhecido em '%s'\n", parameter, geoFileName);
                fechaArquivoCmd(GeoFile);
                return NULL;
            }
        }
        fechaArquivoCmd(GeoFile);
        return BD_Lst;
    }
}
//
Entity readActCircle (ArqCmds GeoFile, char * lineBuffer)
{
    // Is a circle
    char attributes[SIMPLE_PARAMETER_SIZE];
    char border_color[SIMPLE_PARAMETER_SIZE];
    char fill_color[SIMPLE_PARAMETER_SIZE];


    getParametroI(GeoFile, lineBuffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
    int id = atoi(attributes);
    getParametroI(GeoFile, lineBuffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
    double x = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
    double y = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 4, attributes, SIMPLE_PARAMETER_SIZE);
    double radius = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 5, border_color, SIMPLE_PARAMETER_SIZE);
    getParametroI(GeoFile, lineBuffer, 6, fill_color, SIMPLE_PARAMETER_SIZE);
    
    
    Geometry circle = createCircle(id, x, y, radius, border_color, fill_color);
    Entity entity = createCommon(circle, id);
    return entity;
}
//
Entity readActRectangle (ArqCmds GeoFile, char * lineBuffer)
{
    char attributes[SIMPLE_PARAMETER_SIZE];
    char border_color[SIMPLE_PARAMETER_SIZE];
    char fill_color[SIMPLE_PARAMETER_SIZE];


    // Is a rectangle
    getParametroI(GeoFile, lineBuffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
    int id = atoi(attributes);
    getParametroI(GeoFile, lineBuffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
    double x = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
    double y = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 4, attributes, SIMPLE_PARAMETER_SIZE);
    double width = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 5, attributes, SIMPLE_PARAMETER_SIZE);
    double height = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 6, border_color, SIMPLE_PARAMETER_SIZE);
    getParametroI(GeoFile, lineBuffer, 7, fill_color, SIMPLE_PARAMETER_SIZE);

    Geometry rectangle = createRectangle(id, x, y, width, height, border_color, fill_color);
    Entity entity = createCommon(rectangle, id);
    return entity;
}
//
Entity readActLine (ArqCmds GeoFile, char * lineBuffer)
{
    char attributes[SIMPLE_PARAMETER_SIZE];
    char border_color[SIMPLE_PARAMETER_SIZE];

    // Is a line
    getParametroI(GeoFile, lineBuffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
    int id = atoi(attributes);
    getParametroI(GeoFile, lineBuffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
    double x1 = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
    double y1 = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 4, attributes, SIMPLE_PARAMETER_SIZE);
    double x2 = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 5, attributes, SIMPLE_PARAMETER_SIZE);
    double y2 = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 6, border_color, SIMPLE_PARAMETER_SIZE);

    Geometry line = createLine(id, x1, y1, x2, y2, border_color);
    Entity entity = createCommon(line, id);
    return entity;
}
//
Entity readActText (ArqCmds GeoFile, char * lineBuffer, Style style)
{
    char attributes[SIMPLE_PARAMETER_SIZE];
    char border_color[SIMPLE_PARAMETER_SIZE];
    char fill_color[SIMPLE_PARAMETER_SIZE];
    char text_buffer[DEFAULT_BUFFER_SIZE];

    // Is a text
    getParametroI(GeoFile, lineBuffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
    int id = atoi(attributes);
    getParametroI(GeoFile, lineBuffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
    double x = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
    double y = atof(attributes);
    getParametroI(GeoFile, lineBuffer, 4, border_color, SIMPLE_PARAMETER_SIZE);
    getParametroI(GeoFile, lineBuffer, 5, fill_color, SIMPLE_PARAMETER_SIZE);
    getParametroI(GeoFile, lineBuffer, 6, attributes, SIMPLE_PARAMETER_SIZE);
    char anchor = attributes[0];
    getParametroDepoisI(GeoFile, lineBuffer, 7, text_buffer, DEFAULT_BUFFER_SIZE);
    // Remove o '\n' do final da string devido à leitura do arquivo
    text_buffer[strlen(text_buffer) - 1] = '\0';


    Geometry text = createText(id, x, y, border_color, fill_color, anchor, text_buffer);
    Entity entity;
    setGeoStyle(text, style);

    if (strcmp(text_buffer, "v_O_v") == 0)
        entity = createBalloon(text, id);
    else if (strcmp(text_buffer, "|-T-|") == 0)
        entity = createWarplane(text, id);
    else
        entity = createCommon(text, id);

    return entity;
}
// 
void readActTextStyle (ArqCmds GeoFile, char * lineBuffer, Style created_already_style)
{
    char attributes[SIMPLE_PARAMETER_SIZE];

    // Is a text style
    getParametroI(GeoFile, lineBuffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
    setStyleFontFamily(created_already_style, attributes);
    getParametroI(GeoFile, lineBuffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
    setStyleFontWeight(created_already_style, attributes);
    getParametroI(GeoFile, lineBuffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
    setStyleFontSize(created_already_style, atof(attributes));
}



///////////////////////////////////////////
// .QRY FUNCTIONS
bool ReadQryFile(Lista L, char * qryPath)
{
    ArqCmds QryFile = abreArquivoCmd(qryPath);
    if (QryFile == NULL)
    {
        printf("ERRO: nao foi possivel abrir arquivo '%s'\n", qryPath);
        return false;
    } else
    {
        char buffer[DEFAULT_BUFFER_SIZE];
        char parameter[SIMPLE_PARAMETER_SIZE];

        while (leLinha(QryFile, buffer, DEFAULT_BUFFER_SIZE))
        {
            getParametroI(QryFile, buffer, 0, parameter, SIMPLE_PARAMETER_SIZE);

            if (strcmp(parameter, "mv") == 0)
            {
                moveEntity(QryFile, L, buffer);
            } else
            if (strcmp(parameter, "g") == 0)
            {
                rotateEntity(QryFile, L, buffer);
            } else
            if (strcmp(parameter, "ff") == 0)
            {
                setPictureFocus(QryFile, L, buffer);
            } else
            if (strcmp(parameter, "tf") == 0)
            {
                takePicture(QryFile, L, buffer);
            } else
            if (strcmp(parameter, "df") == 0)
            {

            } else
            if (strcmp(parameter, "d") == 0)
            {
                detonateBomb(QryFile, L, buffer);
            } else
            if (strcmp(parameter, "b?") == 0)
            {

            } else
            if (strcmp(parameter, "c?") == 0)
            {

            } else
            {
                printf("ERRO: comando '%s' nao reconhecido em '%s'\n", parameter, qryPath);
                fechaArquivoCmd(QryFile);
                return false;
            }
        }
    }
    fechaArquivoCmd(QryFile);
    return true;
}

void moveEntity(ArqCmds QryFile, Lista L, char * lineBuffer)
{
    char parameter[SIMPLE_PARAMETER_SIZE];

    getParametroI(QryFile, lineBuffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
    int id = atoi(parameter);
    // Encontra a forma geométrica a ser manipulada
    Geometry element = searchGeobyIDinLst(L, id);

    getParametroI(QryFile, lineBuffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
    double x = atof(parameter);
    getParametroI(QryFile, lineBuffer, 3, parameter, SIMPLE_PARAMETER_SIZE);
    double y = atof(parameter);

    Dislocate_Geo(element, x, y);
}
void rotateEntity(ArqCmds QryFile, Lista L, char * lineBuffer)
{
    char parameter[SIMPLE_PARAMETER_SIZE];

    getParametroI(QryFile, lineBuffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
    int id = atoi(parameter);
    getParametroI(QryFile, lineBuffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
    double theta = atof(parameter);

    Geometry element = searchGeobyIDinLst(L, id);
    Rotate_Geo(element, theta);
}
void setPictureFocus(ArqCmds QryFile, Lista L, char * lineBuffer)
{
    char parameter[SIMPLE_PARAMETER_SIZE];

    getParametroI(QryFile, lineBuffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
    int id = atoi(parameter);
    getParametroI(QryFile, lineBuffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
    double radius = atof(parameter);
    getParametroI(QryFile, lineBuffer, 3, parameter, SIMPLE_PARAMETER_SIZE);
    double depth = atof(parameter);
    getParametroI(QryFile, lineBuffer, 4, parameter, SIMPLE_PARAMETER_SIZE);
    double height = atof(parameter);

    Geometry entity = searchEntbyIDinLst(L, id);
    setEntDepth  (entity, depth);
    setEntRadius (entity, radius);
    setEntHeight (entity, height);
}
void takePicture(ArqCmds QryFile, Lista L, char * lineBuffer)
{
    char parameter[SIMPLE_PARAMETER_SIZE];

    getParametroI(QryFile, lineBuffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
    int id = atoi(parameter);
    getParametroI(QryFile, lineBuffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
    int index = atoi(parameter);

    Entity balloon = searchEntbyIDinLst(L, id);

    Lista AuxiliarLst = filterClausure(L, isEntinPicture, (Clausura) balloon);
    addEntPicture(balloon, (Picture) AuxiliarLst, index);
    
    //WriteInSvg("picture.svg", (Lista) popEntPicture(balloon, index), style);

    /*
    // Vizualização da area da foto
    element = getEntGeo(balloon);
    radius = getEntRadius(balloon);
    x = getGeoCords(element)[0];
    y = getGeoCords(element)[1];
    width = radius * 2;
    depth = getEntDepth(balloon);
    height = getEntHeight(balloon);

    rectangle = createRectangle(500, x - radius, y + depth, width, height, "black", "none");
    entity = createCommon(rectangle, 500);
    insertBeforeLst(BD_Lst, getFirstLst(BD_Lst) ,(Item) entity); 
    */
}
void downloadPictures(ArqCmds QryFile, Lista L, char * lineBuffer);
void detonateBomb(ArqCmds QryFile, Lista L, char * lineBuffer)
{
    char parameter[SIMPLE_PARAMETER_SIZE];

    getParametroI(QryFile, lineBuffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
    int id = atoi(parameter);
    getParametroI(QryFile, lineBuffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
    char capacityType = parameter[0];
    getParametroI(QryFile, lineBuffer, 3, parameter, SIMPLE_PARAMETER_SIZE);
    double distance = atof(parameter);
    getParametroI(QryFile, lineBuffer, 4, parameter, SIMPLE_PARAMETER_SIZE);
    int index = atoi(parameter);
    getParametroI(QryFile, lineBuffer, 5, parameter, SIMPLE_PARAMETER_SIZE);
    double dx = atof(parameter);

    Entity warplane = searchEntbyIDinLst(L, id);
    double x = getGeoCords(getEntGeo(warplane))[0];
    double y = getGeoCords(getEntGeo(warplane))[1];
    double theta = getGeoAngle(getEntGeo(warplane));

    // Define como a bomba será lançada
    Bomb bomb = defineBomb(capacityType, x, y, distance, theta);
    /*
    */
    // Verifica sob toda a lista quais são as entidades que foram atingidas pela bomba
    // e as insere em uma lista auxiliar
    Lista AuxiliarLst = filterClausure(L, throwBomb, (Clausura) bomb);
    
    // Insere os IDs dos elementos em AuxiliarLst na lista de alvos da bomba
    fold(AuxiliarLst, addEntTargetID, (Clausura) warplane);
    /* Vizualização dos IDs dos alvos
    for (int * test = popEntTargetID(warplane); test != NULL; test = popEntTargetID(warplane))
        printf("ID: %d\n", *test);
    */


    // Remove os elementos de Auxiliar presentes no Banco de Dados
    fold(AuxiliarLst, removeEntbyIDinLst, (Clausura) L);


    // Libera a lista auxiliar
    //killLst(AuxiliarLst);

    /* Comandos para gerar figura da área de alcance da bomba
    */
    Geometry circle = createCircle(501, getBombTargetCords(bomb)[0], getBombTargetCords(bomb)[1], getBombRadius(bomb), "black", "none");
    Entity entity = createCommon(circle, 501);
    insertLst(L, (Item) entity);

    removeBomb(bomb);
}
///////////////////////////////////////////









void writeGeoInSVG(Entity ent, Clausura c)
{
    Geometry element = getEntGeo(ent);
    ArqSvg SVG = (ArqSvg) c;
    Style style;
    char deco[DEFAULT_BUFFER_SIZE];
    char font_size[SHORT_PARAMETER_SIZE];
    char text_anchor[20];
    switch (getGeoClass(element))
    {
        case 'c':
        {
            preparaDecoracao(SVG, deco, DEFAULT_BUFFER_SIZE, getGeoBorder_color(element), getGeoFill_color(element), "1", 1, 1, 1);
            escreveCirculoSvg(SVG, getGeoCords(element)[0], getGeoCords(element)[1], getGeoRadius(element), deco);
            break;
        };
        case 'r':
        {
            preparaDecoracao(SVG, deco, DEFAULT_BUFFER_SIZE, getGeoBorder_color(element), getGeoFill_color(element), "1", 1, 1, 1);
            escreveRetanguloSvg(SVG, getGeoCords(element)[0], getGeoCords(element)[1], getGeoWidth(element), getGeoHeight(element), deco);
            break;
        };
        case 'l':
        {
            preparaDecoracao(SVG, deco, DEFAULT_BUFFER_SIZE, getGeoBorder_color(element), getGeoFill_color(element), "1", 1, 1, 1);
            escreveLinhaSvg(SVG, getGeoAnchor_1(element)[0], getGeoAnchor_1(element)[1], getGeoAnchor_2(element)[0], getGeoAnchor_2(element)[1], deco);
            break;
        };
        case 't':
        {
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

void WriteInSvg(char * svgFilePath, Lista L, Style style)
{
    ArqSvg SVG = abreEscritaSvg(svgFilePath);
    fold(L, writeGeoInSVG, SVG);
    fechaSvg(SVG);
}