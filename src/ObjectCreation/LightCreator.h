//
// Created by tibov on 08/08/24.
//

#ifndef ENGINE_LIGHTCREATOR_H
#define ENGINE_LIGHTCREATOR_H


#include "../Lighting/LightInfinite.h"
#include "../Lighting/LightPosition.h"
#include "../ConfigReaders/LightReader.h"

class LightCreator {
public:
    static Light* create(const ini::LightReader& lr, bool shadow_support, int shadow_size);
private:
};


#endif //ENGINE_LIGHTCREATOR_H
