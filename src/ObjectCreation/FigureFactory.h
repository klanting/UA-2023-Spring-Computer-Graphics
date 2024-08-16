

#ifndef ENGINE_FIGUREFACTORY_H
#define ENGINE_FIGUREFACTORY_H
#include "Bodies3D.h"
#include "../InputType/FigureType.h"
#include "../Figure/Color.h"
#include "../../libraries/ini_configuration.h"
#include "../ConfigReaders/FigureReader.h"

class FigureFactory {
    /*
     * Factory Design pattern for creating figures
     * */
public:
    static Figure* create(const FigureType &figure_type, const ini::FigureReader& sr);
private:

    static Figure* createCube(const ini::FigureReader& sr);
    static Figure* createIcosahedron(const ini::FigureReader& sr);
    static Figure* createOctahedron(const ini::FigureReader& sr);
    static Figure* createCone(const ini::FigureReader& sr);
    static Figure* createDodecahedron(const ini::FigureReader& sr);
    static Figure* createCylinder(const ini::FigureReader& sr);
    static Figure* createSphere(const ini::FigureReader& sr);
    static Figure* createTorus(const ini::FigureReader& sr);
    static Figure* createTetrahedron(const ini::FigureReader& sr);
    static Figure* create3DLSystem(const ini::FigureReader& sr);
    static Figure* createMobius(const ini::FigureReader& sr);
    static Figure* createTorusBelly(const ini::FigureReader& sr);
    static Figure* createBuckyBall(const ini::FigureReader& sr);
    static Figure* createLineDrawing(const ini::FigureReader& sr);
    static Figure* createMengerSponge(const ini::FigureReader& sr);

};


#endif //ENGINE_FIGUREFACTORY_H
