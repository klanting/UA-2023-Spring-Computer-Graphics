//
// Created by tibov on 24/03/23.
//

#ifndef ENGINE_Z_BUFFER_H
#define ENGINE_Z_BUFFER_H


class Z_buffer {
public:
    Z_buffer(unsigned int width, unsigned int height);
    double get(unsigned int y, unsigned int x);
    void set(unsigned int y, unsigned int x, double val);
    ~Z_buffer();

private:
    unsigned int width;
    unsigned int height;

    unsigned int calculatePosition(unsigned int y, unsigned int x);

    double* grid;
};


#endif //ENGINE_Z_BUFFER_H
