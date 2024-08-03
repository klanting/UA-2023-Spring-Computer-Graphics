//
// Created by tibov on 14/05/23.
//

#include "CubeMap.h"
#include <limits>
#include <cmath>
vector<Color> CubeMap::getColor(const Vector3D &point, const Vector3D &normaal) {
    double best_t = numeric_limits<double>::infinity();
    CubeMapFace map_face;
    for(auto face: cube_map_faces){
        double t = face.calculateT(point, normaal);
        if (t < best_t && t >= -0.01){
            best_t = t;
            map_face = face;
        }

    }
    Vector3D check_p;
    check_p.x = point.x+best_t*normaal.x;
    check_p.y = point.y+best_t*normaal.y;
    check_p.z = point.z+best_t*normaal.z;

    pair<double, double> uv = map_face.getUV(check_p);
    double u = uv.first;
    double v = uv.second;

    double width = ambient_img.get_width();
    double height = ambient_img.get_height();


    while(u > 1){
        u -= 1;
    }

    while(v > 1){
        v -= 1;
    }

    while(u < 0){
        u += 1;
    }

    while(v < 0){
        v += 1;
    }

    //cout << u << " " << v << endl;

    int x = u*width;
    int y = v*height;

    Color ambient(ambient_img(x, y).red/255.0, ambient_img(x, y).green/255.0, ambient_img(x, y).blue/255.0);

    return {ambient};
}

CubeMap::CubeMap(double max) {
    vector<Vector3D> points;
    points.push_back(Vector3D::point(1, -1, -1));
    points.push_back(Vector3D::point(-1, 1, -1));
    points.push_back(Vector3D::point(1, 1, 1));
    points.push_back(Vector3D::point(-1, -1, 1));
    points.push_back(Vector3D::point(1, 1, -1));
    points.push_back(Vector3D::point(-1, -1, -1));
    points.push_back(Vector3D::point(1, -1, 1));
    points.push_back(Vector3D::point(-1, 1, 1));

    vector<vector<int>> faces;
    faces.push_back({0, 4, 2, 6});
    faces.push_back({4, 1, 7, 2});
    faces.push_back({1, 5, 3, 7});
    faces.push_back({5, 0, 6, 3});
    faces.push_back({6, 2, 7, 3});
    faces.push_back({0, 5, 1, 4});

    for (auto f: faces){
        CubeMapFace cf;
        for (int i =0; i<f.size(); i++){
            int index = f[i];
            double u, v;
            if (i == 0){
                u = 0;
                v = 0;
            }else if (i == 1){
                u = 0;
                v = 1;
            }else if (i == 2){
                u = 1;
                v = 1;
            }else if (i == 3){
                u = 1;
                v = 0;
            }
            CubeMapVertex cv(points[index]*max, points[index]*max, Vector3D::point(u, v, 0));
            cf.determine_axis();
            cf.vertexes.push_back(cv);
        }
        cube_map_faces.push_back(cf);
    }

}


