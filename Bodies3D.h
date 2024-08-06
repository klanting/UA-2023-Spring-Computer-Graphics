//
// Created by tibov on 17/03/23.
//

#ifndef ENGINE_BODIES3D_H
#define ENGINE_BODIES3D_H
#include "Figure.h"
#include "vector3d.h"

#include "ini_configuration.h"


namespace Bodies3D{
    Figure* CreateCubes(const Color &c);
    Figure* CreateIcosahedron(const Color &c);
    Figure* CreateOctahedron(const Color &c);
    Figure* CreateDodecahedron(const Color &c);
    Figure* CreateCone(const Color &c, int n, double height);
    Figure* CreateCylinder(const Color &c, int n, double height, bool all);
    Figure* CreateSphere(const Color &c, int n);
    Figure* CreateTorus(const Color &c, int n, int m, double r, double R);
    Figure* CreateTetrahedron(const Color &c);
    Figure* CreateMobiusband(const Color &c, int n, int m);
    Figure* CreateTorusUmbilic(const Color &c, int n, int m);
    void generateFractal(Figure* fig, vector<Figure*>& fractal_output, int nr_iterations, double scale, double original_scale, const string& type);
    Figure* CreateBuckyBall(const Color &c);
    Figure* CreateMengerSponge(const Color &c);
    void makeThick(Figure* fig, vector<Figure*>& fractal_output, double radius, int m, int n);


}


#endif //ENGINE_BODIES3D_H
