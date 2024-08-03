//
// Created by tibov on 19/03/23.
//

#ifndef ENGINE_L_SYSTEM3D_H
#define ENGINE_L_SYSTEM3D_H
#include "l_parser.h"
#include <string>
#include <list>
#include <vector>
#include "easy_image.h"
#include "ini_configuration.h"
#include "l_parser.h"
#include "stack"
#include "tools2D.h"
#include "vector3d.h"
#include "Figure.h"

class L_system3D {
public:
    L_system3D(const LParser::LSystem3D &l_system, const Color &c);
    //~L_system3D();
    string l_replace(const char& v, int amount);
    void l_fill(const string& s);
    Figure* get_fig();
private:
    LParser::LSystem3D l_system;
    double delta_angle;
    string initiator;

    Vector3D H;
    Vector3D L;
    Vector3D U;

    Vector3D pos;
    vector<Vector3D> points;
    vector<vector<int>> lines;
    Color c;

};


#endif //ENGINE_L_SYSTEM3D_H
