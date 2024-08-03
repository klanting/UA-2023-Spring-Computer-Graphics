//
// Created by tibov on 24/03/23.
//

#include "Z_buffer.h"
#include <limits>
#include "iostream"
using namespace std;
Z_buffer::Z_buffer(unsigned int width, unsigned int height): width(width), height(height) {

    for (int i = 0; i<width; i++){
        vector<double> row;
        for (int j = 0; j<height; j++){
            row.push_back(numeric_limits<double>::infinity());
        }
        this->push_back(row);
    }
}
