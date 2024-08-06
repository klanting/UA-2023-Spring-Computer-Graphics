//
// Created by tibov on 05/08/24.
//

#include "SectionReader.h"
#include "../../LightTools.h"

namespace ini {


    SectionReader::SectionReader(bool light_supported, const Section &section, const Color& ambient): light_supported{light_supported}, section{section}, ambient{ambient} {

    }

    int SectionReader::getIntValue(const std::string& key) const{
        return section[key].as_int_or_die();
    }

    double SectionReader::getDoubleValue(const std::string& key) const{
        return section[key].as_double_or_die();
    }

    std::string SectionReader::getStringValue(const std::string &key) const {
        return section[key].as_string_or_die();
    }

    ini::DoubleTuple SectionReader::getDoubleTuple(const std::string &key) const {
        return section[key].as_double_tuple_or_die();
    }

    Color SectionReader::getColor() const {
        ini::DoubleTuple c_tup;
        if (light_supported){
            c_tup = section["ambientReflection"].as_double_tuple_or_die();

        }else{
            c_tup = section["color"].as_double_tuple_or_die();
        }

        /*add normal color or ambient light*/

        Color c(c_tup[0], c_tup[1], c_tup[2]);

        if (light_supported){
            c.multiply(ambient);
        }

        return c;
    }

    bool SectionReader::getBoolValue(const string &key) const {
        return section[key].as_bool_or_default(false);
    }
} // ini