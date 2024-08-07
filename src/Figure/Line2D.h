//
// Created by tibov on 24/02/23.
//

#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H

#include "Point2D.h"
#include "Color.h"
#include "vector3d.h"

class Line2D {
public:
    Line2D(Point2D &p1, Point2D &p2, Color color);
    Line2D(Vector3D p1, Vector3D p2, Color color);
    double get_value_x1();
    double get_value_x2();
    double get_value_y1();
    double get_value_y2();
    double get_value_smallest_x();
    double get_value_largest_x();
    double get_value_smallest_y();
    double get_value_largest_y();
    Point2D p1;
    Point2D p2;
    Color color;
    double z1;
    double z2;
};


#endif //ENGINE_LINE2D_H
