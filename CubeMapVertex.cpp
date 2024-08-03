//
// Created by tibov on 14/05/23.
//

#include "CubeMapVertex.h"

CubeMapVertex::CubeMapVertex(const Vector3D &pos, const Vector3D &normaal, const Vector3D &uv) : pos(pos),
                                                                                                 normaal(normaal),
                                                                                                 uv(uv) {

}

CubeMapVertex::CubeMapVertex(const Vector3D &pos): pos(pos) {

}
