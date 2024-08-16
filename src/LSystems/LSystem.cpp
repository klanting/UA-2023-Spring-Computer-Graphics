//
// Created by tibov on 25/02/23.
//

#include "LSystem.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include "../../libraries/l_parser.h"



LSystem::LSystem(const LParser::LSystem2D &l_system, const Color &c): l_system(l_system), c(c) {
    const double pi = 3.14159265359;
    pos = {0, 0};
    initiator = l_system.get_initiator();
    start_angle = l_system.get_starting_angle()/360*2*pi;
    delta_angle = l_system.get_angle()/360*2*pi;
    angle = start_angle;
    points.emplace_back(0, 0);


    string s;
    for (char c: initiator){
        s += l_replace(c, l_system.get_nr_iterations());

    }
    l_fill(s);


}


string LSystem::l_replace(const char &v, int amount) {
    if (amount == 0){
        string s(1, v);
        return s;
    }else{
        if (find(l_system.get_alphabet().begin(), l_system.get_alphabet().end(), v) == l_system.get_alphabet().end()){
            string s(1, v);
            return s;
        }

        string s;
        for (char c: l_system.get_replacement(v)){
            if (find(l_system.get_alphabet().begin(), l_system.get_alphabet().end(), c) == l_system.get_alphabet().end()){
                string t(1, c);
                s += t;
            }else{
                s += l_replace(c, amount-1);
            }

        }
        return s;
    }
}

void LSystem::l_fill(const string& s){
    stack<double> stack_x;
    stack<double> stack_y;
    stack<double> stack_angle;

    Line2D* last_line = nullptr;
    char last_char = '\0';
    for (char c: s){
        if (c == '+'){
            angle+=delta_angle;
        }else if (c == '-') {
            angle -= delta_angle;
        }else if (c == '('){
            stack_x.push(pos.first);
            stack_y.push(pos.second);
            stack_angle.push(angle);
        }else if (c == ')'){
            pos.first = stack_x.top();
            stack_x.pop();
            pos.second = stack_y.top();
            stack_y.pop();
            angle = stack_angle.top();
            stack_angle.pop();

            Point2D p(pos.first, pos.second);
            points.push_back(p);

        }else{
            bool v = l_system.draw(c);

            pos.first += cos(angle);
            pos.second += sin(angle);
            Point2D p2(pos.first, pos.second);
            points.push_back(p2);

            if (last_char == c && last_line != nullptr && v){
                last_line->p2 = p2;
            }else if (v){

                Line2D* l = new Line2D(*(points.end()-2), *(points.end()-1), LSystem::c);
                lines.push_back(l);

                last_line = l;
            }



        }

        last_char = c;
    }

}

Lines2D LSystem::get_lines() {

    return lines;
}

LSystem::~LSystem() {
    for (Line2D* l : lines){
        delete l;
    }
}

