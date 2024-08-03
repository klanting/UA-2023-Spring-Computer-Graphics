//
// Created by tibov on 25/02/23.
//

#ifndef ENGINE_L_SYSTEM_H
#define ENGINE_L_SYSTEM_H
#include "l_parser.h"
#include <string>
#include "Line2D.h"
#include <list>
#include <vector>
#include "easy_image.h"
#include "ini_configuration.h"
#include "l_parser.h"
#include "stack"
using namespace std;
using Lines2D = list<Line2D*>;

class L_system {
public:
    L_system(const LParser::LSystem2D &l_system, const Color &c);

    ~L_system();
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


#endif //ENGINE_L_SYSTEM_H
