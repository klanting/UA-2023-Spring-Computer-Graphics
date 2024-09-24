

#include "../../libraries/easy_image.h"
#include "../Figure/Line2D.h"
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include "../Figure/Face.h"
#include "../../libraries/vector3d.h"
#include "../Figure/Figure.h"
#include "BufferStorage.h"


using namespace std;
using Lines2D = list<Line2D*>;

#ifndef ENGINE_TOOLS2D_H
#define ENGINE_TOOLS2D_H


namespace tool2D{
    img::EasyImage draw2DLines(const Lines2D &lines, const int size, const Color &bc, bool do_z_buf);
    img::EasyImage draw2DLines(const vector<Figure*> &figures, int size, const Color &bc);
    img::EasyImage draw2DLines_z_buffering(const vector<Figure*> &figures, int size, const Color &bc);
    vector<double> get_ranges(const Lines2D &lines);
    vector<double> get_ranges(const vector<Figure*> &figures);
    pair<double, double> get_image_size(const pair<double, double> &ranges, int size);
    double get_scale_factor(const pair<double, double> &ranges, const pair<double, double> &images_size, double margin);
    void use_scale_factor(const Lines2D &lines, double d);
    pair<double, double> get_deviation(const pair<double, double> &image_size, const vector<double> &min_max, double d);
    void use_add_factor(const Lines2D &lines, double dx, double dy);
    tuple<double, pair<double, double>, pair<double, double>> get_scale_factor_all(const vector<Figure*> &figures, int size, double margin);
    img::EasyImage draw2DTriangle(const vector<Figure*> &figures, const Color &bc, double d, pair<double, double> deviation, const pair<unsigned int, unsigned int>& image_size, const vector<Light*>& lights);

    void doFigureProjection(Figure* figure, double d, const pair<double, double>& deviation);
    void determineFaceData(Figure* figure, double d, bool determine_normal);
    void faceZBufferingFilling(Figure* figure, ZBuffer& z_buf, BufferStorage& buf_store);


}

#endif //ENGINE_TOOLS2D_H
