//
// Created by tibov on 17/05/23.
//

#include "TextureCoord.h"

Color TextureCoord::getAmbient(double u, double v) {
    double width = img_ambient.get_width();
    double height = img_ambient.get_height();

    while (u < 0){
        u += 1;
    }

    while (v < 0){
        v += 1;
    }

    while (u > 1){
        u -= 1;
    }

    while (v > 1){
        v -= 1;
    }

    int x = u*width;
    int y = v*height;



    Color ambient(img_ambient(x, y).red/255.0, img_ambient(x, y).green/255.0, img_ambient(x, y).blue/255.0);

    return ambient;
}

Color TextureCoord::getDifuus(double u, double v) {
    double width = img_difuus.get_width();
    double height = img_difuus.get_height();

    while (u < 0){
        u += 1;
    }

    while (v < 0){
        v += 1;
    }

    while (u > 1){
        u -= 1;
    }

    while (v > 1){
        v -= 1;
    }

    int x = u*width;
    int y = v*height;



    Color ambient(img_ambient(x, y).red/255.0, img_ambient(x, y).green/255.0, img_ambient(x, y).blue/255.0);

    return ambient;
}
