//
// Created by tibov on 24/03/23.
//

#ifndef ENGINE_Z_BUFFER_H
#define ENGINE_Z_BUFFER_H

#include <vector>
using namespace std;
class Z_buffer: public vector<vector<double>> {
public:
    Z_buffer(unsigned int width, unsigned int height);

private:
    unsigned int width;
    unsigned int height;
};


#endif //ENGINE_Z_BUFFER_H
