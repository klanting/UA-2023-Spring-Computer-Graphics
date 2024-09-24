//
// Created by tibov on 24/03/23.
//

#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H


class ZBuffer {
public:
    ZBuffer(unsigned int width, unsigned int height);
    double get(unsigned int y, unsigned int x);
    void set(unsigned int y, unsigned int x, double val);
    ~ZBuffer();

private:
    unsigned int width;
    unsigned int height;

    unsigned int calculatePosition(unsigned int y, unsigned int x);

    double* grid;
};


#endif //ENGINE_ZBUFFER_H
