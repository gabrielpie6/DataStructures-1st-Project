#include "analyticGeometry.h"

#include <math.h>

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
double * Translocation(double xi, double yi, double distance, double theta)
{
    double PI = 3.14159265358979323846;
    double rad = (PI * theta)/180;
    static double cords[2];
    cords[0] = xi - distance * sin(rad);
    cords[1] = yi + distance * cos(rad);
    return &cords[0];
}




// Validations functions

// Helper function to check if point q lies on line segment 'pr'
bool onSegment(double px, double py, double qx, double qy, double rx, double ry)
{
    if (qx <= fmax(px, rx) && qx >= fmin(px, rx) &&
        qy <= fmax(py, ry) && qy >= fmin(py, ry))
       return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(double px, double py, double qx, double qy, double rx, double ry)
{
    double val = (qy - py) * (rx - qx) -
              (qx - px) * (ry - qy);

    if (val == 0) return 0;  // collinear

    return (val > 0)? 1: 2; // clockwise or counterclockwise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doSegmentsIntersect(double Lx1, double Ly1, double Lx2, double Ly2, double Sx1, double Sy1, double Sx2, double Sy2)
{
    // Find the four orientations needed for general and special cases
    int o1 = orientation(Lx1, Ly1, Lx2, Ly2, Sx1, Sy1);
    int o2 = orientation(Lx1, Ly1, Lx2, Ly2, Sx2, Sy2);
    int o3 = orientation(Sx1, Sy1, Sx2, Sy2, Lx1, Ly1);
    int o4 = orientation(Sx1, Sy1, Sx2, Sy2, Lx2, Ly2);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // L1, L2 and S1 are collinear and S1 lies on segment L1L2
    if (o1 == 0 && onSegment(Lx1, Ly1, Sx1, Sy1, Lx2, Ly2)) return true;

    // L1, L2 and S2 are collinear and S2 lies on segment L1L2
    if (o2 == 0 && onSegment(Lx1, Ly1, Sx2, Sy2, Lx2, Ly2)) return true;

    // S1, S2 and L1 are collinear and L1 lies on segment S1S2
    if (o3 == 0 && onSegment(Sx1, Sy1, Lx1, Ly1, Sx2, Sy2)) return true;

    // S1, S2 and L2 are collinear and L2 lies on segment S1S2
    if (o4 == 0 && onSegment(Sx1, Sy1, Lx2, Ly2, Sx2, Sy2)) return true;

    return false; // Doesn't fall in any of the above cases
}

bool isPointInsideCircle(double Cx, double Cy, double r, double Px, double Py)
{
    return (pow(Px - Cx, 2) + pow(Py - Cy, 2) <= pow(r, 2));
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
    if (((Axi >= Bxi && Axi <= Bxf) && (Ayi >= Byi && Ayi <= Byf)) || // Vértice superior esquerdo
        ((Axf >= Bxi && Axf <= Bxf) && (Ayi >= Byi && Ayi <= Byf)) || // Vértice superior direito
        ((Axi >= Bxi && Axi <= Bxf) && (Ayf >= Byi && Ayf <= Byf)) || // Vértice inferior esquerdo
        ((Axf >= Bxi && Axf <= Bxf) && (Ayf >= Byi && Ayf <= Byf)))   // Vértice inferior direito
        return true;
    else
        // checar se existe um subretangulo
        if (doSegmentsIntersect(Axi, Ayi, Axf, Ayi,     Bxi, Byi, Bxi, Byf) || // 
            doSegmentsIntersect(Axi, Ayf, Axf, Ayf,     Bxi, Byi, Bxi, Byf) || //

            doSegmentsIntersect(Axi, Ayi, Axi, Ayf,     Bxi, Byi, Bxf, Byi) ||
            doSegmentsIntersect(Axf, Ayi, Axf, Ayf,     Bxi, Byi, Bxf, Byi))
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
