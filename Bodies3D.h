//
// Created by tibov on 17/03/23.
//

#ifndef ENGINE_BODIES3D_H
#define ENGINE_BODIES3D_H
#include "Figure.h"
#include "vector3d.h"
namespace Bodies3D{
    Figure* CreateCubes(Color &c);
    Figure* CreateIcosahedron(Color &c);
    Figure* CreateOctahedron(Color &c);
    Figure* CreateDodecahedron(Color &c);
    Figure* CreateCone(Color &c, int n, double height);
    Figure* CreateCylinder(Color &c, int n, double height, bool all);
    Figure* CreateSphere(Color &c, int n);
    Figure* CreateTorus(Color &c, int n, int m, double r, double R);
    Figure* CreateTetrahedron(Color &c);
    Figure* CreateMobiusband(Color &c, int n, int m);
    Figure* CreateTorusUmbilic(Color &c, int n, int m);
    void generateFractal(Figure* fig, vector<Figure*>& fractal_output, int nr_iterations, double scale, double original_scale, const string& type);
    Figure* CreateBuckyBall(Color &c);
    Figure* CreateMengerSpons(Color &c);
    void makeThick(Figure* fig, vector<Figure*>& fractal_output, double radius, int m, int n);


}


#endif //ENGINE_BODIES3D_H
