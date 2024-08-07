//
// Created by tibov on 07/08/24.
//

#ifndef ENGINE_LIGHTREADER_H
#define ENGINE_LIGHTREADER_H
#include "ConfigReader.h"
#include "../Figure/Color.h"
#include "../Lighting/Light.h"

namespace ini {

    class LightReader: public ConfigReader{
    public:
        explicit LightReader(const ini::Section& section);
        LightColors getLightColors() const;
        bool isDiffuseInf() const;
    private:

    };

} // ini

#endif //ENGINE_LIGHTREADER_H
