//
// Created by tibov on 03/08/24.
//

#include "FigureFactory.h"
#include "../../L_system3D.h"
#include <map>
#include <functional>

Figure *FigureFactory::create(const FigureType &figure_type, const Color &color, const ini::Section& config) {
    /**
     * This function follows the factory design pattern to create the right figure,
     * instead of the traditional if statements/ switch statements I chose to make the factory
     * using a map
     * */

    map<std::string, function<Figure*(const Color&, const ini::Section& config)>> function_map;

    function_map.insert({"Cube", FigureFactory::createCube});
    function_map.insert({"Icosahedron", FigureFactory::createIcosahedron});
    function_map.insert({"Octahedron", FigureFactory::createOctahedron});
    function_map.insert({"Cone", FigureFactory::createCone});
    function_map.insert({"Dodecahedron", FigureFactory::createDodecahedron});
    function_map.insert({"Cylinder", FigureFactory::createCylinder});
    function_map.insert({"Sphere", FigureFactory::createSphere});
    function_map.insert({"Torus", FigureFactory::createTorus});
    function_map.insert({"Tetrahedron", FigureFactory::createTetrahedron});
    function_map.insert({"3DLSystem", FigureFactory::create3DLSystem});
    function_map.insert({"Mobius", FigureFactory::createMobius});
    function_map.insert({"TorusBelly", FigureFactory::createTorusBelly});
    function_map.insert({"BuckyBall", FigureFactory::createBuckyBall});
    function_map.insert({"LineDrawing", FigureFactory::createLineDrawing});
    function_map.insert({"MengerSponge", FigureFactory::createMengerSponge});

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

Figure *FigureFactory::createDodecahedron(const Color &color, const ini::Section &config) {
    return Bodies3D::CreateDodecahedron(color);
}

Figure *FigureFactory::createCylinder(const Color &color, const ini::Section &config) {
    int n = config["n"].as_int_or_die();
    double height = config["height"].as_double_or_die();
    return Bodies3D::CreateCylinder(color, n, height, true);
}

Figure *FigureFactory::createSphere(const Color &color, const ini::Section &config) {
    int n = config["n"].as_int_or_die();
    return Bodies3D::CreateSphere(color, n);
}

Figure *FigureFactory::createTorus(const Color &color, const ini::Section &config) {
    int n = config["n"].as_int_or_die();
    int m = config["m"].as_int_or_die();
    double r = config["r"].as_double_or_die();
    double R = config["R"].as_double_or_die();
    return Bodies3D::CreateTorus(color, n, m, r, R);
}

Figure *FigureFactory::createTetrahedron(const Color &color, const ini::Section &config) {
    return Bodies3D::CreateTetrahedron(color);
}

Figure *FigureFactory::create3DLSystem(const Color &color, const ini::Section &config) {
    string input_file = config["inputfile"].as_string_or_die();

    LParser::LSystem3D l_system;

    std::ifstream input_stream(input_file);
    input_stream >> l_system;
    input_stream.close();

    L_system3D l(l_system, color);

    return l.get_fig();
}

Figure *FigureFactory::createMobius(const Color &color, const ini::Section &config) {
    int n = config["n"].as_int_or_die();
    int m = config["m"].as_int_or_die();
    return Bodies3D::CreateMobiusband(color, n, m);
}

Figure *FigureFactory::createTorusBelly(const Color &color, const ini::Section &config) {
    int n = config["n"].as_int_or_die();
    int m = config["m"].as_int_or_die();
    return Bodies3D::CreateTorusUmbilic(color, n, m);
}

Figure *FigureFactory::createBuckyBall(const Color &color, const ini::Section &config) {
    return Bodies3D::CreateBuckyBall(color);
}

Figure *FigureFactory::createLineDrawing(const Color &color, const ini::Section &config) {
    int points_amount = config["nrPoints"].as_int_or_die();

    vector<Vector3D> points;
    vector<vector<int>> lines;
    for (int j=0; j<points_amount; j++){
        ini::DoubleTuple point_tup = config["point"+to_string(j)].as_double_tuple_or_die();
        Vector3D p = Vector3D::point(point_tup[0], point_tup[1], point_tup[2]);
        points.push_back(p);
    }

    int lines_amount = config["nrLines"].as_int_or_die();
    for (int j=0; j<lines_amount; j++){
        ini::DoubleTuple point_index_tup = config["line"+to_string(j)].as_double_tuple_or_die();
        vector<int> v;
        for (int k=0; k<point_index_tup.size(); k++){
            v.push_back((int) point_index_tup[k]);
        }

        lines.push_back(v);
    }
    return new Figure(points, lines, color);
}

Figure *FigureFactory::createMengerSponge(const Color &color, const ini::Section &config) {
    return Bodies3D::CreateMengerSponge(color);
}
