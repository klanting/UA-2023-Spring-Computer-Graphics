//
// Created by tibov on 05/08/24.
//

#include "FigureReader.h"
#include "../Lighting/LightTools.h"

namespace ini {


    FigureReader::FigureReader(bool light_supported, const Section &section, const Color& ambient): ConfigReader{section},
    light_supported{light_supported}, ambient{ambient} {

    }



    Color FigureReader::getFigureColor() const {
        ini::DoubleTuple c_tup;
        if (light_supported){
            c_tup = getDoubleTuple("ambientReflection");

        }else{
            c_tup = getDoubleTuple("color");
        }

        /*add normal color or ambient light*/

        Color c(c_tup[0], c_tup[1], c_tup[2]);

        if (light_supported){
            c.multiply(ambient);
        }

        return c;
    }

    Reflections FigureReader::getReflections() const {
        Color diffuse_reflection = getColor("diffuseReflection");
        Color specular_reflection = getColor("specularReflection");

        double reflection_index = getDouble("reflectionCoefficient", 1);

        Reflections reflections{ambient, diffuse_reflection, specular_reflection, reflection_index};

        return reflections;
    }


} // ini