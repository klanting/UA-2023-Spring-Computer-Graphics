//
// Created by tibov on 10/03/23.
//

#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H
#include <vector>
#include "../../libraries/vector3d.h"
#include "Color.h"
#include <map>
using namespace std;

class Face {

public:
    explicit Face(const vector<int> &points);

    pair<Vector3D, Vector3D> getUV(const Vector3D& eye_point, const Vector3D& A, const Vector3D& B, const Vector3D& C);
    vector<int> points;
    double dzdx;
    double dzdy;
    Color difuus_inf = Color(0, 0, 0);
    Vector3D normaal;

    map<int, Vector3D> uv_map;
    map<int, Vector3D> normaal_map;



};


#endif //ENGINE_FACE_H
