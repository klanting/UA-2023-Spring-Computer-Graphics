//
// Created by tibov on 14/05/23.
//

#include "CubeMapFace.h"
#include "cmath"
void CubeMapFace::determine_axis() {
    bool arr[3] = {true, true, true};

    for (auto v: vertexes){
        if (v.pos.x != vertexes[0].pos.x){
            arr[0] = false;
        }

        if (v.pos.y != vertexes[0].pos.y){
            arr[1] = false;
        }

        if (v.pos.z != vertexes[0].pos.z){
            arr[2] = false;
        }
    }

    for (int i=0; i<3; i++){
        if (arr[i]){
            axis_index = i;
        }
    }
}

double CubeMapFace::calculateT(const Vector3D &point, const Vector3D &normaal) {
    double p;
    double n;
    double a;
    if (axis_index == 0){
        p = point.x;
        n = normaal.x;
        a = vertexes[0].pos.x;
    }else if (axis_index == 1){
        p = point.y;
        n = normaal.y;
        a = vertexes[0].pos.y;
    }else{
        p = point.z;
        n = normaal.z;
        a = vertexes[0].pos.z;
    }
    double t = (a-p)/n;
    return t;
}

pair<double, double> CubeMapFace::getUV(const Vector3D &point) {
    CubeMapVertex a = vertexes[0];
    CubeMapVertex  b = vertexes[1];
    CubeMapVertex  c = vertexes[2];
    CubeMapVertex  d = vertexes[3];

    Vector3D d1 = b.normaal-a.normaal;
    Vector3D ds1 = point-a.normaal;

    double dis_a = (d1.x*ds1.x+d1.y*ds1.y+d1.z*ds1.z)/pow(d1.length(), 2);

    d1 = d.normaal-a.normaal;
    ds1 = point-a.normaal;
    double dis_e = (d1.x*ds1.x+d1.y*ds1.y+d1.z*ds1.z)/pow(d1.length(), 2);

    Vector3D e = b.uv*dis_a+a.uv*(1-dis_a);
    Vector3D f = c.uv*dis_a+d.uv*(1-dis_a);

    Vector3D r = f*dis_e+e*(1-dis_e);


    return make_pair(r.x, r.y);
}
