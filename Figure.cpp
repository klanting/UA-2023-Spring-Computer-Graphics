//
// Created by tibov on 10/03/23.
//

#include "Figure.h"
#include <cmath>
#include "Point2D.h"
#include <limits>

Figure::Figure(const vector<Vector3D> &points, const vector<vector<int>> &lines, const Color &c) : points(points), ambient_color(c){
    for (auto line: lines){
        faces.push_back(Face(line));
    }
}

Figure::Figure(const vector<Vector3D> &points, const vector<vector<int>> &lines, const vector<vector<Vector3D>> &uv, const vector<vector<Vector3D>> &v_normaal,
               const Color &c) : points(points), ambient_color(c) {
    for (auto line: lines){
        faces.push_back(Face(line));
    }

    for (int i=0; i<faces.size(); i++){
        auto& f = faces[i];
        for (int j=0; j < uv[i].size(); j++){
            f.uv_map[lines[i][j]] = uv[i][j];
            f.normaal_map[lines[i][j]] = v_normaal[i][j];
        }

    }
}


void Figure::EyePerspectifTransform(const Vector3D &eye_cords) {
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

    eyeMatrix(4,3) = -r;


    for (auto &point: points){
        point = point*eyeMatrix;


    }

}

void Figure::EyePerspectifTransform(const Vector3D &eye_cords, const Vector3D& view_dir) {
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

    /*
    if (useTexture){
        texture->a = texture->a*eyeMatrix;
        texture->b = texture->b*eyeMatrix;
    }*/

    eyeMatrix(4,3) = -r;


    for (auto &point: points){
        point = point*eyeMatrix;
    }

    /*
    if (useTexture){
        texture->p = texture->p*eyeMatrix;
    }*/
}


void Figure::DoProjection(double d) {

    for (auto &point: points){
        double x_acc = d*point.x/(-point.z);
        double y_acc = d*point.y/(-point.z);
        point.x = x_acc;
        point.y = y_acc;
    }


}


void Figure::RotateX(double angle_degree) {
    double rad = -1*M_PI/180*angle_degree;
    Matrix RotateMatrix;
    RotateMatrix(2, 2) = cos(rad);
    RotateMatrix(2, 3) = -sin(rad);
    RotateMatrix(3, 3) = cos(rad);
    RotateMatrix(3, 2) = sin(rad);

    for (auto & point :points){
        point = point*RotateMatrix;
    }
}

void Figure::RotateY(double angle_degree) {
    double rad = -1*M_PI/180*angle_degree;
    Matrix RotateMatrix;
    RotateMatrix(1, 1) = cos(rad);
    RotateMatrix(1, 3) = sin(rad);
    RotateMatrix(3, 3) = cos(rad);
    RotateMatrix(3, 1) = -sin(rad);

    for (auto & point :points){
        point = point*RotateMatrix;
    }
}

void Figure::RotateZ(double angle_degree) {
    double rad = -1*M_PI/180*angle_degree;
    Matrix RotateMatrix;
    RotateMatrix(1, 1) = cos(rad);
    RotateMatrix(1, 2) = -sin(rad);
    RotateMatrix(2, 2) = cos(rad);
    RotateMatrix(2, 1) = sin(rad);
    for (auto & point :points){
        point = point*RotateMatrix;
    }
}

void Figure::Scalar(double scale) {
    Matrix ScaleMatrix;
    ScaleMatrix(1, 1) = scale;
    ScaleMatrix(2, 2) = scale;
    ScaleMatrix(3, 3) = scale;

    for (auto & point :points){
        point = point*ScaleMatrix;
    }
}

void Figure::FullRotScaleMove(double angle_x, double angle_y, double angle_z, double scale, const Vector3D &center) {
    double rad_x = -1*M_PI / 180 * angle_x;
    Matrix RotateX;
    RotateX(2, 2) = cos(rad_x);
    RotateX(2, 3) = -sin(rad_x);
    RotateX(3, 3) = cos(rad_x);
    RotateX(3, 2) = sin(rad_x);

    double rad_y = -1*M_PI / 180 * angle_y;
    Matrix RotateY;
    RotateY(1, 1) = cos(rad_y);
    RotateY(1, 3) = sin(rad_y);
    RotateY(3, 3) = cos(rad_y);
    RotateY(3, 1) = -sin(rad_y);

    double rad_z = -1*M_PI/180*angle_z;
    Matrix RotateZ;
    RotateZ(1, 1) = cos(rad_z);
    RotateZ(1, 2) = -sin(rad_z);
    RotateZ(2, 2) = cos(rad_z);
    RotateZ(2, 1) = sin(rad_z);

    Matrix ScaleMatrix;
    ScaleMatrix(1, 1) = scale;
    ScaleMatrix(2, 2) = scale;
    ScaleMatrix(3, 3) = scale;

    Matrix TranslatieMatrix;
    TranslatieMatrix(4, 1) = center.x;
    TranslatieMatrix(4, 2) = center.y;
    TranslatieMatrix(4, 3) = center.z;

    Matrix result = RotateX*RotateY*RotateZ*ScaleMatrix*TranslatieMatrix;
    for (auto & point :points){
        point = point*result;
    }



}

