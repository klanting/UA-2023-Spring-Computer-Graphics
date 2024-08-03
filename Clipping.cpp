//
// Created by tibov on 01/04/23.
//

#include "Clipping.h"

namespace Clipping{
    void clipNear(Figure* figure, double dNear){
        vector<Face> new_faces;
        vector<Vector3D> new_points;

        double dval = -dNear;

        for (auto face: figure->faces){

            pair<vector<Vector3D>, vector<Vector3D>> side_pair = CheckSide(figure, face, dval, "near", dNear);
            Cut(side_pair, "near", dval, dNear, new_faces, new_points);
        }

        figure->faces = new_faces;
        figure->points = new_points;

    }

    void clipFar(Figure* figure, double dFar){
        vector<Face> new_faces;
        vector<Vector3D> new_points;

        double dval = -dFar;

        for (auto face: figure->faces){

            pair<vector<Vector3D>, vector<Vector3D>> side_pair = CheckSide(figure, face, dval, "far", dFar);
            Cut(side_pair, "far", dval, dFar, new_faces, new_points);
        }

        figure->faces = new_faces;
        figure->points = new_points;
    }

    void clipRight(Figure* figure, double dNear, double dRight){
        vector<Face> new_faces;
        vector<Vector3D> new_points;

        double dval = dRight;

        for (auto face: figure->faces){
            pair<vector<Vector3D>, vector<Vector3D>> side_pair = CheckSide(figure, face, dval, "right", dNear);
            Cut(side_pair, "right", dval, dNear, new_faces, new_points);
        }

        figure->faces = new_faces;
        figure->points = new_points;

    }

    void clipLeft(Figure* figure, double dNear, double dLeft){
        vector<Face> new_faces;
        vector<Vector3D> new_points;

        double dval = dLeft;

        for (auto face: figure->faces){
            pair<vector<Vector3D>, vector<Vector3D>> side_pair = CheckSide(figure, face, dval, "left", dNear);
            Cut(side_pair, "left", dval, dNear, new_faces, new_points);

        }

        figure->faces = new_faces;
        figure->points = new_points;

    }

    void clipTop(Figure* figure, double dNear, double dTop){

        vector<Face> new_faces;
        vector<Vector3D> new_points;

        double dval = dTop;

        for (auto face: figure->faces){
            Vector3D A = figure->points[face.points[0]];
            Vector3D B = figure->points[face.points[1]];
            Vector3D C = figure->points[face.points[2]];
            vector<Vector3D> temp_fases = {A, B, C};

            vector<Vector3D> outside;
            vector<Vector3D> inside;

            pair<vector<Vector3D>, vector<Vector3D>> side_pair = CheckSide(figure, face, dval, "top", dNear);
            Cut(side_pair, "top", dval, dNear, new_faces, new_points);

        }

        figure->faces = new_faces;
        figure->points = new_points;

    }

    void clipBottom(Figure* figure, double dNear, double dBottom){
        vector<Face> new_faces;
        vector<Vector3D> new_points;

        double dval = dBottom;

        for (auto face: figure->faces){
            pair<vector<Vector3D>, vector<Vector3D>> side_pair = CheckSide(figure, face, dval, "bottom", dNear);
            Cut(side_pair, "top", dval, dNear, new_faces, new_points);

        }

        figure->faces = new_faces;
        figure->points = new_points;

    }

    pair<vector<Vector3D>, vector<Vector3D>> CheckSide(Figure* figure, const Face &face, double compare_value, const string& type, double dNear){

        bool greater = true;
        if (type == "near" || type == "right" || type == "top"){
            greater = true;
        }else if (type == "far" || type == "left"|| type == "bottom") {
            greater = false;
            compare_value = compare_value * -1;
        }

        vector<Vector3D> outside;
        vector<Vector3D> inside;

        Vector3D A = figure->points[face.points[0]];
        Vector3D B = figure->points[face.points[1]];
        Vector3D C = figure->points[face.points[2]];
        vector<Vector3D> temp_fases = {A, B, C};

        for (int i=0; i<3; i++){
            Vector3D current_point = temp_fases[i];

            double point_value = toValue(current_point, type, dNear);

            if (!greater){
                point_value = point_value*-1;
            }

            if (point_value > compare_value){
                outside.push_back(current_point);
            }else{
                inside.push_back(current_point);
            }


        }

        return make_pair(outside, inside);

    }

