#ifndef ENTITY_H
#define ENTITY_H

#include "geometry.h"
#include "lista.h"
#include "fila.h"

/*
    Módulo que provê a definição de tipos abstratos de dados para três formatos de entidades e dois
    tipo abstratos de dados de objetos que podem interagir com as entidades, todas as três entidades
    possuem formas geométricas associadas (Geometry).
    São as entidades:
        - Common:   Entidade comum, que não possui características especiais. Contém um identificador
                    único e uma forma geométrica.
        - Balloon:  Entidade que representa um balão. Contém um identificador único, uma forma geométrica,
                    um raio, uma altura e uma profundidade, estes últimos três valores são respectivos
                    a propriedades de captura de uma foto. Possui um conjunto de 10 câmeras de fotos
                    (rolos de fotos), onde cada câmera pode armazenar até 15 fotos.
        - Warplane: Entidade que representa um caça. Contém um identificador único, uma forma
                    geométrica, um contador de disparos realizados e uma lista de identificadores
                    dos alvos que o caça acertou.

    Uma entidade comum (Common) não possui uma tipagem própria, pois esta é dada pela forma geométrica
    associada a ela. Portanto tem-se seis tipos de entidades por convenção:

    CONVENÇÃO DE ENTIDADES (getEntType)):
        - Círculo:   'c' (Common)
        - Retângulo: 'r' (Common)
        - Linha:     'l' (Common)
        - Texto:     't' (Common)
        - Balão:     'b' (Balloon)
        - Caça:      'd' (Warplane)
    
    São os objetos:
        - Bomb:     Objeto cujo objetivo é ser lançado por um caça a uma distancia, com determinado alcance
                    (3 niveis de capacidade) em relacao à posição do caça e sua rotacao correte. Ao ser detonada,
                    a bomba explode e destrói todas as entidades que estiverem dentro de seu raio de alcance.
                    Caso a entidade atingida seja um balão, o balão é destruído e todas as fotos que estavam
                    em seu rolo de fotos têm suas entidades clonadas e inseridas no banco de dados novamente com
                    um novo identificador único, de maneira que os clones não são influenciados pela detonação da
                    bomba em questão que os 'gerou'.
        - Picture:  Objeto que representa o estado visual em uma delimitada região da simulação em certo instante,
                    isto é, uma foto. Uma foto é tirada por um balao e possui um raio, uma altura, uma profundidade
                    e coordenadas que definem sua posição no espaço da simulação, juntamente aos elementos
                    capturados. Ao identificar que um elemento está dentro da região de captura de uma foto (frame),
                    este elemento é copiado e inserido na lista de elementos da foto, mantendo suas propriedades.

*/

typedef void * Entity;
typedef void * Picture;
typedef void * Bomb;

#define BOMB_CAPACITY_A 10
#define BOMB_CAPACITY_B 15
#define BOMB_CAPACITY_C 30

#define FILAS_AMOUNT 10
#define PICTURES_AMOUNT 15

// CREATION FUNCTIONS
/*
    Cria uma entidade comum, com uma forma geométrica associada e um identificador.
    Pré-condição: geo é uma forma geométrica válida.
*/
Entity    createCommon          (Geometry geo, int id);

/*
    Cria uma entidade balão, com uma forma geométrica associada e um identificador.
    Pré-condição: geo é uma forma geométrica válida.
*/
Entity    createBalloon         (Geometry geo, int id);

/*
    Cria uma entidade caça, com uma forma geométrica associada e um identificador.
    Pré-condição: geo é uma forma geométrica válida.
*/
Entity    createWarplane        (Geometry geo, int id);

/*
    Cria uma foto, com um raio, uma altura, uma profundidade, coordenadas que definem sua posição no espaço
    da simulação e uma lista de elementos (opcional) será associada à foto como seus elementos capturados.
    Pré-condição: radius, height, depth, são valores positivos. optional_list_of_elements deve ser NULL caso
                  não haja uma lista de elementos a ser associados à foto durante a criação, caso contrário
                  a lista deve ser válida.
*/
Picture   createPicture         (double radius, double height, double depth, double x0, double y0, void * optional_list_of_elements);

