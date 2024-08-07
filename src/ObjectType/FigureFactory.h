

#ifndef ENGINE_FIGUREFACTORY_H
#define ENGINE_FIGUREFACTORY_H
#include "../ObjectCreation/Bodies3D.h"
#include "FigureType.h"
#include "../Figure/Color.h"
#include "../Configuration/ini_configuration.h"
#include "../Configuration/SectionReader.h"

class FigureFactory {
    /*
     * Factory Design pattern for creating figures
     * */
public:
    explicit FigureFactory() = default;
    static Figure* create(const FigureType &figure_type, const ini::SectionReader& sr);
private:

    static Figure* createCube(const ini::SectionReader& sr);
    static Figure* createIcosahedron(const ini::SectionReader& sr);
    static Figure* createOctahedron(const ini::SectionReader& sr);
    static Figure* createCone(const ini::SectionReader& sr);
    static Figure* createDodecahedron(const ini::SectionReader& sr);
    static Figure* createCylinder(const ini::SectionReader& sr);
    static Figure* createSphere(const ini::SectionReader& sr);
    static Figure* createTorus(const ini::SectionReader& sr);
    static Figure* createTetrahedron(const ini::SectionReader& sr);
    static Figure* create3DLSystem(const ini::SectionReader& sr);
    static Figure* createMobius(const ini::SectionReader& sr);
    static Figure* createTorusBelly(const ini::SectionReader& sr);
    static Figure* createBuckyBall(const ini::SectionReader& sr);
    static Figure* createLineDrawing(const ini::SectionReader& sr);
    static Figure* createMengerSponge(const ini::SectionReader& sr);

};


#endif //ENGINE_FIGUREFACTORY_H
