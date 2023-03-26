#include "geometry.h"
#include "drawSvg.h"
#include "cmdsFiles.h"
#include "lista.h"
#include "entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 500
#define SHORT_PARAMETER_SIZE 50
#define SIMPLE_PARAMETER_SIZE 100
#define MEDIUM_PARAMETER_SIZE 250


void WriteInSvg (char * svgFileName, Lista L, Style style);

/*
    Banco de dados é uma lista que guarda vários tipos de dados:
        - formas geométricas: circulos, retangulos, linhas e textos;
        - estilos de texto;
        - baloes: um texto "v_O_v" (forma geométrica), porem possui mais dados inclusos;
        - caças: um texto "|-T-|" (forma geométrica), porém possui mais dados inclusos;
    Para lidar com a lista de forma mais simples, pode-se criar um tipo de dado "Entity"
    que armazena uma generalização de todos os tipos de dados acima, sendo identificado por
    uma classe convencionada. Pode-se também criar uma estrutura simples que armazena apenas
    a classe do tipo e um ponteiro de tipo vazio que apontará para o tipo específico dependendo
    de cada caso. Neste caso, há possibilidade de maiores erros se não for feito com cuidado.
*/
void main()
{
    /////////////////////////////////////////////
    //            VARIÁVEIS ÚTEIS              //
    /////////////////////////////////////////////
    //
    char buffer[DEFAULT_BUFFER_SIZE];
    char parameter[SIMPLE_PARAMETER_SIZE];
    char attributes[SIMPLE_PARAMETER_SIZE];
    //
    Lista BD_Lst = createLst(-1);
    Entity entity;
    Geometry element;
    Geometry circle;
    Geometry rectangle;
    Geometry line;
    Geometry text;
    Picture pic;
    //
    int id, index;
    double x, x2;
    double y, y2;
    double radius;
    double width;
    double height;
    double depth;
    char anchor;
    char border_color[SIMPLE_PARAMETER_SIZE];
    char fill_color[SIMPLE_PARAMETER_SIZE];
    char text_buffer[DEFAULT_BUFFER_SIZE];
    //
    /* Convenção de valores-padrão e inicialização
        Como o estilo dos textos é único e aplicado a todos os textos, então pode ser armazenado como uma variável "global"
        sendo ele sempre o primeiro elemento da lista Banco de Dados (BD_Lst).
     */
    Style style = createTextStyle("serif", "normal", 16);
    /////////////////////////////////////////////

    


    /////////////////////////////////////////////
    //       LEITURA DO ARQUIVO .geo           //
    /////////////////////////////////////////////
    char * geoFileName = "a01.geo";
    ArqCmds GeoFile = abreArquivoCmd(geoFileName);
    if (GeoFile == NULL)
    {
        printf("ERRO: nao foi possivel abrir arquivo '%s'\n", geoFileName);
        return;
    } else
    {
        while (leLinha(GeoFile, buffer, DEFAULT_BUFFER_SIZE))
        {
            getParametroI(GeoFile, buffer, 0, parameter, SIMPLE_PARAMETER_SIZE);

            if (parameter[1] == 's')
            {
                // Is a text style
                getParametroI(GeoFile, buffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
                setStyleFontFamily(style, attributes);
                getParametroI(GeoFile, buffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
                setStyleFontWeight(style, attributes);
                getParametroI(GeoFile, buffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
                setStyleFontSize(style, atoi(attributes));
            }
            else
            if (parameter[0] == 'c')
            {
                // Is a circle
                getParametroI(GeoFile, buffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
                id = atoi(attributes);
                getParametroI(GeoFile, buffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
                x = atof(attributes);
                getParametroI(GeoFile, buffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
                y = atof(attributes);
                getParametroI(GeoFile, buffer, 4, attributes, SIMPLE_PARAMETER_SIZE);
                radius = atof(attributes);
                getParametroI(GeoFile, buffer, 5, border_color, SIMPLE_PARAMETER_SIZE);
                getParametroI(GeoFile, buffer, 6, fill_color, SIMPLE_PARAMETER_SIZE);
                
                
                circle = createCircle(id, x, y, radius, border_color, fill_color);
                entity = createCommon(circle, id);

                insertLst(BD_Lst, (Item) entity);
            }
            else
            if (parameter[0] == 'r')
            {
                // Is a rectangle
                getParametroI(GeoFile, buffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
                id = atoi(attributes);
                getParametroI(GeoFile, buffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
                x = atof(attributes);
                getParametroI(GeoFile, buffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
                y = atof(attributes);
                getParametroI(GeoFile, buffer, 4, attributes, SIMPLE_PARAMETER_SIZE);
                width = atof(attributes);
                getParametroI(GeoFile, buffer, 5, attributes, SIMPLE_PARAMETER_SIZE);
                height = atof(attributes);
                getParametroI(GeoFile, buffer, 6, border_color, SIMPLE_PARAMETER_SIZE);
                getParametroI(GeoFile, buffer, 7, fill_color, SIMPLE_PARAMETER_SIZE);

                rectangle = createRectangle(id, x, y, width, height, border_color, fill_color);
                entity = createCommon(rectangle, id);
                insertLst(BD_Lst, (Item) entity);   
            }
            else
            if (parameter[0] == 'l')
            {
                // Is a line
                getParametroI(GeoFile, buffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
                id = atoi(attributes);
                getParametroI(GeoFile, buffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
                x = atof(attributes);
                getParametroI(GeoFile, buffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
                y = atof(attributes);
                getParametroI(GeoFile, buffer, 4, attributes, SIMPLE_PARAMETER_SIZE);
                x2 = atof(attributes);
                getParametroI(GeoFile, buffer, 5, attributes, SIMPLE_PARAMETER_SIZE);
                y2 = atof(attributes);
                getParametroI(GeoFile, buffer, 6, border_color, SIMPLE_PARAMETER_SIZE);

                line = createLine(id, x, y, x2, y2, border_color);
                entity = createCommon(line, id);
                insertLst(BD_Lst, (Item) entity);
            }
            else
            if (parameter[0] == 't')
            {
                //t 7 60 60 black orange m v_O_v
                // Is a text
                getParametroI(GeoFile, buffer, 1, attributes, SIMPLE_PARAMETER_SIZE);
                id = atoi(attributes);
                getParametroI(GeoFile, buffer, 2, attributes, SIMPLE_PARAMETER_SIZE);
                x = atof(attributes);
                getParametroI(GeoFile, buffer, 3, attributes, SIMPLE_PARAMETER_SIZE);
                y = atof(attributes);
                getParametroI(GeoFile, buffer, 4, border_color, SIMPLE_PARAMETER_SIZE);
                getParametroI(GeoFile, buffer, 5, fill_color, SIMPLE_PARAMETER_SIZE);
                getParametroI(GeoFile, buffer, 6, attributes, SIMPLE_PARAMETER_SIZE);
                anchor = attributes[0];
                getParametroDepoisI(GeoFile, buffer, 7, text_buffer, DEFAULT_BUFFER_SIZE);
                // Remove o '\n' do final da string devido à leitura do arquivo
                text_buffer[strlen(text_buffer) - 1] = '\0';

                text = createText(id, x, y, border_color, fill_color, anchor, text_buffer);
                setGeoStyle(text, style);
                if (strcmp(text_buffer, "v_O_v") == 0)
                    entity = createBalloon(text, id);
                else
                if (strcmp(text_buffer, "|-T-|") == 0)
                    entity = createWarplane(text, id);
                else
                    entity = createCommon(text, id);

                insertLst(BD_Lst, (Item) entity);
            }
            else
            {
                printf("ERRO: comando '%s' nao reconhecido em '%s'\n", parameter, geoFileName);
                fechaArquivoCmd(GeoFile);
                return;
            }
        }
    }
    fechaArquivoCmd(GeoFile);








    /////////////////////////////////////////////
    //       LEITURA DO ARQUIVO .qry           //
    /////////////////////////////////////////////
    /* Exemplo de arquivo .qry
    c 1 50.00 50.0 30.00 grey magenta
    c 2 120.0 45.0 15.0 grey magenta
    t 7 60 60 black black m v_O_v
    c 5 230.0 180.0 13.0 grey magenta
    l 3 65.5 35.0 100.7 110.2 cyan
    r 4 10.0 150.0 90.0 40.0 cyan yellow
    ts serif normal 50
    */
    char * qryFileName = "q.qry";




    ArqCmds QryFile = abreArquivoCmd(qryFileName);
    if (QryFile == NULL)
    {
        printf("ERRO: nao foi possivel abrir arquivo '%s'\n", qryFileName);
        return;
    } else
    {
        while (leLinha(QryFile, buffer, DEFAULT_BUFFER_SIZE))
        {
            getParametroI(QryFile, buffer, 0, parameter, SIMPLE_PARAMETER_SIZE);

            if (strcmp(parameter, "mv") == 0)
            {
                getParametroI(QryFile, buffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
                id = atoi(parameter);

                // Encontra a forma geométrica a ser manipulada
                element = searchGeobyIDinLst(BD_Lst, id);

                getParametroI(QryFile, buffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
                x = atof(parameter);
                getParametroI(QryFile, buffer, 3, parameter, SIMPLE_PARAMETER_SIZE);
                y = atof(parameter);

                Dislocate_Geo(element, x, y);
            } else
            if (strcmp(parameter, "g") == 0)
            {
                getParametroI(QryFile, buffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
                id = atoi(parameter);
                getParametroI(QryFile, buffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
                radius = atof(parameter);

                element = searchGeobyIDinLst(BD_Lst, id);
                Rotate_Geo(element, radius);
            } else
            if (strcmp(parameter, "ff") == 0)
            {
                getParametroI(QryFile, buffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
                id = atoi(parameter);
                getParametroI(QryFile, buffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
                radius = atof(parameter);
                getParametroI(QryFile, buffer, 3, parameter, SIMPLE_PARAMETER_SIZE);
                depth = atof(parameter);
                getParametroI(QryFile, buffer, 4, parameter, SIMPLE_PARAMETER_SIZE);
                height = atof(parameter);

                entity = searchEntbyIDinLst(BD_Lst, id);
                setEntRadius(entity, radius);
                setEntDepth(entity, depth);
                setEntHeight(entity, height);
            } else
            if (strcmp(parameter, "tf") == 0)
            {
                getParametroI(QryFile, buffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
                id = atoi(parameter);
                getParametroI(QryFile, buffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
                index = atoi(parameter);





                //entity = searchEntbyIDinLst(BD_Lst, id);
                //addEntPicture(entity, pic, index);                
            } else
            if (strcmp(parameter, "df") == 0)
            {

            } else
            if (strcmp(parameter, "d") == 0)
            {

            } else
            if (strcmp(parameter, "b?") == 0)
            {

            } else
            if (strcmp(parameter, "c?") == 0)
            {

            } else
            {
                printf("ERRO: comando '%s' nao reconhecido em '%s'\n", parameter, qryFileName);
                fechaArquivoCmd(QryFile);
                return;
            }
        }
    }
    fechaArquivoCmd(QryFile);
    
    WriteInSvg("teste.svg", BD_Lst, style);
}

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

