//
// Created by tibov on 07/08/24.
//

#include "LightReader.h"

namespace ini {
    LightReader::LightReader(const Section &section) : ConfigReader(section) {

    }

    LightColors LightReader::getLightColors() const{

        Color ambient = getColor("ambientLight");
        Color diffuse = getColor("diffuseLight");
        Color specular = getColor("specularLight");

        LightColors lc{ambient, diffuse, specular};

        return lc;
    }

    bool LightReader::isDiffuseInf() const {
        return getBool("infinity");
    }
} // ini