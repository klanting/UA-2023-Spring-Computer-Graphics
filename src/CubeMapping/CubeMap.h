//
// Created by tibov on 14/05/23.
//

#ifndef ENGINE_CUBEMAP_H
#define ENGINE_CUBEMAP_H
#include "../../libraries/vector3d.h"
#include <vector>
#include "CubeMapFace.h"
#include "../Figure/Color.h"
#include "../../libraries/easy_image.h"
using namespace std;
class CubeMap {
public:
    vector<CubeMapFace> cube_map_faces;
    vector<Color> getColor(const Vector3D& point, const Vector3D& normaal);
    img::EasyImage ambient_img;
    img::EasyImage difuus_img;
    CubeMap(double max);
private:

};


#endif //ENGINE_CUBEMAP_H
