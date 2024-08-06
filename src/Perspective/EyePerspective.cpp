//
// Created by tibov on 06/08/24.
//

#include "EyePerspective.h"

EyePerspective::EyePerspective(const Vector3D &eye): eye{eye} {
    r = sqrt(pow(eye.x, 2)+pow(eye.y, 2)+pow(eye.z, 2));
    double temp = eye.z/r;

    double theta = atan2(eye.y, eye.x);
    double phi = acos(temp);

    eye_matrix_point(1, 1) = -sin(theta);
    eye_matrix_point(1, 2) = -cos(theta) * cos(phi);
    eye_matrix_point(1, 3) = cos(theta) * sin(phi);
    eye_matrix_point(2, 1) = cos(theta);
    eye_matrix_point(2, 2) = -sin(theta) * cos(phi);
    eye_matrix_point(2, 3) = sin(theta) * sin(phi);
    eye_matrix_point(3, 2) = sin(phi);
    eye_matrix_point(3, 3) = cos(phi);

    eye_matrix_point_inverse = eye_matrix_point;
    eye_matrix_pointless_inverse = eye_matrix_point;
    eye_matrix_point_inverse(4, 3) = -r;

    eye_matrix_point.inv();
    eye_matrix_pointless_inverse.inv();

}

double EyePerspective::getR() const {
    return r;
}

const Vector3D &EyePerspective::getEye() const {
    return eye;
}

const Matrix &EyePerspective::getEyeMatrixPointInverse() const {
    return eye_matrix_point_inverse;
}

const Matrix &EyePerspective::getEyeMatrixPointlessInverse() const {
    return eye_matrix_pointless_inverse;
}

const Matrix &EyePerspective::getEyeMatrixPoint() const {
    return eye_matrix_point;
}