/*
    Cria uma bomba, com uma capacidade de alcance, coordenadas que definem sua posição central no espaço da simulação,
    uma distancia e um ângulo de lançamento. A capacidade de alcance é definida por um caractere que pode ser
    'A', 'B' ou 'C', onde 'A' representa uma capacidade de alcance de 10 unidades, 'B' representa uma capacidade
    de alcance de 15 unidades e 'C' representa uma capacidade de alcance de 30 unidades.
    Pré-condição: capacityType deve ser 'A', 'B' ou 'C'. Ox e Oy são as coordenadas de origem as quais sofrerão
                  deslocamento de acordo com a distancia e o ângulo de lançamento da bomba, assim definindo sua posição central
                  no espaço da simulação. distance e theta são valores positivos que definem a distancia e o ângulo
                  de lançamento da bomba, respectivamente.
*/
Bomb      defineBomb            (char capacityType, double Ox, double Oy, double distance, double theta);

// PROCESSING FUNCTIONS
/*
    Remove toda a memória alocada por uma entidade.
    Pré-condição: ent é uma entidade válida.
*/
void      removeEntity          (Entity ent);

/*
    Busca por uma entidade dentro uma lista de entidades, a partir de um identificador.
    Retorta a primeira entidade encontrada com o identificador especificado, caso não encontre
    nenhuma entidade com o identificador especificado, retorna NULL.
    Pré-condição: L é uma lista de entidades válida. Preferencialmente, id deve ser um identificador
                  associado a um elemento existente em L.
*/
Entity    searchEntbyIDinLst    (Lista L, int id);

/*
    Busca por uma forma geométrica dentro uma lista de entidades, a partir de um identificador.
    Retorta a primeira forma geométrica encontrada com o identificador especificado, caso não encontre
    nenhuma forma geométrica com o identificador especificado, retorna NULL.
    Pré-condição: L é uma lista de entidades válida. Preferencialmente, id deve ser um identificador
                  associado a um elemento existente em L.
*/
Geometry  searchGeobyIDinLst    (Lista L, int id);

// GENERAL FUNCTIONS
/*
    PARA O SEGUINTE CONJUNTO DE FUNÇÕES:
        - getEntType: retorna o tipo de uma entidade segundo a convenção estabelecida.
        - getEntID: retorna o identificador de uma entidade.
        - getEntGeo: retorna a forma geométrica associada a uma entidade.
        - setEntType: define o tipo de uma entidade segundo a convenção estabelecida.
        - setEntID: define o identificador de uma entidade.
        - setEntGeo: define a forma geométrica associada a uma entidade.
    Pré-condição: ent é uma entidade válida e type é um dos tipos definidos pela conveção de entidades.
*/
char      getEntType            (Entity ent);
int       getEntID              (Entity ent);
Geometry  getEntGeo             (Entity ent);
void      setEntType            (Entity ent, char type);
void      setEntID              (Entity ent, int id);
void      setEntGeo             (Entity ent, Geometry geo);

