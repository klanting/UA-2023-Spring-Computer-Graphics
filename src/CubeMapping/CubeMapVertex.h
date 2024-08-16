//
// Created by tibov on 14/05/23.
//

#ifndef ENGINE_CUBEMAPVERTEX_H
#define ENGINE_CUBEMAPVERTEX_H
#include "../../libraries/vector3d.h"
using namespace std;
class CubeMapVertex {
public:
    CubeMapVertex(const Vector3D &pos, const Vector3D &normaal, const Vector3D &uv);
    CubeMapVertex(const Vector3D &pos);
public:

    Vector3D pos;
    Vector3D normaal;
    Vector3D uv;
};


#endif //ENGINE_CUBEMAPVERTEX_H
