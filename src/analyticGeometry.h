#ifndef ANALYTIC_GEOMETRY_H
#define ANALYTIC_GEOMETRY_H

#include <stdbool.h>

bool isCircleInsideRectangle(double Cx, double Cy, double r, double Rxi, double Ryi, double Rxf, double Ryf);
bool isRectangleInsideRectangle(double Axi, double Ayi, double Axf, double Ayf, double Bxi, double Byi, double Bxf, double Byf);
double distance(double x1, double y1, double x2, double y2);

#endif