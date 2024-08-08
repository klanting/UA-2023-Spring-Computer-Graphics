//
// Created by tibov on 19/03/23.
//

#include "LSystem3D.h"
#include <algorithm>
#include <cmath>
LSystem3D::LSystem3D(const LParser::LSystem3D &l_system, const Color &c): l_system(l_system), c(c)   {
    const double pi = 3.14159265359;
    pos = Vector3D::point(0, 0, 0);

    U = Vector3D::point(0, 0, 1);
    H = Vector3D::point(1, 0, 0);
    L = Vector3D::point(0, 1, 0);

    initiator = l_system.get_initiator();
    delta_angle = l_system.get_angle()/360*2*M_PI;
    points.emplace_back(Vector3D::point(0, 0, 0));


    string s;
    for (char c: initiator){
        s += l_replace(c, (int) l_system.get_nr_iterations());

    }
    l_fill(s);

}

string LSystem3D::l_replace(const char &v, int amount) {
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

void LSystem3D::l_fill(const string &s) {
    stack<Vector3D> stack_pos;
    stack<Vector3D> stack_H;
    stack<Vector3D> stack_U;
    stack<Vector3D> stack_L;

    Line2D* last_line = nullptr;
    bool last_l = false;
    for (char c: s){
        if (c == '+'){
            Vector3D H_new = H*cos(delta_angle)+L*sin(delta_angle);
            Vector3D L_new = -H*sin(delta_angle)+L*cos(delta_angle);
            H = H_new;
            L = L_new;
            last_l = false;
        }else if (c == '-') {
            Vector3D H_new = H*cos(-delta_angle)+L*sin(-delta_angle);
            Vector3D L_new = -H*sin(-delta_angle)+L*cos(-delta_angle);
            H = H_new;
            L = L_new;
            last_l = false;
        }else if (c == '^'){
            Vector3D H_new = H*cos(delta_angle)+U*sin(delta_angle);
            Vector3D U_new = -H*sin(delta_angle)+U*cos(delta_angle);
            H = H_new;
            U = U_new;
            last_l = false;
        }else if (c == '&'){
            Vector3D H_new = H*cos(-delta_angle)+U*sin(-delta_angle);
            Vector3D U_new = -H*sin(-delta_angle)+U*cos(-delta_angle);
            H = H_new;
            U = U_new;
            last_l = false;
        }else if (c == '\\'){
            Vector3D L_new = L*cos(delta_angle)-U*sin(delta_angle);
            Vector3D U_new = L*sin(delta_angle)+U*cos(delta_angle);
            L = L_new;
            U = U_new;
            last_l = false;
        }else if (c == '/'){
            Vector3D L_new = L*cos(-delta_angle)-U*sin(-delta_angle);
            Vector3D U_new = L*sin(-delta_angle)+U*cos(-delta_angle);
            L = L_new;
            U = U_new;
            last_l = false;
        }else if (c == '|'){
            H = -1*H;
            L = -1*L;
            last_l = false;
        }else if (c == '('){
            stack_pos.push(pos);
            stack_H.push(Vector3D::point(H.x, H.y, H.z));
            stack_U.push(Vector3D::point(U.x, U.y, U.z));
            stack_L.push(Vector3D::point(L.x, L.y, L.z));
            last_l = false;
        }else if (c == ')'){

            pos = stack_pos.top();
            stack_pos.pop();
            H = stack_H.top();
            U = stack_U.top();
            L = stack_L.top();
            stack_H.pop();
            stack_U.pop();
            stack_L.pop();


            points.push_back(Vector3D::point(pos.x, pos.y, pos.z));
            last_l = false;


        }else{
            bool v = l_system.draw(c);
            pos += H;

            points.push_back(Vector3D::point(pos.x, pos.y, pos.z));

            if (last_l){
                //do later
                //last_line->p2 = p2;
                points.pop_back();
                points.pop_back();
                points.push_back(Vector3D::point(pos.x, pos.y, pos.z));

                vector<int> last_line= lines[lines.size()-1];
                lines[lines.size()-1][1] = (int) points.size()-1;
            }else if (v){

                lines.push_back({(int) points.size()-2, (int) points.size()-1});
                //last_line = l;

            }

            last_l = true;



        }
    }

}

Figure *LSystem3D::get_fig() {
    Figure* fig = new Figure(points, lines, c);
    return fig;
}
