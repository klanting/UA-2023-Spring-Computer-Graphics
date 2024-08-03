//
// Created by tibov on 01/04/23.
//

#ifndef ENGINE_CLIPPING_H
#define ENGINE_CLIPPING_H
#include "Figure.h"
#include <vector>

namespace Clipping {
    void clipNear(Figure* figure, double dNear);
    void clipFar(Figure* figure, double dFar);
    void clipRight(Figure* figure, double dNear, double dRight);
    void clipLeft(Figure* figure, double dNear, double dLeft);
    void clipTop(Figure* figure, double dNear, double dTop);
    void clipBottom(Figure* figure, double dNear, double dBottom);
    pair<vector<Vector3D>, vector<Vector3D>> CheckSide(Figure* figure, const Face &face, double compare_value, const string& type, double dNear);
    double toValue(Vector3D& point, const string& type, double dNear);
    double CalculateP(double dval, const Vector3D& p1, const Vector3D& p2, const string& type, double dNear);
    void Cut(const pair<vector<Vector3D>, vector<Vector3D>>& value_pair, const string& type, double dval, double dNear, vector<Face> &new_faces, vector<Vector3D> &new_points);
};


#endif //ENGINE_CLIPPING_H
