#include "analyticGeometry.h"

#include <math.h>
#include <stdio.h>

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
double slope(double x1, double y1, double x2, double y2)
{
    if (x1 != x2)
        return (y2 - y1) / (x2 - x1);
}
double LineFunction(double m, double b, double x)
{
    return m * x + b;
}




// Validations functions

// Problema em caso específico quando L é vertical
bool doSegmentsIntersect(double Lx1, double Ly1, double Lx2, double Ly2, double Sx1, double Sy1, double Sx2, double Sy2) 
{
    double den = (Sy2 - Sy1) * (Lx2 - Lx1) - (Sx2 - Sx1) * (Ly2 - Ly1);
    
    // Verificar se os segmentos são paralelos
    if (den == 0) {
        if (Lx1 == Lx2) {
            if ((Sy1 <= Ly1 && Ly1 <= Sy2) || (Sy1 <= Ly2 && Ly2 <= Sy2) ||
                (Ly1 <= Sy1 && Sy1 <= Ly2) || (Ly1 <= Sy2 && Sy2 <= Ly2)) {
                return true;
            }
        } else {
            if ((Sx1 <= Lx1 && Lx1 <= Sx2) || (Sx1 <= Lx2 && Lx2 <= Sx2) ||
                (Lx1 <= Sx1 && Sx1 <= Lx2) || (Lx1 <= Sx2 && Sx2 <= Lx2)) {
                return true;
            }
        }
        return false;
    }
    
    double ua = ((Sx2 - Sx1) * (Ly1 - Sy1) - (Sy2 - Sy1) * (Lx1 - Sx1)) / den;
    double ub = ((Lx2 - Lx1) * (Ly1 - Sy1) - (Ly2 - Ly1) * (Lx1 - Sx1)) / den;
    
    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
        return true;
    } else {
        return false;
    }
}

bool isCircleInsideRectangle(double Cx, double Cy, double r, double Rxi, double Ryi, double Rxf, double Ryf)
{   
    // Avaliar dentro do retângulo expandido
    if ((Cx >= Rxi - r && Cx <= Rxf + r) && (Cy >= Ryi     && Cy <= Ryf    ) || 
        (Cx >= Rxi     && Cx <= Rxf    ) && (Cy >= Ryi - r && Cy <= Ryf + r))
        return true;
    else
        // Avaliar vértices
        if ((pow(Cx - Rxi, 2) + pow(Cy - Ryi, 2) <= pow(r, 2)) || // Vértice superior esquerdo
            (pow(Cx - Rxf, 2) + pow(Cy - Ryi, 2) <= pow(r, 2)) || // Vértice superior direito
            (pow(Cx - Rxi, 2) + pow(Cy - Ryf, 2) <= pow(r, 2)) || // Vértice inferior esquerdo
            (pow(Cx - Rxf, 2) + pow(Cy - Ryf, 2) <= pow(r, 2)))   // Vértice inferior direito
            return true;
        else
            return false;
}

bool isRectangleInsideRectangle(double Axi, double Ayi, double Axf, double Ayf, double Bxi, double Byi, double Bxf, double Byf)
{
    if (
        ((Axi >= Bxi && Axi <= Bxf) && (Ayi >= Byi && Ayi <= Byf)) || // Vértice superior esquerdo
        ((Axf >= Bxi && Axf <= Bxf) && (Ayi >= Byi && Ayi <= Byf)) || // Vértice superior direito
        ((Axi >= Bxi && Axi <= Bxf) && (Ayf >= Byi && Ayf <= Byf)) || // Vértice inferior esquerdo
        ((Axf >= Bxi && Axf <= Bxf) && (Ayf >= Byi && Ayf <= Byf)))   // Vértice inferior direito
        return true;
    else
        return false;
}

bool isPointInsideRectangle(double x1, double y1, double Rxi, double Ryi, double Rxf, double Ryf)
{
    if ((x1 >= Rxi && x1 <= Rxf) && (y1 >= Ryi && y1 <= Ryf))
        return true;
    else
        return false;
}

bool isLineInsideRectangle(double x1, double y1, double x2, double y2, double Rxi, double Ryi, double Rxf, double Ryf)
{
    if (isPointInsideRectangle(x1, y1, Rxi, Ryi, Rxf, Ryf) || isPointInsideRectangle(x2, y2, Rxi, Ryi, Rxf, Ryf))
    {
        //printf("oi\n");
        return true;
    }
    else
        if (doSegmentsIntersect(x1,y1,x2,y2,  Rxi, Ryi, Rxf, Ryi) || // Aresta superior
            doSegmentsIntersect(x1,y1,x2,y2,  Rxf, Ryi, Rxf, Ryf) || // Aresta direita
            doSegmentsIntersect(x1,y1,x2,y2,  Rxi, Ryf, Rxf, Ryf) || // Aresta inferior
            doSegmentsIntersect(x1,y1,x2,y2,  Rxi, Ryi, Rxi, Ryf))   // Aresta esquerda
            return true;
        else
            return false;
}



/*
void main()
{
    //Ambiente de testes
    bool teste;
   for (int i = -5; i <= 15; i++)
   {
    teste = isLineInsideRectangle(i,1.5,  i+0.02,2.5,  1,1,3,1);
    printf("Teste i=[%d]: %d\n",i, teste);
   }
}
*/
