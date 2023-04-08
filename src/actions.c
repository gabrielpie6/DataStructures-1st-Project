#include "actions.h"


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
//
bool ReadQryFile(Lista L, char * qryPath, char * outputPath, char * geo_qryCombination, Style style)
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
        char * txtFile = malloc(sizeof(char) * (strlen(outputPath) + 1 + strlen(geo_qryCombination) + strlen(".txt") + 1));
        sprintf(txtFile, "%s/%s.txt", outputPath, geo_qryCombination);
        FILE * TXTFile = fopen(txtFile, "w");

        while (leLinha(QryFile, buffer, DEFAULT_BUFFER_SIZE))
        {
            getParametroI(QryFile, buffer, 0, parameter, SIMPLE_PARAMETER_SIZE);

            if (strcmp(parameter, "mv") == 0) moveEntity       (QryFile, L, buffer, TXTFile); else
            if (strcmp(parameter, "g" ) == 0) rotateEntity     (QryFile, L, buffer, TXTFile); else
            if (strcmp(parameter, "ff") == 0) setPictureFocus  (QryFile, L, buffer); else
            if (strcmp(parameter, "tf") == 0) {takePicture      (QryFile, L, buffer, TXTFile);
                Entity balloon = searchEntbyIDinLst(L, 7);
                Entity b2 = copyEntity(balloon);
                Picture pic = popPictureInFila(balloon, 0);
                Lista elements = getPictureElements(pic);
                
                
                
                char * teste = malloc(sizeof(char) * (strlen(outputPath) + 1 + strlen("foto.svg") + 1));
                sprintf(teste, "%s/foto.svg", outputPath);
                ArqSvg Test = abreEscritaSvg(teste);
                free(teste);
                //WriteEntListInSvg(Test, elements, style, 0, 0);
                printf("oi\n");
                printf("len: %d\n", lengthLst(elements));
                /*
                for (Entity ent; lengthLst(elements) > 0;)
                {
                    ent = popLst(elements);
                    printf("id: %d\n", getEntID(ent));
                }
                */
                WriteEntListInSvg(Test, elements, style, 0, 0);
                fechaSvg(Test);
            
            } else
            if (strcmp(parameter, "df") == 0) downloadPictures (QryFile, L, buffer, outputPath, geo_qryCombination, style, TXTFile); else
            if (strcmp(parameter, "d" ) == 0) detonateBomb     (QryFile, L, buffer, TXTFile); else
            if (strcmp(parameter, "b?") == 0) {} else
            if (strcmp(parameter, "c?") == 0) {} else
            {
                printf("ERRO: comando '%s' nao reconhecido em '%s'\n", parameter, qryPath);
                fechaArquivoCmd(QryFile);
                fclose(TXTFile);
                return false;
            }
        }
        fclose(TXTFile);
    }
    fechaArquivoCmd(QryFile);
    return true;
}
//
void moveEntity(ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile)
{
    char parameter[SIMPLE_PARAMETER_SIZE];

    getParametroI(QryFile, lineBuffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
    int id = atoi(parameter);
    // Encontra a forma geométrica a ser manipulada
    Geometry element = searchGeobyIDinLst(L, id);

    getParametroI(QryFile, lineBuffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
    double dx = atof(parameter);
    getParametroI(QryFile, lineBuffer, 3, parameter, SIMPLE_PARAMETER_SIZE);
    double dy = atof(parameter);


    double x0, y0, x0A, y0A, x0B, y0B;
    if (getGeoClass(element) == 'l')
    {
        x0A = getGeoAnchor_1(element)[0];
        y0A = getGeoAnchor_1(element)[1];
        x0B = getGeoAnchor_2(element)[0];
        y0B = getGeoAnchor_2(element)[1];
    }
    else
    {
        x0 = getGeoCords(element)[0];
        y0 = getGeoCords(element)[1];
    }

    Dislocate_Geo(element, dx, dy);
    

    // ESCRITA NO ARQUIVO TXT
    // reportar os atributos da figura do dado id, a posição original e a posição final
    fprintf(TXTFile, "[*] %s\n", lineBuffer);
    switch(getGeoClass(element))
    {
        /*
            circulo
            ancora originalmente     em (x, y)
            ancora apos deslocamento em (x, y)
            raio: r
            preenchimento: cor_do_preenchimento
            borda: cor_da_borda
        */
        case 'c':
        {
            double xf = getGeoCords(element)[0];
            double yf = getGeoCords(element)[1];
            fprintf(TXTFile, "circulo\n");
            fprintf(TXTFile, "ancora originalmente     em (%lf, %lf)\n", x0, y0);
            fprintf(TXTFile, "ancora apos deslocamento em (%lf, %lf)\n", xf, yf);
            fprintf(TXTFile, "raio: %lf\n", getGeoRadius(element));
            fprintf(TXTFile, "preenchimento: %s\n", getGeoFill_color(element));
            fprintf(TXTFile, "borda: %s\n", getGeoBorder_color(element));
            fprintf(TXTFile, "\n");
            break;
        }
        /*
            retangulo
            ancora originalmente     em (x, y)
            ancora apos deslocamento em (x, y)
            largura: w
            altura: h
            preenchimento: cor_do_preenchimento
            borda: cor_da_borda
        */
        case 'r':
        {
            double xf = getGeoCords(element)[0];
            double yf = getGeoCords(element)[1];
            fprintf(TXTFile, "retangulo\n");
            fprintf(TXTFile, "ancora originalmente     em (%lf, %lf)\n", x0, y0);
            fprintf(TXTFile, "ancora apos deslocamento em (%lf, %lf)\n", xf, yf);
            fprintf(TXTFile, "largura: %lf\n", getGeoWidth(element));
            fprintf(TXTFile, "altura: %lf\n", getGeoHeight(element));
            fprintf(TXTFile, "preenchimento: %s\n", getGeoFill_color(element));
            fprintf(TXTFile, "borda: %s\n", getGeoBorder_color(element));
            fprintf(TXTFile, "\n");
            break;
        }
        /*
            linha
            ancora 1 originalmente     em (x, y)
            ancora 1 apos deslocamento em (x, y)
            ancora 2 originalmente     em (x, y)
            ancora 2 apos deslocamento em (x, y)
            cor: cor_da_linha
        */
        case 'l':
        {
            double xfA = getGeoAnchor_1(element)[0];
            double yfA = getGeoAnchor_1(element)[1];
            double xfB = getGeoAnchor_2(element)[0];
            double yfB = getGeoAnchor_2(element)[1];
            fprintf(TXTFile, "linha\n");
            fprintf(TXTFile, "ancora 1 originalmente     em (%lf, %lf)\n", x0A, y0A);
            fprintf(TXTFile, "ancora 1 apos deslocamento em (%lf, %lf)\n", xfA, yfA);
            fprintf(TXTFile, "ancora 2 originalmente     em (%lf, %lf)\n", x0B, y0B);
            fprintf(TXTFile, "ancora 2 apos deslocamento em (%lf, %lf)\n", xfB, yfB);
            fprintf(TXTFile, "cor: %s\n", getGeoBorder_color(element));
            fprintf(TXTFile, "\n");
            break;
        }
        /*
            texto
            ancora originalmente     em (x, y)
            ancora apos deslocamento em (x, y)
            rotacao: theta
            tipo de ancora: tipo
            texto: t
            preenchimento: cor_do_preenchimento
            borda: cor_da_borda
        */
        case 't':
        {
            double xf = getGeoCords(element)[0];
            double yf = getGeoCords(element)[1];
            fprintf(TXTFile, "texto\n");
            fprintf(TXTFile, "ancora originalmente     em (%lf, %lf)\n", x0, y0);
            fprintf(TXTFile, "ancora apos deslocamento em (%lf, %lf)\n", xf, yf);
            fprintf(TXTFile, "rotacao: %lf\n", getGeoAngle(element));
            fprintf(TXTFile, "tipo de ancora: %c\n", getGeoAnchor(element));
            fprintf(TXTFile, "texto: %s\n", getGeoText(element));
            fprintf(TXTFile, "preenchimento: %s\n", getGeoFill_color(element));
            fprintf(TXTFile, "borda: %s\n", getGeoBorder_color(element));
            fprintf(TXTFile, "\n");
            break;
        }
    }
}
//
void rotateEntity(ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile)
{
    char parameter[SIMPLE_PARAMETER_SIZE];

    getParametroI(QryFile, lineBuffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
    int id = atoi(parameter);
    getParametroI(QryFile, lineBuffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
    double theta = atof(parameter);

    Geometry element = searchGeobyIDinLst(L, id);
    double theta0 = getGeoAngle(element);

    Rotate_Geo(element, theta);
    double thetaf = getGeoAngle(element);

    // ESCRITA NO ARQUIVO TXT
    // reportar os atributos da figura do dado id, reportar a inclinação (graus) antes e depois da operação.
    // PELO QUE APARENTE, SOMENTE SERÁ ROTACIONADO TEXTOS!!!!
    /*
        texto
        ancora em (x, y)
        rotacao original: theta0
        rotacao final:    thetaf
        tipo de ancora: tipo
        texto: t
        preenchimento: cor_do_preenchimento
        borda: cor_da_borda
    */
    fprintf(TXTFile, "[*] %s\n", lineBuffer);
    fprintf(TXTFile, "texto\n");
    fprintf(TXTFile, "ancora em (%lf, %lf)\n", getGeoCords(element)[0], getGeoCords(element)[1]);
    fprintf(TXTFile, "rotacao original: %lf\n", theta0);
    fprintf(TXTFile, "rotacao final:    %lf\n", thetaf);
    fprintf(TXTFile, "tipo de ancora: %c\n", getGeoAnchor(element));
    fprintf(TXTFile, "texto: %s\n", getGeoText(element));
    fprintf(TXTFile, "preenchimento: %s\n", getGeoFill_color(element));
    fprintf(TXTFile, "borda: %s\n", getGeoBorder_color(element));
    fprintf(TXTFile, "\n");
}
//
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
//
void ajustEntInFrame(Entity ent, Clausura c)
{
    void ** clausures =  (void **  ) c;
    Entity  balloon   =  (Entity   ) clausures[0];
    double  xi        = *((double *) clausures[1]);
    double  yi        = *((double *) clausures[2]);
    double  xf        = *((double *) clausures[3]);
    double  yf        = *((double *) clausures[4]);
    
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
void takePicture(ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile)
{
    char parameter[SIMPLE_PARAMETER_SIZE];

    getParametroI(QryFile, lineBuffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
    int id = atoi(parameter);
    getParametroI(QryFile, lineBuffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
    int index = atoi(parameter);

    Entity balloon = searchEntbyIDinLst(L, id);

    // Lista de elementos que estão dentro do frame da foto do balão
    Lista AuxiliarLst = filterClausure(L, isEntinFrame, (Clausura) balloon);

    // É preciso fazer uma cópia da lista obtida, pois esta NÃO POSSUI NOVOS ELEMENTOS alocados na memória
    // (são apenas ponteiros para os elementos da lista original)
    Lista AuxiliarLst2 = map(AuxiliarLst, copyEntity);
    
    // Ajuste das coordenadas das entidades para posição relativa ao frame da foto
    double xi, yi, xf, yf;
    defineFrame(balloon, &xi, &yi, &xf, &yf);
    void * clausures[5];
    clausures[0] = (void *) balloon;
    clausures[1] = (void *) &xi;
    clausures[2] = (void *) &yi;
    clausures[3] = (void *) &xf;
    clausures[4] = (void *) &yf;
    fold (AuxiliarLst2, ajustEntInFrame, (Clausura) clausures);


    Picture pic = createPicture(getEntRadius(balloon), getEntHeight(balloon), getEntDepth(balloon), AuxiliarLst2);
    addPictureInFila(balloon, pic, index);
    
    //killLst(AuxiliarLst);

    //WriteInSvg("picture.svg", (Lista) popEntPicture(balloon, index), style);

    /*
    Style style = createTextStyle("arial", "normal", 16);
    ArqSvg arq = abreEscritaSvg("picture.svg");
    printf("lenAuxiliar = %d\n", lengthLst(AuxiliarLst2));
    WriteEntListInSvg(arq, AuxiliarLst2, style, 0, 0);
    fechaSvg(arq);
    */

    /*
    // Vizualização da area da foto
    Geometry element = getEntGeo(balloon);
    double radius = getEntRadius(balloon);
    double x = getGeoCords(element)[0];
    double y = getGeoCords(element)[1];
    double width = radius * 2;
    double depth = getEntDepth(balloon);
    double height = getEntHeight(balloon);

    Geometry rectangle = createRectangle(500, x - radius, y + depth, width, height, "black", "none");
    Entity entity = createCommon(rectangle, 500);
    insertBeforeLst(L, getFirstLst(L) ,(Item) entity); 
    */
}
//
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
void downloadPictures(ArqCmds QryFile, Lista L, char * lineBuffer, char * outputPath, char * geo_qryCombination, Style style, FILE * TXTFile)
{
    char parameter[SIMPLE_PARAMETER_SIZE];
    char suffix[SIMPLE_PARAMETER_SIZE];

    getParametroI(QryFile, lineBuffer, 1, parameter, SIMPLE_PARAMETER_SIZE);
    int id = atoi(parameter);
    getParametroI(QryFile, lineBuffer, 2, parameter, SIMPLE_PARAMETER_SIZE);
    int index = atoi(parameter);
    getParametroI(QryFile, lineBuffer, 3, parameter, SIMPLE_PARAMETER_SIZE);
    strcpy(suffix, parameter);

    Entity balloon = searchEntbyIDinLst(L, id);
    Fila   F       = getFilaOfPictures(balloon, index);
    double radius  = getEntRadius(balloon);
    double height  = getEntHeight(balloon);
    double depth   = getEntDepth (balloon);
    
    // pontuar cada foto
    double pontuação, dx = 0, dy = 0;
    char * svgFileName = (char *) malloc(sizeof(char) * (strlen(outputPath) + 1 + strlen(geo_qryCombination) + 1 + strlen(suffix) + strlen(".svg") + 1));
    sprintf(svgFileName, "%s/%s-%s.svg", outputPath, geo_qryCombination, suffix);
    ArqSvg PicturesSVG = abreEscritaSvg(svgFileName);
    Picture pic;
    Entity entity;

    Lista Decorations = createLst(-1);
    Geometry frame, baloonID, pont, raio, altura, prof;
    char deco[DEFAULT_BUFFER_SIZE];


    // Percorrer cada foto da fila de fotos F e processa uma pontuação para cada foto
    while (isFilaEmpty(F) == false)
    {
        pic = popPictureInFila(balloon, index);
        pontuação = scorePicture(pic);


        // Escrever foto no svg
        WriteEntListInSvg(PicturesSVG, L, style, dx, dy);

        // Escrever rodapé de cada foto
        //frame = createRectangle(0, dx, dy, getPictureRadius(pic) * 2, getPictureHeight(pic), "black", "none");
        preparaDecoracao(PicturesSVG, deco, DEFAULT_BUFFER_SIZE, "black", "none", "1", 1, 1, 1);
        escreveRetanguloSvg(PicturesSVG, dx, dy, getPictureRadius(pic) * 2, getPictureHeight(pic), deco);
        //
        dx += getPictureRadius(pic) * 2; //// PRECISA AJUSTAR O EXTRAPOLAMENTO DE FORMAS!!!!!!!
    }
    fechaSvg(PicturesSVG);
}
void detonateBomb(ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile)
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
    Geometry circle = createCircle(501, getBombTargetCords(bomb)[0], getBombTargetCords(bomb)[1], getBombRadius(bomb), "black", "none");
    Entity entity = createCommon(circle, 501);
    insertLst(L, (Item) entity);
    */

    removeBomb(bomb);
}
///////////////////////////////////////////









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

Entity copyEntity (Entity ent)
{
    Entity newEnt;
    Geometry eGeo;
    switch (getEntType(ent))
    {
        case 'c':
        {
            eGeo = getEntGeo(ent);
            eGeo = createCircle(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoRadius(eGeo), getGeoBorder_color(eGeo), getGeoFill_color(eGeo));
            newEnt = createCommon(eGeo, getEntID(ent));
            break;
        }
        case 'r':
        {
            eGeo = getEntGeo(ent);
            eGeo = createRectangle(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoWidth(eGeo), getGeoHeight(eGeo), getGeoBorder_color(eGeo), getGeoFill_color(eGeo));
            newEnt = createCommon(eGeo, getEntID(ent));
            break;
        }
        case 'l':
        {
            eGeo = getEntGeo(ent);
            eGeo = createLine(getEntID(ent), getGeoAnchor_1(eGeo)[0], getGeoAnchor_1(eGeo)[1], getGeoAnchor_2(eGeo)[0], getGeoAnchor_2(eGeo)[1], getGeoBorder_color(eGeo));
            newEnt = createCommon(eGeo, getEntID(ent));
            break;
        }
        case 't':
        {
            eGeo = getEntGeo(ent);
            Style style = getGeoStyle(eGeo);
            eGeo = createText(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoBorder_color(eGeo), getGeoFill_color(eGeo), getGeoAnchor(eGeo), getGeoText(eGeo));
            setGeoStyle(eGeo, style);
            newEnt = createCommon(eGeo, getEntID(ent));
            break;
        }
        case 'b':
        {
            eGeo = getEntGeo(ent);
            Style style = getGeoStyle(eGeo);
            eGeo = createText(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoBorder_color(eGeo), getGeoFill_color(eGeo), getGeoAnchor(eGeo), getGeoText(eGeo));
            setGeoStyle(eGeo, style);
            newEnt = createBalloon(eGeo, getEntID(ent));
        }
        case 'd':
        {
            eGeo = getEntGeo(ent);
            Style style = getGeoStyle(eGeo);
            eGeo = createText(getEntID(ent), getGeoCords(eGeo)[0], getGeoCords(eGeo)[1], getGeoBorder_color(eGeo), getGeoFill_color(eGeo), getGeoAnchor(eGeo), getGeoText(eGeo));
            setGeoStyle(eGeo, style);
            newEnt = createWarplane(eGeo, getEntID(ent));
        }
    }
    return newEnt;
}