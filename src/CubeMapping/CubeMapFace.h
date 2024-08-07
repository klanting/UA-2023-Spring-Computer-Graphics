//
// Created by tibov on 14/05/23.
//

#ifndef ENGINE_CUBEMAPFACE_H
#define ENGINE_CUBEMAPFACE_H
#include "CubeMapVertex.h"
#include <vector>
#include "CubeMapVertex.h"
#include "../2DProjection/easy_image.h"
class CubeMapFace {
public:
    vector<CubeMapVertex> vertexes;
    void determine_axis();
    int axis_index = -1;
    double calculateT(const Vector3D& point, const Vector3D& normaal);
    pair<double, double> getUV(const Vector3D& point);
    img::EasyImage ambient_img;

private:
};


#endif //ENGINE_CUBEMAPFACE_H
