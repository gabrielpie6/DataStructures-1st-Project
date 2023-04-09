#include "geoFile.h"

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