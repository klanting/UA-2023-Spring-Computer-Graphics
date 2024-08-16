//
// Created by tibov on 25/02/23.
//

#ifndef ENGINE_LSYSTEM_H
#define ENGINE_LSYSTEM_H
#include "../../libraries/l_parser.h"
#include <string>
#include "../Figure/Line2D.h"
#include <list>
#include <vector>
#include "../../libraries/easy_image.h"
#include "../../libraries/ini_configuration.h"
#include "../../libraries/l_parser.h"
#include "stack"
using namespace std;
using Lines2D = list<Line2D*>;

class LSystem {
public:
    LSystem(const LParser::LSystem2D &l_system, const Color &c);

    ~LSystem();
    string l_replace(const char& v, int amount);
    void l_fill(const string& s);
    Lines2D get_lines();


private:
    double angle;
    double start_angle;
    double delta_angle;
    string initiator;
    LParser::LSystem2D l_system;

    pair<double, double> pos;
    vector<Point2D> points;
    Lines2D lines;
    Color c;




};


#endif //ENGINE_LSYSTEM_H
