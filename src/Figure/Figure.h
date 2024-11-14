//
// Created by tibov on 10/03/23.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <vector>
#include "../../libraries/vector3d.h"
#include "Face.h"
#include "Color.h"
#include "../../libraries/easy_image.h"
#include "Line2D.h"
#include "list"
#include "../Lighting/Light.h"
#include "../Lighting/LightTools.h"
#include "../Textures/TextureMap.h"
#include "../CubeMapping/CubeMap.h"
#include "../Textures/TextureCoord.h"
#include "../Perspective/EyePerspective.h"
using namespace std;


struct Reflections{
    Color ambient_intensity = Color(0, 0, 0);
    Color diffuse_color = Color(0, 0, 0);
    Color spectral_color = Color(0, 0, 0);
    double reflection_index = 1;

};

class Figure {
public:
    Figure(const vector<Vector3D> &points, const vector<vector<int>> &lines, const Color &c);
    Figure(const vector<Vector3D> &points, const vector<vector<int>> &lines, const vector<vector<Vector3D>> &uv, const vector<vector<Vector3D>> &v_normaal, const Color &c);


    vector<Vector3D> points;
    vector<Face> faces;

    Reflections reflections;

    Color ambient_color = Color(0, 0, 0);

    void EyePerspectiveTransform(const Vector3D &eye_cords);
    void EyeTransformFace();
    void EyeUnPerspectiveTransform(const Vector3D &eye_cords);
    void EyePerspectiveTransform(const Vector3D &eye_cords, const Vector3D& view_dir);
    void DoProjection(double d);
    void RotateX(double angle_degree);
    void RotateY(double angle_degree);
    void RotateZ(double angle_degree);
    void Scalar(double scale);
    void FullRotScaleMove(double angle_x, double angle_y, double angle_z, double scale, const Vector3D &center);
    void translation(const Vector3D &center);
    void Triangulate();
    void UndoProjection(double d);
    void DiffuseLightInf(const vector<Light*>& lights);
    Vector3D getOriginal(const Vector3D& point, bool has_point);
    TextureMap* texture = nullptr;
    bool useTexture = false;
    bool cube_mapping = false;
    CubeMap* cube_map = nullptr;
    bool texture_coord = false;
    TextureCoord* texture_co;

    bool fix_round = false;

    void setEye(EyePerspective* eye_perspective);

private:
    EyePerspective* eye_perspective;

};


#endif //ENGINE_FIGURE_H
