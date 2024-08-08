//
// Created by tibov on 26/04/23.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H
#include "../Figure/Color.h"
#include "../Figure/vector3d.h"
#include "ShadowMask.h"

struct LightColors{
    Color ambient = Color(0, 0, 0);
    Color diffuse = Color(0, 0, 0);
    Color specular = Color(0, 0, 0);
};

class Figure;
class Light {
public:
    Light();
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

    [[nodiscard]] Color getAmbient() const;
    [[nodiscard]] Color getDiffuse() const;
    [[nodiscard]] Color getSpectral() const;

    void setLightColors(const LightColors &lightColors);

private:
    LightColors light_colors;

    void MakeShadowBuffer(const vector<Figure*>& figures);

};


#endif //ENGINE_LIGHT_H
