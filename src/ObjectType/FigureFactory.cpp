//
// Created by tibov on 03/08/24.
//

#include "FigureFactory.h"
#include "../LSystems/L_system3D.h"
#include <map>
#include <functional>

Figure *FigureFactory::create(const FigureType &figure_type, const ini::SectionReader& sr) {
    /**
     * This function follows the factory design pattern to create the right figure,
     * instead of the traditional if statements/ switch statements I chose to make the factory
     * using a map
     * */

    map<std::string, function<Figure*(const ini::SectionReader& sr)>> function_map;

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

    Figure* f = function_map[figure_type.getFractalFree()](sr);


    return f;
}

Figure *FigureFactory::createCube(const ini::SectionReader& sr) {
    return Bodies3D::CreateCubes(sr.getColor());
}

Figure *FigureFactory::createIcosahedron(const ini::SectionReader& sr) {
    return Bodies3D::CreateIcosahedron(sr.getColor());
}

Figure *FigureFactory::createOctahedron(const ini::SectionReader& sr) {
    return Bodies3D::CreateOctahedron(sr.getColor());
}

Figure *FigureFactory::createCone(const ini::SectionReader& sr) {
    int n = sr.getIntValue("n");
    double height = sr.getDoubleValue("height");
    return Bodies3D::CreateCone(sr.getColor(), n, height);
}

Figure *FigureFactory::createDodecahedron(const ini::SectionReader& sr) {
    return Bodies3D::CreateDodecahedron(sr.getColor());
}

Figure *FigureFactory::createCylinder(const ini::SectionReader& sr) {
    int n = sr.getIntValue("n");
    double height = sr.getDoubleValue("height");
    return Bodies3D::CreateCylinder(sr.getColor(), n, height, true);
}

Figure *FigureFactory::createSphere(const ini::SectionReader& sr) {
    int n = sr.getIntValue("n");
    return Bodies3D::CreateSphere(sr.getColor(), n);
}

Figure *FigureFactory::createTorus(const ini::SectionReader& sr) {
    int n = sr.getIntValue("n");
    int m = sr.getIntValue("m");
    double r = sr.getDoubleValue("r");
    double R = sr.getDoubleValue("R");
    return Bodies3D::CreateTorus(sr.getColor(), n, m, r, R);
}

Figure *FigureFactory::createTetrahedron(const ini::SectionReader& sr) {
    return Bodies3D::CreateTetrahedron(sr.getColor());
}

Figure *FigureFactory::create3DLSystem(const ini::SectionReader& sr) {
    string input_file = sr.getStringValue("inputfile");


    LParser::LSystem3D l_system;

    std::ifstream input_stream(input_file);
    input_stream >> l_system;
    input_stream.close();

    L_system3D l(l_system, sr.getColor());

    return l.get_fig();
}

Figure *FigureFactory::createMobius(const ini::SectionReader& sr) {
    int n = sr.getIntValue("n");
    int m = sr.getIntValue("m");
    return Bodies3D::CreateMobiusband(sr.getColor(), n, m);
}

Figure *FigureFactory::createTorusBelly(const ini::SectionReader& sr) {
    int n = sr.getIntValue("n");
    int m = sr.getIntValue("m");
    return Bodies3D::CreateTorusUmbilic(sr.getColor(), n, m);
}

Figure *FigureFactory::createBuckyBall(const ini::SectionReader& sr) {
    return Bodies3D::CreateBuckyBall(sr.getColor());
}

Figure *FigureFactory::createLineDrawing(const ini::SectionReader& sr) {
    int points_amount = sr.getIntValue("nrPoints");

    vector<Vector3D> points;
    vector<vector<int>> lines;
    for (int j=0; j<points_amount; j++){
        ini::DoubleTuple point_tup = sr.getDoubleTuple("point"+to_string(j));
        Vector3D p = Vector3D::point(point_tup[0], point_tup[1], point_tup[2]);
        points.push_back(p);
    }

    int lines_amount = sr.getIntValue("nrLines");
    for (int j=0; j<lines_amount; j++){
        ini::DoubleTuple point_index_tup = sr.getDoubleTuple("line"+to_string(j));
        vector<int> v;
        for (int k=0; k<point_index_tup.size(); k++){
            v.push_back((int) point_index_tup[k]);
        }

        lines.push_back(v);
    }
    return new Figure(points, lines, sr.getColor());
}

Figure *FigureFactory::createMengerSponge(const ini::SectionReader& sr) {

    return Bodies3D::CreateMengerSponge(sr.getColor());
}
