//
// Created by tibov on 24/02/23.
//

#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H


class Color {
public:
    explicit Color(double r, double g, double b);
    void multiply(const Color& c);
    double red;
    double green;
    double blue;
};


#endif //ENGINE_COLOR_H
