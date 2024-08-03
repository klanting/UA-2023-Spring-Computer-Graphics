//
// Created by tibov on 06/05/23.
//

#ifndef ENGINE_TEXTUREMAP_H
#define ENGINE_TEXTUREMAP_H
#include "iostream"
#include "fstream"
#include "vector"
#include "vector3d.h"
#include "Color.h"
using namespace std;
class TextureMap {
public:
    TextureMap(const string &path, const Vector3D& P, const Vector3D& A, const Vector3D& B);
    vector<vector<vector<unsigned int>> > matrix;
    pair<double, double> get_uv(const Vector3D& original_point);
    Color getColor(const Vector3D& original_point);
    Vector3D p = Vector3D::point(0, 0, 0);
    Vector3D a = Vector3D::vector(0, 0, 0);
    Vector3D b = Vector3D::vector(0, 0, 0);
private:
    unsigned int get_byte();
    unsigned int concatinate(const vector<unsigned int>& b);
    void read_header();
    void read_data();
    ifstream stream;

    unsigned int offset;
    unsigned width;
    unsigned height;
    unsigned int bits;
    unsigned int row_size;
    unsigned int change;


    Matrix UVmatrix;


};


#endif //ENGINE_TEXTUREMAP_H
