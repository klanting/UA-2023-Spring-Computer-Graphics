

#include "Z_buffer.h"
#include <limits>
#include <cstdlib>
using namespace std;
Z_buffer::Z_buffer(unsigned int width, unsigned int height): width(width), height(height) {

    unsigned int size = width*height;

    grid = (double*) std::malloc(size*sizeof(double));

    auto grid_ptr = grid;
    for (int i=0; i<size; i++){
        *grid_ptr = numeric_limits<double>::infinity();
        grid_ptr++;

    }

}

double Z_buffer::get(unsigned int y, unsigned int x) {
    return grid[calculatePosition(y, x)];
}

unsigned int Z_buffer::calculatePosition(unsigned int y, unsigned int x) {

    return x*width+y;
}

void Z_buffer::set(unsigned int y, unsigned int x, double val) {
    grid[calculatePosition(y, x)] = val;
}

Z_buffer::~Z_buffer() {
    free(grid);
}
