//
// Created by tibov on 24/02/23.
//

#include "Line2D.h"
#include "Point2D.h"
#include "Color.h"
#include <iostream>


Line2D::Line2D(Point2D &p1, Point2D &p2, Color color): p1(p1), p2(p2), color(color) {

}

Line2D::Line2D(Vector3D p1, Vector3D p2, Color color): color(color) {
    Point2D pm_1(p1.x, p1.y);
    Line2D::p1 = pm_1;
    Point2D pm_2(p2.x, p2.y);
    Line2D::p2 = pm_2;
    z1 = p1.z;
    z2 = p2.z;
}


double Line2D::get_value_x1() {
    return p1.x;
}

double Line2D::get_value_x2() {
    return p2.x;
}

double Line2D::get_value_y1() {
    return p1.y;
}

double Line2D::get_value_y2() {
    return p2.y;
}

double Line2D::get_value_smallest_x() {
    if (p1.x < p2.x){
        return p1.x;
    }else{
        return p2.x;
    }
}

double Line2D::get_value_largest_x() {
    if (p1.x > p2.x){
        return p1.x;
    }else{
        return p2.x;
    }
}

double Line2D::get_value_smallest_y() {
    if (p1.y < p2.y){
        return p1.y;
    }else{
        return p2.y;
    }
}

double Line2D::get_value_largest_y() {
    if (p1.y > p2.y){
        return p1.y;
    }else{
        return p2.y;
    }
}

