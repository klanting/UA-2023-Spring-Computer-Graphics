//
// Created by tibov on 30/04/23.
//

#ifndef ENGINE_BUFFERSTORAGE_H
#define ENGINE_BUFFERSTORAGE_H

#include <vector>

#include "Figure.h"
#include "Face.h"
using namespace std;
class BufferStorage: public vector<vector<pair<Figure*, int>>> {
public:
    BufferStorage(unsigned int width, unsigned int height);

private:
    unsigned int width;
    unsigned int height;
};


#endif //ENGINE_BUFFERSTORAGE_H
