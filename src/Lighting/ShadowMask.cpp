//
// Created by tibov on 03/05/23.
//

#include "ShadowMask.h"

#include <limits>
#include "iostream"
using namespace std;
ShadowMask::ShadowMask(unsigned int width, unsigned int height): width(width), height(height) {
    this->reserve(width);

    for (int i = 0; i<width; i++){
        vector<double> row;
        row.reserve(height);

        for (int j = 0; j<height; j++){
            row.push_back(numeric_limits<double>::infinity());
        }
        this->push_back(row);
    }
}

ShadowMask::ShadowMask() {

}
