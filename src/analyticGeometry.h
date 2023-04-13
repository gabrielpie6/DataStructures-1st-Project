#ifndef ANALYTIC_GEOMETRY_H
#define ANALYTIC_GEOMETRY_H

#include <stdbool.h>

#define PI 3.14159265358979323846

/*
    Calcula a distância euclidiana entre dois pontos A = (x1, y1) e B = (x2, y2)

    pré-condição: nenhuma
*/
double   distance               (double x1,  double y1,  double x2,  double y2);

/*
    Calcula a inclinação da reta que passa pelos pontos A = (x1, y1) e B = (x2, y2)

    pré-condição: x1 != x2
*/
double   slope                  (double x1, double y1, double x2, double y2);

/*
    Calcula o valor de f(x) dada pela reta no plano cartesiano f: y = mx + b

    pré-condição: nenhuma
*/
double   LineFunction           (double m,  double b,  double x);

/*
    Opera um ponto A = (xi, yi) ao realizar o deslocamento de <distance> unidades no eixo X e então
    rotacionado <theta> graus no sentido horário. O resultado de A operado é um novo ponto que é retornado
    como vetor (double x, double y).

    pre-condição: distance >= 0
*/
double * Translocation          (double xi, double yi, double distance, double theta);

/*
    Calcula a área de um círculo de raio r e retorna o resultado.

    pré-condição: r >= 0
*/
double   circleArea             (double r);

/*
    Calcula o comprimento da circunferência de um círculo de raio r e retorna o resultado.

    pré-condição: r >= 0
*/
double   circunference          (double r);

/*
    Calcula a área de um retângulo de largura width e altura height e retorna o resultado.

    pré-condição: width >= 0 e height >= 0
*/
double   rectangleArea          (double width, double height);



//
// VALIDATION FUNCTIONS
//
/*
    Verifica se um segmento de reta L formado por dois pontos-âncora L1 = (Lx1, Ly1) e L2 = (Lx2, Ly2)
    intersecta um outro segmento de reta S formado por dois pontos-âncora S1 = (Sx1, Sy1) e S2 = (Sx2, Sy2).
    Retorna true caso os segmentos de reta se intersectem e false caso contrário.

    pré-condição: comprimento de L > 0 e comprimento de S > 0
*/
bool doSegmentsIntersect        (double Lx1, double Ly1, double Lx2, double Ly2, 
                                 double Sx1, double Sy1, double Sx2, double Sy2);

/*
    Verifica se um ponto P = (Px, Py) está dentro de um círculo de centro C = (Cx, Cy) e raio r.
    Retorna true caso o ponto esteja dentro do círculo e false caso contrário.

    pré-condição: r > 0
*/
bool isPointInsideCircle        (double Cx, double Cy, double r, double Px, double Py);

/*
    Verifica se um segmento de reta L formado por dois pontos-âncora L1 = (Lx1, Ly1) e L2 = (Lx2, Ly2)
    intersecta um retângulo formado por dois pontos-âncoras Ri = (Rxi, Ryi) o vértice do canto superior esquerdo
    e Rf = (Rxf, Ryf) o vértice do canto inferior direito. Retorna true caso o segmento de reta e o círculo
    se intersectem e false caso contrário.

    pré-condição: comprimento de L > 0 e Ri != Rf
*/
bool isLineInsideRectangle      (double Lx1, double Ly1, double Lx2, double Ly2,
                                 double Rxi, double Ryi, double Rxf, double Ryf);


/*
    Verifica se um círculo de centro C = (Cx, Cy) e raio r possui alguma parcela dentro de um retângulo formado 
    por dois pontos-âncoras Ri = (Rxi, Ryi) o vértice do canto superior esquerdo e Rf = (Rxf, Ryf) o vértice do canto
    inferior direito. Retorna true caso o círculo esteja parcialmente dentro do retângulo e false caso contrário.

    pré-condição: r > 0 e Ri != Rf
*/
bool isCircleInsideRectangle    (double Cx,  double Cy,  double r, 
                                 double Rxi, double Ryi, double Rxf, double Ryf);


/*
    Verifica se um retângulo A formado por dois pontos-âncoras Ai = (Axi, Ayi) o vértice do canto superior esquerdo
    e Af = (Axf, Ayf) o vértice do canto inferior direito está PARCIALMENTE dentro de um retângulo B formado por
    dois pontos-âncoras Bi = (Bxi, Byi) o vértice do canto superior esquerdo e Bf = (Bxf, Byf) o vértice do canto
    inferior direito. Retorna true caso o retângulo A esteja parcialmente dentro do retângulo B e false caso contrário.

    pré-condição: Ai != Af e Bi != Bf
*/
bool isRectangleInsideRectangle (double Axi, double Ayi, double Axf, double Ayf,
                                 double Bxi, double Byi, double Bxf, double Byf);


/*
    Verifica se um segmento de reta L formado por dois pontos-âncora L1 = (x1, y1) e L2 = (x2, y2) possui alguma
    parcela dentro de um retângulo formado por dois pontos-âncoras Ri = (Rxi, Ryi) o vértice do canto superior esquerdo 
    e Rf = (Rxf, Ryf) o vértice do canto inferior direito. Retorna true caso o segmento de reta e o retângulo
    se intersectem e false caso contrário.

    pré-condição: comprimento de L > 0 e Ri != Rf
*/
bool isLineInsideRectangle      (double x1,  double y1,  double x2,  double y2, 
                                 double Rxi, double Ryi, double Rxf, double Ryf);

/*
    Verifica se um ponto P = (x1, y1) está dentro de um retângulo formado por dois pontos-âncoras Ri = (Rxi, Ryi) o vértice
    do canto superior esquerdo e Rf = (Rxf, Ryf) o vértice do canto inferior direito. Retorna true caso o ponto esteja
    dentro do retângulo e false caso contrário.

    pré-condição: Ri != Rf
*/
bool isPointInsideRectangle     (double x1, double y1, 
                                 double Rxi, double Ryi, double Rxf, double Ryf);

/*
    Verifica se um círculo A formado por um centro A = (Cx1, Cy1) e um raio r1 possui alguma parcela dentro de um
    círculo B formado por um centro B = (Cx2, Cy2) e um raio r2. Retorna true caso o círculo A esteja parcialmente
    dentro do círculo B e false caso contrário.

    pré-condição: r1 > 0 e r2 > 0
*/
bool isCircleInsideCircle       (double Cx1, double Cy1, double r1, 
                                 double Cx2, double Cy2, double r2);

/*
    Verifica se um segmento de reta L formado por dois pontos-âncora L1 = (Lx1, Ly1) e L2 = (Lx2, Ly2) possui alguma
    parcela dentro de um círculo formado por um centro C = (Cx, Cy) e um raio r. Retorna true caso o segmento de reta
    e o círculo se intersectem e false caso contrário.

    pré-condição: comprimento de L > 0 e r > 0
*/
bool isLineInsideCircle         (double Lx1, double Ly1, double Lx2, double Ly2, 
                                 double Cx,  double Cy,  double r);

#endif