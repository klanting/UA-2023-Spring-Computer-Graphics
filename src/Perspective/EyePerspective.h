//
// Created by tibov on 06/08/24.
//

#ifndef ENGINE_EYEPERSPECTIVE_H
#define ENGINE_EYEPERSPECTIVE_H

#include <cmath>
#include "../../libraries/vector3d.h"

class EyePerspective {
public:
    explicit EyePerspective(const Vector3D& eye);

    double getR() const;

    const Vector3D &getEye() const;

    const Matrix &getEyeMatrixPointInverse() const;

    const Matrix &getEyeMatrixPointlessInverse() const;

    const Matrix &getEyeMatrixPointLess() const;
    const Matrix &getEyeMatrixPoint() const;

private:
    Vector3D eye;
    Matrix eye_matrix_point_inverse;
    Matrix eye_matrix_pointless;
    Matrix eye_matrix_point;
    Matrix eye_matrix_pointless_inverse;
    double r;
};


#endif //ENGINE_EYEPERSPECTIVE_H
