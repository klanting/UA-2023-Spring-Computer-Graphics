//
// Created by tibov on 24/02/23.
//

#include "Color.h"
#include "iostream"
Color::Color(double r, double g, double b): red(r), green(g), blue(b) {

}


void Color::multiply(const Color &c) {
    red = red*c.red;
    green = green*c.green;
    blue = blue*c.blue;

    if (red > 1){
        red = 1.0;
    }

    if (green > 1){
        green = 1.0;
    }

    if (blue > 1){
        blue = 1.0;
    }
}