// BALLON FUNCTIONS
// Getters and Setters
/*
    PARA O SEGUINTE CONJUNTO DE FUNÇÕES:
        - setEntDepth: define a profundidade de foco de captura de foto do balao.
        - getEntDepth: retorna a profundidade de foco de captura de foto do balao.
        - setEntHeight: define a altura da foto a ser capturada pelo balao.
        - getEntHeight: retorna a altura da foto a ser capturada pelo balao.
        - setEntRadius: define o raio da foto a ser capturada pelo balao.
        - getEntRadius: retorna o raio da foto a ser capturada pelo balao.
    Pré-condição: ent é um BALÃO válido e depth, height e radius são valores positivos.
*/
void      setEntDepth           (Entity ent, double depth);
double    getEntDepth           (Entity ent);
void      setEntHeight          (Entity ent, double height);
double    getEntHeight          (Entity ent);
void      setEntRadius          (Entity ent, double radius);
double    getEntRadius          (Entity ent);
// Balloon's pictures
/*
    PARA O SEGUINTE CONJUNTO DE FUNÇÕES:
        - getPictureRadius: retorna o raio da foto.
        - getPictureHeight: retorna a altura da foto.
        - getPictureDepth: retorna a profundidade de foco de captura de foto.
        - getPictureCords: retorna as coordenadas da foto, x e y respectivamentes (x, y).
        - getPictureElements: retorna a lista de elementos capturados pela foto.
        - addEntPicture: adiciona uma entidade à lista de elementos capturados de uma foto.
        - popEntPicture: remove uma entidade da lista de elementos capturados de uma foto.
        - addPictureInFila: adiciona uma foto ao fim de uma fila de fotos de indice index associada a um balão.
        - popPictureInFila: remove a primeira foto de uma fila de fotos de indice index associada a um balão.
        - getFilaOfPictures: retorna a fila de fotos de índice index associada a um balão.
        - removePicture: remove a memória alocada por uma foto.
    Pré-condição: pic é uma foto válida, balloon é um balão válido e index é um índice válido da fila.
*/
double    getPictureRadius      (Picture pic);
double    getPictureHeight      (Picture pic);
double    getPictureDepth       (Picture pic);
double  * getPictureCords       (Picture pic);
Lista     getPictureElements    (Picture pic);
void      addEntPicture         (Entity ent, Picture pic);
Entity    popEntPicture         (Picture pic);
void      addPictureInFila      (Entity balloon, Picture pic, int index);
Picture   popPictureInFila      (Entity balloon, int index);
Fila      getFilaOfPictures     (Entity balloon, int index);
void      removePicture         (Picture pic);

// WARPLANE FUNCTIONS
// Warplane's actions
/*
    PARA O SEGUINTE CONJUNTO DE FUNÇÕES:
        - removeBomb: remove a memória alocada por uma bomba.
        - throwBomb: verifica se a entidade ent é antigida pela bomba bomb.
        - incrementEntShots: incrementa o número de tiros disparados por um caça ent.
        - getEntShots: retorna o número de tiros disparados por um caça ent.
        - addEntTargetID: adiciona um identificador de uma entidade à lista de alvos de um caça warplane.
        - popEntTargetID: remove e entao retorna o identificador de uma entidade da lista de alvos de um caça ent.
        - getEntTargetsID: retorna a lista de identificadores de entidades alvos de um caça ent.
        - setEntTargetsID: define a lista L de identificadores de entidades alvos a um caça warplane.
    Pré-condição: bomb é uma bomba válida, ent é uma entidade válida, warplane é um caça válido, L é uma lista
                  válida de identificadores de entidades válidas.
*/
void      removeBomb            (Bomb bomb);
bool      throwBomb             (Entity ent, Bomb bomb);
void      incrementEntShots     (Entity ent);
int       getEntShots           (Entity ent);
void      addEntTargetID        (Entity ent, Entity warplane);
int     * popEntTargetID        (Entity ent);
Lista     getEntTargetsID       (Entity ent);
void      setEntTargetsID       (Entity warplane, Lista L);


// BOMB FUNCTIONS
// Getters
/*
    PARA O SEGUINTE CONJUNTO DE FUNÇÕES:
        - getBombRadius: retorna o raio de alcance da bomba.
        - getBombOriginCord: retorna as coordenadas do ponto de origem da bomba, x e y respectivamentes (x, y).
        - getBombTargetCords: retorna as coordenadas do ponto central de explosão da bomba, x e y respectivamentes (x, y).
    Pré-condição: bomb é uma bomba válida.
*/
double   getBombRadius         (Bomb bomb);
double * getBombOriginCord     (Bomb bomb);
double * getBombTargetCords    (Bomb bomb);

#endif