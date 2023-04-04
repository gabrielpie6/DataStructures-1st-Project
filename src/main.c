#include "actions.h"

#include <stdio.h>





void main()
{
    /////////////////////////////////////////////
    //            VARIÁVEIS ÚTEIS              //
    /////////////////////////////////////////////
    //
    Lista BD_Lst;

    //
    /* Convenção de valores-padrão e inicialização
        Como o estilo dos textos é único e aplicado a todos os textos, então pode ser armazenado como uma variável pseudo "global"
        sendo ele sempre o primeiro elemento da lista Banco de Dados (BD_Lst).
     */
    Style style = createTextStyle("serif", "normal", 16);

    /////////////////////////////////////////////
    //       LEITURA DO ARQUIVO .geo           //
    /////////////////////////////////////////////
    BD_Lst = ReadGeoFile("a01.geo", style);
    if (BD_Lst == NULL)
    {
        printf("ERRO: [in main]: nao foi possivel ler arquivo .geo\n");
        return;
    }

    /////////////////////////////////////////////
    //       LEITURA DO ARQUIVO .qry           //
    /////////////////////////////////////////////
    char * qryFileName = "q.qry";
    if (ReadQryFile(BD_Lst, qryFileName) == false)
    {
        printf("ERRO: [in main]: nao foi possivel ler arquivo .qry\n");
        return;
    }
    

    WriteInSvg("teste.svg", BD_Lst, style);
    printf("Executado com sucesso\n");
}