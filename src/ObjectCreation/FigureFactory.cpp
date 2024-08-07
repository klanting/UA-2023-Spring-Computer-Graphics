//
// Created by tibov on 03/08/24.
//

#include "FigureFactory.h"
#include "../LSystems/L_system3D.h"
#include <map>
#include <functional>

Figure *FigureFactory::create(const FigureType &figure_type, const ini::FigureReader& sr) {
    /**
     * This function follows the factory design pattern to create the right figure,
     * instead of the traditional if statements/ switch statements I chose to make the factory
     * using a map
     * */

    map<std::string, function<Figure*(const ini::FigureReader& sr)>> function_map;

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

    Figure* f = function_map[figure_type.getBaseType()](sr);


    return f;
}

Figure *FigureFactory::createCube(const ini::FigureReader& sr) {
    return Bodies3D::CreateCubes(sr.getFigureColor());
}

Figure *FigureFactory::createIcosahedron(const ini::FigureReader& sr) {
    return Bodies3D::CreateIcosahedron(sr.getFigureColor());
}

Figure *FigureFactory::createOctahedron(const ini::FigureReader& sr) {
    return Bodies3D::CreateOctahedron(sr.getFigureColor());
}

Figure *FigureFactory::createCone(const ini::FigureReader& sr) {
    int n = sr.getInt("n");
    double height = sr.getDouble("height");
    return Bodies3D::CreateCone(sr.getFigureColor(), n, height);
}

Figure *FigureFactory::createDodecahedron(const ini::FigureReader& sr) {
    return Bodies3D::CreateDodecahedron(sr.getFigureColor());
}

Figure *FigureFactory::createCylinder(const ini::FigureReader& sr) {
    int n = sr.getInt("n");
    double height = sr.getDouble("height");
    return Bodies3D::CreateCylinder(sr.getFigureColor(), n, height, true);
}

Figure *FigureFactory::createSphere(const ini::FigureReader& sr) {
    int n = sr.getInt("n");
    return Bodies3D::CreateSphere(sr.getFigureColor(), n);
}

Figure *FigureFactory::createTorus(const ini::FigureReader& sr) {
    int n = sr.getInt("n");
    int m = sr.getInt("m");
    double r = sr.getDouble("r");
    double R = sr.getDouble("R");
    return Bodies3D::CreateTorus(sr.getFigureColor(), n, m, r, R);
}

Figure *FigureFactory::createTetrahedron(const ini::FigureReader& sr) {
    return Bodies3D::CreateTetrahedron(sr.getFigureColor());
}

Figure *FigureFactory::create3DLSystem(const ini::FigureReader& sr) {
    string input_file = sr.getString("inputfile");


    LParser::LSystem3D l_system;

    std::ifstream input_stream(input_file);
    input_stream >> l_system;
    input_stream.close();

    L_system3D l(l_system, sr.getFigureColor());

    return l.get_fig();
}

Figure *FigureFactory::createMobius(const ini::FigureReader& sr) {
    int n = sr.getInt("n");
    int m = sr.getInt("m");
    return Bodies3D::CreateMobiusband(sr.getFigureColor(), n, m);
}

Figure *FigureFactory::createTorusBelly(const ini::FigureReader& sr) {
    int n = sr.getInt("n");
    int m = sr.getInt("m");
    return Bodies3D::CreateTorusUmbilic(sr.getFigureColor(), n, m);
}

Figure *FigureFactory::createBuckyBall(const ini::FigureReader& sr) {
    return Bodies3D::CreateBuckyBall(sr.getFigureColor());
}

Figure *FigureFactory::createLineDrawing(const ini::FigureReader& sr) {
    int points_amount = sr.getInt("nrPoints");

    vector<Vector3D> points;
    vector<vector<int>> lines;
    for (int j=0; j<points_amount; j++){
        ini::DoubleTuple point_tup = sr.getDoubleTuple("point"+to_string(j));
        Vector3D p = Vector3D::point(point_tup[0], point_tup[1], point_tup[2]);
        points.push_back(p);
    }

    int lines_amount = sr.getInt("nrLines");
    for (int j=0; j<lines_amount; j++){
        ini::DoubleTuple point_index_tup = sr.getDoubleTuple("line"+to_string(j));
        vector<int> v;
        for (int k=0; k<point_index_tup.size(); k++){
            v.push_back((int) point_index_tup[k]);
        }

        lines.push_back(v);
    }
    return new Figure(points, lines, sr.getFigureColor());
}

Figure *FigureFactory::createMengerSponge(const ini::FigureReader& sr) {

    return Bodies3D::CreateMengerSponge(sr.getFigureColor());
}
