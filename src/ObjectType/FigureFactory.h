

#ifndef ENGINE_FIGUREFACTORY_H
#define ENGINE_FIGUREFACTORY_H
#include "../../Bodies3D.h"
#include "FigureType.h"
#include "../../Color.h"
#include "../../ini_configuration.h"

class FigureFactory {
    /*
     * Factory Design pattern for creating figures
     * */
public:
    explicit FigureFactory() = default;
    static Figure* create(const FigureType &figure_type, const Color &color, const ini::Section& config);
private:

    static Figure* createCube(const Color &color, const ini::Section& config);
    static Figure* createIcosahedron(const Color &color, const ini::Section& config);
    static Figure* createOctahedron(const Color &color, const ini::Section& config);
    static Figure* createCone(const Color &color, const ini::Section& config);
    static Figure* createDodecahedron(const Color &color, const ini::Section& config);
    static Figure* createCylinder(const Color &color, const ini::Section& config);
    static Figure* createSphere(const Color &color, const ini::Section& config);
    static Figure* createTorus(const Color &color, const ini::Section& config);
    static Figure* createTetrahedron(const Color &color, const ini::Section& config);
    static Figure* create3DLSystem(const Color &color, const ini::Section& config);
    static Figure* createMobius(const Color &color, const ini::Section& config);
    static Figure* createTorusBelly(const Color &color, const ini::Section& config);
    static Figure* createBuckyBall(const Color &color, const ini::Section& config);
    static Figure* createLineDrawing(const Color &color, const ini::Section& config);
    static Figure* createMengerSponge(const Color &color, const ini::Section& config);

};


#endif //ENGINE_FIGUREFACTORY_H
