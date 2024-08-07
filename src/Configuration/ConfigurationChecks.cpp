//
// Created by tibov on 06/08/24.
//

#include "ConfigurationChecks.h"

void ConfigurationChecks::checkTextureMapping(Figure *f, const ini::FigureReader &sr) {
    bool texture_mapping = sr.getBool("textureMapping");

    if (texture_mapping){
        string path = sr.getString("texturePath");


        ini::DoubleTuple P = sr.getDoubleTuple("textureP");
        ini::DoubleTuple A = sr.getDoubleTuple("textureA");
        ini::DoubleTuple B = sr.getDoubleTuple("textureB");

        Vector3D Pv = Vector3D::point(P[0], P[1], P[2]);
        Vector3D Pa = Vector3D::vector(A[0], A[1], A[2]);
        Vector3D Pb = Vector3D::vector(B[0], B[1], B[2]);


        TextureMap* t = new TextureMap(path, Pv, Pa, Pb);
        f->useTexture = true;
        f->texture = t;
    }
}
