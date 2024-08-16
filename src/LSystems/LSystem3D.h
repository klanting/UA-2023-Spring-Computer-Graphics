//
// Created by tibov on 19/03/23.
//

#ifndef ENGINE_LSYSTEM3D_H
#define ENGINE_LSYSTEM3D_H
#include "../../libraries/l_parser.h"
#include <string>
#include <list>
#include <vector>
#include "../../libraries/easy_image.h"
#include "../../libraries/ini_configuration.h"
#include "../../libraries/l_parser.h"
#include "stack"
#include "../2DProjection/tools2D.h"
#include "../../libraries/vector3d.h"
#include "../Figure/Figure.h"

class LSystem3D {
public:
    LSystem3D(const LParser::LSystem3D &l_system, const Color &c);
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


#endif //ENGINE_LSYSTEM3D_H
