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

    red = std::min(red, 1.0);
    green = std::min(green, 1.0);
    blue = std::min(blue, 1.0);
}

double Color::getRed() const {
    return red;
}

double Color::getGreen() const {
    return green;
}

double Color::getBlue() const {
    return blue;
}
