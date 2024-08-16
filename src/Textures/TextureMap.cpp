//
// Created by tibov on 06/05/23.
//

#include "TextureMap.h"
#include "cmath"
#include <algorithm>
#include "../../libraries/easy_image.h"
unsigned int TextureMap::get_byte() {
    char data = '\000';
    stream.get(data);
    int b = int(data);
    while (b < 0){
        b += 256;
    }
    return b;

}

unsigned int TextureMap::concatinate(const vector<unsigned int>& b) {
    unsigned int out = 0;
    for (int i=0; i<b.size();i++){
        unsigned int v = b[i];
        out = out + (v << (8*i));
    }
    return out;
}

TextureMap::TextureMap(const string &path, const Vector3D& P, const Vector3D& A, const Vector3D& B):p(P), a(A), b(B) {

    stream.open(path);
    read_header();
    read_data();
    stream.close();

    Vector3D c = Vector3D::cross(a, b);
    UVmatrix(1, 1) = a.x;
    UVmatrix(1, 2) = a.y;
    UVmatrix(1, 3) = a.z;
    UVmatrix(2, 1) = b.x;
    UVmatrix(2, 2) = b.y;
    UVmatrix(2, 3) = b.z;
    UVmatrix(3, 1) = c.x/2;
    UVmatrix(3, 2) = c.y/2;
    UVmatrix(3, 3) = c.z/2;
    UVmatrix.inv();
}

void TextureMap::read_header() {
    vector<unsigned int> temp;
    for (int i =0; i<10; i++){
        get_byte();
    }


    for (int i =0; i<4; i++){
        temp.push_back(get_byte());
    }

    offset = concatinate(temp);
    temp.clear();

    for (int i =0; i<4; i++){
        get_byte();
    }

    for (int i =0; i<4; i++){
        temp.push_back(get_byte());
    }

    width = concatinate(temp);
    temp.clear();

    for (int i =0; i<4; i++){
        temp.push_back(get_byte());
    }

    height = concatinate(temp);
    temp.clear();

    for (int i =0; i<2; i++){
        get_byte();
    }

    for (int i =0; i<4; i++){
        temp.push_back(get_byte());
    }

    bits = concatinate(temp);
    temp.clear();

    for (int i =0; i<offset-34; i++){
        get_byte();
    }

    row_size = ceil((double) bits*(double) width/32.0)*4.0;
    change = lround(((double)row_size/(double)bits*8.0-(double)width)*(double)bits/8.0);
}

void TextureMap::read_data() {
    for (unsigned int i=0; i<height; i++){
        vector<vector<unsigned int>> row;
        for (unsigned int j=0; j<width; j++){
            unsigned int g = get_byte();
            unsigned int r = get_byte();
            unsigned int b = get_byte();

            vector<unsigned int> rgb = {r, g, b};
            row.push_back(rgb);
        }

        for (int i =0; i<change; i++){
            get_byte();
        }


        matrix.push_back(row);
    }


}

pair<double, double> TextureMap::get_uv(const Vector3D& original_point) {
    Vector3D temp = original_point-p;

    Vector3D result = temp*UVmatrix;


    return make_pair(result.x, result.y);
}

Color TextureMap::getColor(const Vector3D &original_point) {
    pair<double, double> pi = get_uv(original_point);
    double u = pi.first;
    double v = pi.second;

    /*
    if (u < 0){
        u = u*-1;
    }

    if (v < 0){
        v = v*-1;
    }*/

    vector<unsigned int> rgb;
    if (u > 0 && v > 0 && u < 1 && v < 1){
        rgb = matrix[::floor(u*matrix.size())][::floor(v*matrix[0].size())];
    }else{
        rgb = {0, 0, 0};
    }

    Color c(rgb[0]/255.0, rgb[1]/255.0, rgb[2]/255.0);
    return c;
}
