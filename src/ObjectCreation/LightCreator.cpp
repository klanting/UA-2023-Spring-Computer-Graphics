//
// Created by tibov on 08/08/24.
//

#include "LightCreator.h"


Light *LightCreator::create(const ini::LightReader &lr, bool shadow_support, int shadow_size) {
    LightColors colors = lr.getLightColors();

    Light* l = nullptr;
    if (lr.isDiffuseInf()){
        l = new LightInfinite(colors);


        l->direction = lr.getPoint("direction");

    }else{
        l = new LightPosition(colors);

        double spot_angle = lr.getDouble("spotAngle", 90);
        l->spot_angle = cos(spot_angle*M_PI/180.0);

        l->location = lr.getPoint("location", Vector3D::point(0, 0, 0));
    }

    if (shadow_support && !lr.isDiffuseInf()){
        l->mask = new ShadowMask();
        l->shadow_size = shadow_size;
        l->shadow = true;
    }
    return l;
}
