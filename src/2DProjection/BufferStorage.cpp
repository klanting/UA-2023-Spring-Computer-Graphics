//
// Created by tibov on 30/04/23.
//

#include "BufferStorage.h"

#include "iostream"
using namespace std;
BufferStorage::BufferStorage(unsigned int width, unsigned int height): width(width), height(height) {

    this->reserve(width);

    for (int i = 0; i<width; i++){
        vector<pair<Figure*, int>> row;
        row.reserve(height);
        for (int j = 0; j<height; j++){
            row.push_back(make_pair(nullptr, -1));
        }
        this->push_back(row);
    }
}
