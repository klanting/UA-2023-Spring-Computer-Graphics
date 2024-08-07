//
// Created by tibov on 10/03/23.
//

#include "Face.h"


Face::Face(const vector<int> &points): points(points) {

}

pair<Vector3D, Vector3D> Face::getUV(const Vector3D &eye_point, const Vector3D& A, const Vector3D& B, const Vector3D& C) {
    Vector3D a = B - A;
    Vector3D b = C - A;

    Vector3D c = Vector3D::cross(a, b);

    Matrix UVmatrix;

    UVmatrix(1, 1) = a.x;
    UVmatrix(1, 2) = a.y;
    UVmatrix(2, 1) = b.x;
    UVmatrix(2, 2) = b.y;
    UVmatrix.inv();
    Vector3D temp = eye_point - A;

    Vector3D result = temp * UVmatrix;

    Vector3D AU = uv_map[points[0]];
    Vector3D BU = uv_map[points[1]];
    Vector3D CU = uv_map[points[2]];
    Vector3D result_uv = (1-result.x-result.y)*AU+(result.x)*BU+(result.y)*CU;

    Vector3D An = normaal_map[points[0]];
    Vector3D Bn = normaal_map[points[1]];
    Vector3D Cn = normaal_map[points[2]];

    Vector3D result_n = (1-result.x-result.y)*An+(result.x)*Bn+(result.y)*Cn;

    return make_pair(result_uv, result_n);
}