//
// Created by tibov on 26/04/23.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H
#include "Color.h"
#include "vector3d.h"
#include "ShadowMask.h"

class Figure;
class Light {
public:
    Light();
    Color ambient = Color(0, 0, 0);
    Color difuus = Color(0, 0, 0);
    Color spiegelend = Color(0, 0, 0);
    Color difuus_infinity = Color(0, 0, 0);
    Vector3D direction = Vector3D::point(0, 0, 0);
    Vector3D location = Vector3D::point(0, 0, 0);
    Vector3D original_location = Vector3D::point(0, 0, 0);
    double spot_angle = 0;
    bool inf = false;
    int shadow_size;
    bool shadow = false;

    double d;
    double dx;
    double dy;
    bool impact = true;

    ShadowMask* mask;

    void EyePerspectifTransform(const Vector3D &eye_cords);
    void EyePerspectifTransform(const Vector3D &eye_cords, const Vector3D& view_dir);
    void shadow_transform(const vector<Figure*>& figures);
    bool same(const Vector3D& normal_point);
private:
    void MakeShadowBuffer(const vector<Figure*>& figures);

};


#endif //ENGINE_LIGHT_H