void Figure::Translatie(const Vector3D &center) {
    Matrix TranslatieMatrix;
    TranslatieMatrix(4, 1) = center.x;
    TranslatieMatrix(4, 2) = center.y;
    TranslatieMatrix(4, 3) = center.z;

    for (auto & point :points){
        point = point*TranslatieMatrix;
    }
}

void Figure::Triangulate() {
    vector<Face> new_faces;
    for (Face &face: faces){
        if (face.points.size() <= 3){
            new_faces.push_back(face);
            continue;
        }

        for (int i = 1; i<face.points.size()-1; i++){
            Face f({face.points[0], face.points[i], face.points[i+1]});
            f.uv_map = face.uv_map;
            f.normaal_map = face.normaal_map;
            new_faces.push_back(f);
        }
    }

    faces = new_faces;
}

vector<double> Figure::RangesProjection(double d) {
    double min_x = numeric_limits<double>::max();
    double max_x = numeric_limits<double>::min();
    double min_y = numeric_limits<double>::max();
    double max_y = numeric_limits<double>::min();

    for (auto &point: points){
        double x_acc = d*point.x/(-point.z);
        double y_acc = d*point.y/(-point.z);
        if (x_acc < min_x){
            min_x = x_acc;
        }

        if (x_acc> max_x){
            max_x = x_acc;
        }

        if (y_acc < min_y){
            min_y = y_acc;
        }

        if (y_acc > max_y){
            max_y = y_acc;
        }
    }

    vector<double> result = {min_x, max_x, min_y, max_y};
    return result;
}

void Figure::UndoProjection(double d) {

    for (auto &point: points){

        double x_acc = point.x*(-point.z)/d;
        double y_acc = point.y*(-point.z)/d;

        point.x = x_acc;
        point.y = y_acc;
    }


}

void Figure::DifuusLichtInf(const vector<Light *> &lights) {
    for (auto& face: faces){
        Vector3D normaal_copy = face.normaal;
        normaal_copy.normalise();

        vector<double> angles;
        for (auto l: lights){
            l->direction.normalise();
            double angle = l->direction.x*-1*normaal_copy.x+l->direction.y*-1*normaal_copy.y+l->direction.z*-1*normaal_copy.z;
            angles.push_back(angle);

        }
        Color result = LightTools::SumDifuusInf(lights, angles);
        face.difuus_inf = Color(result.red*difuus_color.red, result.green*difuus_color.green, result.blue*difuus_color.blue);

    }
}

void Figure::EyeUnPerspectifTransform(const Vector3D &eye_cords) {
    double r = sqrt(pow(eye_cords.x, 2) + pow(eye_cords.y, 2) + pow(eye_cords.z, 2));
    double temp = eye_cords.z / r;

    double theta = atan2(eye_cords.y, eye_cords.x);
    double phi = acos(temp);

    Matrix eyeMatrix;
    eyeMatrix(1, 1) = -sin(theta);
    eyeMatrix(1, 2) = -cos(theta) * cos(phi);
    eyeMatrix(1, 3) = cos(theta) * sin(phi);
    eyeMatrix(2, 1) = cos(theta);
    eyeMatrix(2, 2) = -sin(theta) * cos(phi);
    eyeMatrix(2, 3) = sin(theta) * sin(phi);
    eyeMatrix(3, 2) = sin(phi);
    eyeMatrix(3, 3) = cos(phi);
    eyeMatrix(4, 3) = -r;

    eyeMatrix.inv();

    for (auto &point: points) {
        point = point * eyeMatrix;


    }
}

Vector3D Figure::getOriginal(const Vector3D &point, bool has_point) {
    double r = sqrt(pow(eye.x, 2)+pow(eye.y, 2)+pow(eye.z, 2));
    double temp = eye.z/r;
    if (r == 0){
        return Vector3D::point(0, 0, 0);
    }

    double theta = atan2(eye.y, eye.x);
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
    if (has_point){
        eyeMatrix(4,3) = -r;
    }


    eyeMatrix.inv();


    return point*eyeMatrix;
}

void Figure::EyeTransformFace(const Vector3D &eye_cords) {
    double r = sqrt(pow(eye.x, 2)+pow(eye.y, 2)+pow(eye.z, 2));
    double temp = eye.z/r;

    double theta = atan2(eye.y, eye.x);
    double phi = acos(temp);

    Matrix eyeMatrix;
    eyeMatrix(1, 1) = -sin(theta);
    eyeMatrix(1, 2) = -cos(theta) * cos(phi);
    eyeMatrix(1, 3) = cos(theta) * sin(phi);
    eyeMatrix(2, 1) = cos(theta);
    eyeMatrix(2, 2) = -sin(theta) * cos(phi);
    eyeMatrix(2, 3) = sin(theta) * sin(phi);
    eyeMatrix(3, 2) = sin(phi);
    eyeMatrix(3, 3) = cos(phi);

    for(auto& face: faces){
        for(auto& v: face.normaal_map){
            v.second = v.second*eyeMatrix;
        }

    }
}





