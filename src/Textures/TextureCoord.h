//
// Created by tibov on 17/05/23.
//

#ifndef ENGINE_TEXTURECOORD_H
#define ENGINE_TEXTURECOORD_H
#include "../../libraries/vector3d.h"
#include <vector>
#include "../Figure/Color.h"
#include "../../libraries/easy_image.h"
#include <map>
using namespace std;

class TextureCoord {
public:
    img::EasyImage img_ambient = img::EasyImage(0, 0);
    img::EasyImage img_difuus = img::EasyImage(0, 0);
    Color getAmbient(double u, double v);
    Color getDifuus(double u, double v);
    bool img_dif = false;
private:
};


#endif //ENGINE_TEXTURECOORD_H
