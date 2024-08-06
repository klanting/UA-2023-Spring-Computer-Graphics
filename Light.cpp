//
// Created by tibov on 26/04/23.
//

#include "Light.h"
#include "Color.h"
#include <cmath>
#include <tuple>
#include "Figure.h"
#include "tools2D.h"
Light::Light() {

}

void Light::EyePerspectifTransform(const Vector3D &eye_cords) {
    double r = sqrt(pow(eye_cords.x, 2)+pow(eye_cords.y, 2)+pow(eye_cords.z, 2));
    double temp = eye_cords.z/r;

    double theta = atan2(eye_cords.y, eye_cords.x);
    double phi = acos(temp);
    Matrix eyeMatrix;
    eyeMatrix(1,1) = -sin(theta);
    eyeMatrix(1,2) = -cos(theta)*cos(phi);
    eyeMatrix(1,3) = cos(theta)*sin(phi);
    eyeMatrix(2, 1) = cos(theta);
    eyeMatrix(2, 2) = -sin(theta)*cos(phi);
    eyeMatrix(2, 3) = sin(theta)*sin(phi);
    eyeMatrix(3,2) = sin(phi);
    eyeMatrix(3,3) = cos(phi);

    direction = direction*eyeMatrix;

    eyeMatrix(4,3) = -r;

    original_location = location;

    location = location*eyeMatrix;

}

void Light::EyePerspectifTransform(const Vector3D &eye_cords, const Vector3D &view_dir) {
    Vector3D dir = view_dir*-1;
    double r = sqrt(pow(eye_cords.x, 2)+pow(eye_cords.y, 2)+pow(eye_cords.z, 2));
    double r_dir = sqrt(pow(dir.x, 2)+pow(dir.y, 2)+pow(dir.z, 2));
    double temp = dir.z/r_dir;

    double theta = atan2(dir.y, dir.x);
    double phi = acos(temp);
    Matrix eyeMatrix;
    eyeMatrix(1,1) = -sin(theta);
    eyeMatrix(1,2) = -cos(theta)*cos(phi);
    eyeMatrix(1,3) = cos(theta)*sin(phi);
    eyeMatrix(2, 1) = cos(theta);
    eyeMatrix(2, 2) = -sin(theta)*cos(phi);
    eyeMatrix(2, 3) = sin(theta)*sin(phi);
    eyeMatrix(3,2) = sin(phi);
    eyeMatrix(3,3) = cos(phi);

    direction = direction*eyeMatrix;

    eyeMatrix(4,3) = -r;

    original_location = location;
    location = location*eyeMatrix;
}

void Light::shadow_transform(const vector<Figure*>& figures) {
    for (auto f: figures){
        f->EyePerspectifTransform(location);
        f->DoProjection(1);

        EyePerspective* eye_position = new EyePerspective{location};
        f->setEye(eye_position);
    }

    MakeShadowBuffer(figures);


    for (auto f: figures){
        f->EyeUnPerspectifTransform(location);
    }


}

