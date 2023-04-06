#ifndef ANALYTIC_GEOMETRY_H
#define ANALYTIC_GEOMETRY_H

#include <stdbool.h>

#define PI 3.14159265358979323846

double   distance               (double x1,  double y1,  double x2,  double y2);
double   slope                  (double x1, double y1, double x2, double y2);
double   LineFunction           (double m,  double b,  double x);
double * Translocation          (double xi, double yi, double distance, double theta);
double   circleArea             (double r);
double   circunference          (double r);
double   rectangleArea          (double width, double height);




// Validations functions
bool doSegmentsIntersect        (double Lx1, double Ly1, double Lx2, double Ly2, 
                                 double Sx1, double Sy1, double Sx2, double Sy2);
bool isPointInsideCircle        (double Cx, double Cy, double r, double Px, double Py);
bool isLineInsideRectangle      (double Lx1, double Ly1, double Lx2, double Ly2,
                                 double Rxi, double Ryi, double Rxf, double Ryf);

bool isCircleInsideRectangle    (double Cx,  double Cy,  double r, 
                                 double Rxi, double Ryi, double Rxf, double Ryf);

bool isRectangleInsideRectangle (double Axi, double Ayi, double Axf, double Ayf,
                                 double Bxi, double Byi, double Bxf, double Byf);

bool isLineInsideRectangle      (double x1,  double y1,  double x2,  double y2, 
                                 double Rxi, double Ryi, double Rxf, double Ryf);
bool isPointInsideRectangle     (double x1, double y1, 
                                 double Rxi, double Ryi, double Rxf, double Ryf);
bool isCircleInsideCircle       (double Cx1, double Cy1, double r1, 
                                 double Cx2, double Cy2, double r2);
bool isLineInsideCircle         (double Lx1, double Ly1, double Lx2, double Ly2, 
                                 double Cx,  double Cy,  double r);

#endif