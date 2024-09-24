

#include "ZBuffer.h"
#include <limits>
#include <cstdlib>
using namespace std;
ZBuffer::ZBuffer(unsigned int width, unsigned int height): width(width), height(height) {

    unsigned int size = width*height;

    grid = (double*) std::malloc(size*sizeof(double));

    auto grid_ptr = grid;
    for (int i=0; i<size; i++){
        *grid_ptr = numeric_limits<double>::infinity();
        grid_ptr++;

    }

}

double ZBuffer::get(unsigned int y, unsigned int x) {
    return grid[calculatePosition(y, x)];
}

unsigned int ZBuffer::calculatePosition(unsigned int y, unsigned int x) {

    return x*width+y;
}

void ZBuffer::set(unsigned int y, unsigned int x, double val) {
    grid[calculatePosition(y, x)] = val;
}

ZBuffer::~ZBuffer() {
    free(grid);
}
