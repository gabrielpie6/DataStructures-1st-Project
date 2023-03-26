#include "analyticGeometry.h"

#include <math.h>

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

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}