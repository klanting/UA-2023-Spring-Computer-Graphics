//
// Created by tibov on 03/08/24.
//

#include "FigureFactory.h"
#include <map>
#include <functional>

Figure *FigureFactory::create(const FigureType &figure_type, const Color &color, const ini::Section& config) {


    map<std::string, function<Figure*(const Color&, const ini::Section& config)>> function_map;

    function_map.insert({"Cube", FigureFactory::createCube});
    function_map.insert({"Icosahedron", FigureFactory::createIcosahedron});
    function_map.insert({"Octahedron", FigureFactory::createOctahedron});
    function_map.insert({"Cone", FigureFactory::createCone});

    Figure* f = function_map[figure_type.getFractalFree()](color, config);


    return f;
}

Figure *FigureFactory::createCube(const Color &color, const ini::Section &config) {
    return Bodies3D::CreateCubes(color);
}

Figure *FigureFactory::createIcosahedron(const Color &color, const ini::Section &config) {
    return Bodies3D::CreateIcosahedron(color);
}

Figure *FigureFactory::createOctahedron(const Color &color, const ini::Section &config) {
    return Bodies3D::CreateOctahedron(color);
}

Figure *FigureFactory::createCone(const Color &color, const ini::Section &config) {
    int n = config["n"].as_int_or_die();
    double height = config["height"].as_double_or_die();
    return Bodies3D::CreateCone(color, n, height);
}