    double toValue(Vector3D& point, const string& type, double dNear){
        if (type == "near" || type == "far"){
            return point.z;
        }else if (type == "right" || type == "left"){
            double x_acc = point.x/(-point.z)*dNear;
            return x_acc;
        }else if (type == "top" || type == "bottom"){
            double y_acc = point.y/(-point.z)*dNear;
            return y_acc;
        }
        return 0;
    }

    void Cut(const pair<vector<Vector3D>, vector<Vector3D>>& value_pair, const string& type, double dval, double dNear, vector<Face> &new_faces, vector<Vector3D> &new_points){
        vector<Vector3D> outside = value_pair.first;
        vector<Vector3D> inside = value_pair.second;

        if (outside.size() == 0){
            new_points.push_back(inside[0]);
            new_points.push_back(inside[1]);
            new_points.push_back(inside[2]);
            new_faces.push_back(Face({(int) new_points.size()-3, (int) new_points.size()-2, (int) new_points.size()-1}));
        }else if (outside.size() == 1){
            Vector3D outside_point = outside[0];
            Vector3D inside_point1 = inside[0];
            Vector3D inside_point2 = inside[1];
            double p = CalculateP(dval, inside_point1, outside_point, type, dNear);
            Vector3D new_point_1 = Vector3D::point(p*outside_point+(1-p)*inside_point1);
            p = CalculateP(dval, inside_point2, outside_point, type, dNear);
            Vector3D new_point_2 = Vector3D::point(p*outside_point+(1-p)*inside_point2);

            new_points.push_back(inside_point1);
            new_points.push_back(new_point_1);
            new_points.push_back(new_point_2);
            new_points.push_back(inside_point2);
            new_faces.push_back(Face({(int) new_points.size()-4, (int) new_points.size()-2, (int) new_points.size()-1}));
            new_faces.push_back(Face({(int) new_points.size()-4, (int) new_points.size()-3, (int) new_points.size()-2}));

        }else if (outside.size() == 2){
            Vector3D outside_point1 = outside[0];
            Vector3D outside_point2 = outside[1];
            Vector3D inside_point = inside[0];

            double p = CalculateP(dval, inside_point, outside_point1, type, dNear);
            Vector3D new_point_1 = Vector3D::point(p*outside_point1+(1-p)*inside_point);
            p = CalculateP(dval, inside_point, outside_point2, type, dNear);
            Vector3D new_point_2 = Vector3D::point(p*outside_point2+(1-p)*inside_point);

            new_points.push_back(inside_point);
            new_points.push_back(new_point_1);
            new_points.push_back(new_point_2);
            new_faces.push_back(Face({(int) new_points.size()-3, (int) new_points.size()-2, (int) new_points.size()-1}));
        }
    }

    double CalculateP(double dval, const Vector3D& p1, const Vector3D& p2, const string& type, double dNear){
        if (type == "near" || type == "far"){
            return (dval-p1.z)/(p2.z-p1.z);
        }else if (type == "right" || type == "left"){
            double noemer = (p1.x-p2.x)*dNear + (p1.z-p2.z)*dval;
            double p = (p1.x*dNear+p1.z*dval)/noemer;
            return p;
        }else{
            double noemer = (p1.y-p2.y)*dNear + (p1.z-p2.z)*dval;
            double p = (p1.y*dNear+p1.z*dval)/noemer;
            return p;
        }
    }
}