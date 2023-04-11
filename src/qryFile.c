#include "qryFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////
// .QRY FUNCTIONS
//
bool ReadQryFile(Lista L, char * qryPath, char * outputPath, char * geo_qryCombination, Style style, Lista Decos)
{
    ArqCmds QryFile = abreArquivoCmd(qryPath);
    if (QryFile == NULL)
    {
        printf("ERRO: nao foi possivel abrir arquivo '%s'\n", qryPath);
        return false;
    }
    else
    {
        char buffer[DEFAULT_BUFFER_SIZE];
        char parameter[SIMPLE_PARAMETER_SIZE];
        char * txtFile = malloc(sizeof(char) * (strlen(outputPath) + 1 + strlen(geo_qryCombination) + strlen(".txt") + 1));
        sprintf(txtFile, "%s/%s.txt", outputPath, geo_qryCombination);
        FILE * TXTFile = fopen(txtFile, "w");

        while (leLinha(QryFile, buffer, DEFAULT_BUFFER_SIZE))
        {
            getParametroI(QryFile, buffer, 0, parameter, SIMPLE_PARAMETER_SIZE);

            if (strcmp(parameter, "mv") == 0) moveEntity          (QryFile, L, buffer, TXTFile); else
            if (strcmp(parameter, "g" ) == 0) rotateEntity        (QryFile, L, buffer, TXTFile); else
            if (strcmp(parameter, "ff") == 0) setPictureFocus     (QryFile, L, buffer); else
            if (strcmp(parameter, "tf") == 0) takePicture         (QryFile, L, buffer, TXTFile, Decos); else
            if (strcmp(parameter, "df") == 0) downloadPictures    (QryFile, L, buffer, outputPath, geo_qryCombination, style, TXTFile); else
            if (strcmp(parameter, "d" ) == 0) detonateBomb        (QryFile, L, buffer, TXTFile, Decos); else
            if (strcmp(parameter, "b?") == 0) reportBalloonsData  (QryFile, L, buffer, TXTFile); else
            if (strcmp(parameter, "c?") == 0) reportWarplanesData (QryFile, L, buffer, TXTFile); else
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
void takePicture(ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile, Lista Decos)
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
    
    // Ajusta os elementos para que fiquem relativos à posição da foto
    double xi, yi, xf, yf;
    defineFrame(balloon, &xi, &yi, &xf, &yf);


    Picture pic = createPicture(getEntRadius(balloon), getEntHeight(balloon), getEntDepth(balloon), xi, yi, AuxiliarLst2);
    addPictureInFila(balloon, pic, index);
    
    killLst(AuxiliarLst);

    // Inserção do frame da foto como uma entidade decorativa na lista Decos
    Geometry frame = createRectangle(-1, xi, yi, getPictureRadius(pic) * 2, getPictureHeight(pic), "red;stroke-dasharray:2 3", "none");
    insertLst(Decos, (Item) frame);

    //
    // ESCRITA DOS ATRIBUTOS NO TXT
    //
    /*
        [*] tf ...
        balao: id
        raio da foto: radius
        profundidade da foto: depth
        altura da foto: height
        IDENTIFICADORES DOS ELEMENTOS FOTOGRAFADOS
        id [id]: (x, y)
        ...
    */
    fprintf(TXTFile, "[*] %s\n", lineBuffer);
    fprintf(TXTFile, "balao: %d\n", id);
    fprintf(TXTFile, "raio da foto: %lf\n", getPictureRadius(pic));
    fprintf(TXTFile, "profundidade da foto: %lf\n", getPictureDepth(pic));
    fprintf(TXTFile, "altura da foto: %lf\n", getPictureHeight(pic));
    fprintf(TXTFile, "IDENTIFICADOR(ES) DO(S) ELEMENTO(S) FOTOGRAFADO(S)\n");
    Lista elements = getPictureElements(pic);
    Entity ent;
    for (Posic p = getFirstLst(elements); getNextLst(elements, p) != NIL p = getNextLst(elements, p))
    {
        ent = (Entity) getLst(elements, p);
        fprintf(TXTFile, "id [%d]: (%lf, %lf)\n", getEntID(ent), getGeoCords(getEntGeo(ent))[0], getGeoCords(getEntGeo(ent))[0]);
    }
    fprintf(TXTFile, "\n");
}
//
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
    
    char * svgFileName = (char *) malloc(sizeof(char) * (strlen(outputPath) + 1 + strlen(geo_qryCombination) + 1 + strlen(suffix) + strlen(".svg") + 1));
    sprintf(svgFileName, "%s/%s-%s.svg", outputPath, geo_qryCombination, suffix);
    ArqSvg PicturesSVG = abreEscritaSvg(svgFileName);
    Picture pic;
    Lista elements;

    // Escrita dos atributos da foto
    Lista Decorations = createLst(-1);
    Geometry frame, balloonID, pont, raio, altura, prof;
    Style writeStyle = createTextStyle("serif", "normal", 25);
    char * strokeColor = "none";
    char * fillColor   = "black";
    char textBuffer[DEFAULT_BUFFER_SIZE];

    fprintf(TXTFile, "[*] %s\n", lineBuffer);
    fprintf(TXTFile, "balao: %d\n", id);
    fprintf(TXTFile, "FILA [%d]:\n", index);

    //
    // Percorrer cada foto da fila de fotos F e processa uma pontuação para cada foto
    //
    double pontuacao, width, height, dx = 0, dy = 0;
    double textInitX = 0, textInitY = 0;
    double spacing = 20;
    double * limits;
    double minimumSpace = 5;

    int count = 1;
    while (countFila(F) > 0)
    {
        pic      = (Picture) popFila(F);
        ajustElementsToRelativePicPos(pic);
        elements = getPictureElements(pic);
        pontuacao = scorePicture(pic);
        width = getPictureRadius(pic) * 2;
        height = getPictureHeight(pic);

        /*
            limits[0] = leftBound
            limits[1] = rightBound
            limits[2] = topBound
            limits[3] = bottomBound
        */
        limits = PictureBoundingBox(pic);


        // Escrever foto no svg
        dx -= limits[0];
        dy = -limits[2];
        WriteEntListInSvg(PicturesSVG, elements, style, dx, dy);
        
        

        //
        // ESCRITA DOS ATRIBUTOS DA FOTO (RODAPÉ)
        //
        frame = createRectangle(0, dx, dy, getPictureRadius(pic) * 2, getPictureHeight(pic), "black", "none");
        insertLst(Decorations, (Item) frame);

        textInitX = dx; // Arumar espacamento (?)
        textInitY = dy + spacing + limits[3];
        /*
            balao: id
            pont: pontuacao
            raio: radius
            altura: height
            prof: depth
        */
        sprintf(textBuffer, "balao: %d", id);

        balloonID = createText(-1, textInitX, textInitY, strokeColor, fillColor, 'i', textBuffer);
        setGeoStyle(balloonID, writeStyle);
        insertLst(Decorations, (Item) balloonID);

        textInitY += spacing;
        sprintf(textBuffer, "pont: %.2lf", pontuacao);
        pont = createText(-1, textInitX, textInitY, strokeColor, fillColor, 'i', textBuffer);
        setGeoStyle(pont, writeStyle);
        insertLst(Decorations, (Item) pont);

        textInitY += spacing;
        sprintf(textBuffer, "raio: %.2lf", getPictureRadius(pic));
        raio = createText(-1, textInitX, textInitY, strokeColor, fillColor, 'i', textBuffer);
        setGeoStyle(raio, writeStyle);
        insertLst(Decorations, (Item) raio);

        textInitY += spacing;
        sprintf(textBuffer, "altura: %.2lf", getPictureHeight(pic));
        altura = createText(-1, textInitX, textInitY, strokeColor, fillColor, 'i', textBuffer);
        setGeoStyle(altura, writeStyle);
        insertLst(Decorations, (Item) altura);

        textInitY += spacing;
        sprintf(textBuffer, "prof: %.2lf", getPictureDepth(pic));
        prof = createText(-1, textInitX, textInitY, strokeColor, fillColor, 'i', textBuffer);
        setGeoStyle(prof, writeStyle);
        insertLst(Decorations, (Item) prof);

        dx += limits[1] + minimumSpace;
        
        //
        // ESCREVE ATRIBUTOS das fotos no TXT
        //
        /*
            [*] df ...
            balao: id
            FOTO [1] - pont: pontuacao (%.2lf), raio: radius (%.2lf), altura: height (%.2lf), prof: depth (%.2lf)
            ...
            FOTO [n] - pont: pontuacao (%.2lf), raio: radius (%.2lf), altura: height (%.2lf), prof: depth (%.2lf)
        */
        fprintf(TXTFile, "\tFOTO [%d] - pont: %.2lf, raio: %.2lf, altura: %.2lf, prof: %.2lf\n", count, pontuacao, getPictureRadius(pic), getPictureHeight(pic), getPictureDepth(pic));
        count++;
    }
    WriteGeoListInSvg(PicturesSVG, Decorations, style, 0, 0);
    killLst(Decorations);
    fechaSvg(PicturesSVG);
    free(limits);
    fprintf(TXTFile, "\n");
}
void detonateBomb(ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile, Lista Decos)
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
    incrementEntShots(warplane);

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

    // Percorre a lista de elementos atingidos e busca por baloes atingidos
    Entity ent, target, clone;
    Geometry geo, X;
    Fila F;
    Lista elements;
    Posic p, q;
    Picture pic;
    double x1, y1;
    char stroke[COLOR_STRING_SIZE], fill[COLOR_STRING_SIZE];
    Style style = getGeoStyle(getEntGeo(warplane));
    int i;
    
    /*
        [*] d ...
        ELEMENTO(S) ATINGIDO(S):
            [id: id] - tipo: <tipo>, coordenadas: (x, y), cor de borda: <cor de borda>, cor de preenchimento: <cor de preenchimento>
            ...
        CLONE(S) GERADO(S):
            [id: id] - tipo: <tipo>, coordenadas: (x, y), cor de borda: <cor de borda>, cor de preenchimento: <cor de preenchimento>
            ...
    */

    fprintf(TXTFile, "[*] %s\n", lineBuffer);
    fprintf(TXTFile, "ELEMENTO(S) ATINGIDO(S):\n");
    for (p = getFirstLst(AuxiliarLst); p != NIL p = getNextLst(AuxiliarLst, p))
        writeEntAttributesInTXT(TXTFile, getLst(AuxiliarLst, p));



    fprintf(TXTFile, "CLONE(S) GERADO(S):\n");
    for (p = getFirstLst(AuxiliarLst); p != NIL p = getNextLst(AuxiliarLst, p))
    {
        ent = (Entity) getLst(AuxiliarLst, p);
        geo = getEntGeo(ent);
        
        /* SVG: colocar um X vermelho (FF0000) na âncora das figuras atingidas. */
        switch (getEntType(ent))
        {
            case 'c':
            case 'r':
            case 't':
            {
                x1 = getGeoCords(geo)[0];
                y1 = getGeoCords(geo)[1];
                break;
            }
            case 'l':
            {
                x1 = getGeoAnchor_1(geo)[0];
                y1 = getGeoAnchor_1(geo)[1];
                break;
            }
            case 'b':
            {
                x1 = getGeoCords(geo)[0];
                y1 = getGeoCords(geo)[1];
                // Fazer clone elementos de TODAS as fotos que não foram enviadas para a 'base'
                // Percorrer as filas de fotos do balão onde há fotos
                for (i = 0; i < FILAS_AMOUNT; i++)
                {
                    // Para cada fila, percorrer as fotos
                    F = getFilaOfPictures(ent, i);
                    for (; countFila(F) > 0;)
                    {
                        // Para cada elemento da foto, percorrer a lista de elementos
                        pic = popFila(F); // Retira a foto da fila do balao que SERÁ destruído ainda
                        elements = getPictureElements(pic);
                        for (q = getFirstLst(elements); q != NIL q = getNextLst(elements, q))
                        {
                            target = (Entity) getLst(elements, q);
                            clone = copyEntity(target);
                            setEntID(clone, index);
                            index++;
                            geo = getEntGeo(clone);

                            Dislocate_Geo(geo, dx, 0);

                            // Inverter as cores de borda com preenchimento (stroke <-> fill) (Somente quando é possível)
                            switch (getGeoClass(geo))
                            {
                                case 'c':
                                case 'r':
                                case 't':
                                {
                                    strcpy(stroke, getGeoBorder_color(geo));
                                    strcpy(fill, getGeoFill_color(geo));
                                    setGeoBorder_color(geo, fill);
                                    setGeoFill_color(geo, stroke);
                                    break;
                                }
                                case 'l':
                                {
                                    // Não fazer nada, pois linha só tem uma cor
                                    break;
                                }
                            }
                            insertLst(L, (Item) clone);
                            writeEntAttributesInTXT(TXTFile, clone);
                        }
                    }
                }
                break;
            }
            case 'd':
            {
                x1 = getGeoCords(geo)[0];
                y1 = getGeoCords(geo)[1];
                break;
            }
        }
        X = createText(-1, x1, y1, "#FF0000", "#FF0000", 'm', "X");
        setGeoStyle(X, style);
        insertLst(Decos, (Item) X);
    }
    fprintf(TXTFile, "\n");
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


void reportBalloonsData (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile)
{
    /* 
        Reporta os dados de todos os balões
        existentes, incluindo seus atributos e o número
        de fotos por fila e a rotação corrente do
        balão.
    */
   /*
        [*] b?
        BALAO    [id_i] - rotacao: <rotacao>, raio: <raio>, prof: <prof>, altura: <altura>
            FILA [j] - qtd de fotos: <qtd de fotos>
            ...
            FILA [m] - qtd de fotos: <qtd de fotos>
        ...
        BALAO    [id_n] - rotacao: <rotacao>, raio: <raio>, prof: <prof>, altura: <altura>

   */


    Entity ent;
    Geometry geo;
    Fila F;
    int i, qtd;
    fprintf(TXTFile, "[*] %s\n", lineBuffer);
    // Percorre toda a lista L procurando por baloes    
    for (Posic p = getFirstLst(L); p != NIL p = getNextLst(L, p))
    {
        ent = (Entity) getLst(L, p);
        if (getEntType(ent) == 'b')
        {
            geo = getEntGeo(ent);
            fprintf(TXTFile, "BALAO [id: %d] - posicao: (%.2lf, %.2lf), rotacao (graus): %.2lf, raio: %.2lf, prof: %.2lf, altura: %.2lf\n", getEntID(ent), getGeoCords(geo)[0], getGeoCords(geo)[1], getGeoAngle(geo), getEntRadius(ent), getEntDepth(ent), getEntHeight(ent));
            // Percorrer as FILAS de fotos dentro do balao e contar quantas fotos tem em cada fila.
            // Obs.: mostrar apenas as filas que possuem fotos.
            for (i = 0; i < FILAS_AMOUNT; i++)
            {
                F = getFilaOfPictures(ent, i);
                qtd = countFila(F);
                if (qtd > 0)
                    fprintf(TXTFile, "\tFILA [%d] - qtd de fotos: %d\n", i, qtd);
            }
        }
    }
    fprintf(TXTFile, "\n");
}
void reportWarplanesData (ArqCmds QryFile, Lista L, char * lineBuffer, FILE * TXTFile)
{
    /*
        Reporta os dados de todos as caças
        existentes: seus atributos, a rotação corrente,
        quantos disparos já efetuou e os
        identificadores dos elementos que acertou até
        o momento.
    */
    /*
        [*] c?
        CACA   [id_i] - rotacao: <rotacao>, disparos realizados: <disparos>, alvos atingidos: <alvos>
            ALVOS:
            id: id_n
            ...
            id: id_m
        ...
        CACA   [id_j] - rotacao: <rotacao>, raio: <raio>, prof: <prof>, altura: <altura>, disparos: <disparos>
            ALVOS:
            id: id_p
            ...
            id: id_q
    */

    Entity ent;
    Geometry geo;
    Lista targets;
    Posic p, q;
    fprintf(TXTFile, "[*] %s\n", lineBuffer);
    // Percorre toda a lista L procurando por baloes    
    for (p = getFirstLst(L); p != NIL p = getNextLst(L, p))
    {
        ent = (Entity) getLst(L, p);
        if (getEntType(ent) == 'd')
        {
            geo = getEntGeo(ent);
            targets = getEntTargetsID(ent);
            fprintf(TXTFile, "CACA [id: %d] - posicao: (%.2lf, %.2lf), rotacao (graus): %.2lf, disparos realizados: %d\n", getEntID(ent), getGeoCords(geo)[0], getGeoCords(geo)[1], getGeoAngle(geo), getEntShots(ent));
            fprintf(TXTFile, "ALVO(S) ATINGIDO(S) - total: %d\n", lengthLst(targets)); 
            for (q = getFirstLst(targets); q != NIL q = getNextLst(targets, q))
                fprintf(TXTFile, "\t[id: %d]\n", *((int *) getLst(targets, q)));
                
        }
    }
    fprintf(TXTFile, "\n");
}
///////////////////////////////////////////