void Light::MakeShadowBuffer(const vector<Figure *> &figures) {
    tuple<double, pair<double, double>, pair<double, double>> relocate_data = tool2D::get_scale_factor_all(figures, shadow_size, 0.98);

    d = get<0>(relocate_data);

    pair<double, double> deviation = get<1>(relocate_data);

    dx = deviation.first;
    dy = deviation.second;

    pair<double, double> image_size = get<2>(relocate_data);
    for (auto figure: figures){
        figure->UndoProjection(1);
    }

    mask = new ShadowMask((unsigned int)  image_size.first, (unsigned int)  image_size.second);


    for (auto& figure: figures){
        tool2D::determineFaceData(figure, d, false);
        tool2D::doFigureProjection(figure, d, deviation);
    }



    for (auto figure: figures){
        int face_counter = 0;
        for (auto face: figure->faces){
            Vector3D A = figure->points[face.points[0]];
            Vector3D B = figure->points[face.points[1]];
            Vector3D C = figure->points[face.points[2]];
            vector<Vector3D> temp_fases = {A, B, C};
            double xG = (A.x+B.x+C.x)/3;
            double yG = (A.y+B.y+C.y)/3;
            double diff_zG = 1/(3*A.z)+1/(3*B.z)+1/(3*C.z);

            double dzdx = face.dzdx;
            double dzdy = face.dzdy;

            double y_min = min(A.y, B.y);
            y_min = min(C.y, y_min);

            double y_max = max(A.y, B.y);
            y_max = max(C.y, y_max);
            for (int y_i= lround(y_min+0.5); y_i <= lround(y_max-0.5); y_i++){
                vector<double> valid_x_i;
                for (int i = 0; i<3; i++){
                    double x_1 = temp_fases[i%3].x;
                    double x_2 = temp_fases[(i+1)%3].x;
                    double y_1 = temp_fases[i%3].y;
                    double y_2 = temp_fases[(i+1)%3].y;
                    if ((y_i-y_1)*(y_i-y_2) <= 0 && y_1 != y_2){
                        double x_i = x_2 + (x_1-x_2)*(y_i-y_2)/(y_1-y_2);
                        valid_x_i.push_back(x_i);
                    }
                }
                if (valid_x_i.empty()){
                    continue;
                }

                int x_l = lround(min(valid_x_i[0], valid_x_i[1])+0.5);
                int  x_r = lround(max(valid_x_i[0], valid_x_i[1])-0.5);
                for (int x_i = x_l; x_i<=x_r; x_i++){
                    double diff_zi = diff_zG+(x_i-xG)*dzdx+(y_i-yG)*dzdy;

                    if (diff_zi < (*mask)[x_i][y_i]){

                        (*mask)[x_i][y_i] = diff_zi;
                    }

                }
            }

            face_counter += 1;
        }
    }

    for (auto figure: figures){
        for (auto &p: figure->points){
            p.x -= dx;
            p.y -= dy;


        }

        figure->UndoProjection(d);
    }

}

bool Light::same(const Vector3D &normal_point) {
    double r = sqrt(pow(original_location.x, 2)+pow(original_location.y, 2)+pow(original_location.z, 2));
    double temp = original_location.z/r;

    double theta = atan2(original_location.y, original_location.x);
    double phi = acos(temp);
    Matrix eyeMatrix;
    eyeMatrix(1,1) = -sin(theta);
    eyeMatrix(1,2) = -cos(theta)*cos(phi);
    eyeMatrix(1,3) = cos(theta)*sin(phi);
    eyeMatrix(2, 1) = cos(theta);
    eyeMatrix(2, 2) = -sin(theta)*cos(phi);
    eyeMatrix(2, 3) = sin(theta)*sin(phi);
    eyeMatrix(3,2) = sin(phi);
    eyeMatrix(3,3) = cos(phi);
    eyeMatrix(4,3) = -r;

    Vector3D point_L = normal_point*eyeMatrix;
    Vector3D point_D = Vector3D::point(point_L.x*d/(-point_L.z)+dx, point_L.y*d/(-point_L.z)+dy, point_L.z);

    double alpha_x = point_D.x - floor(point_D.x);
    double alpha_y = point_D.y - floor(point_D.y);

    double diff_A = (*mask)[floor(point_D.x)][ceil(point_D.y)];
    double diff_B = (*mask)[ceil(point_D.x)][ceil(point_D.y)];
    double diff_C = (*mask)[floor(point_D.x)][floor(point_D.y)];
    double diff_D = (*mask)[ceil(point_D.x)][floor(point_D.y)];

    double diff_E = (1-alpha_x)*diff_A + alpha_x*diff_B;
    double diff_F = (1-alpha_x)*diff_C + alpha_x*diff_D;

    double z_val = alpha_y*diff_E+(1-alpha_y)*diff_F;


    if(!isfinite(diff_A) || !isfinite(diff_B) || !isfinite(diff_C) || !isfinite(diff_D)){
        return true;

    }


    if ((1/point_D.z) < z_val+0.0001*11000/d){
        return true;
    }

    return false;

}

