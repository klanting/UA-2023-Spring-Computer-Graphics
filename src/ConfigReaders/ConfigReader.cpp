//
// Created by tibov on 07/08/24.
//

#include "ConfigReader.h"

namespace ini {

    ConfigReader::ConfigReader(const Section &section): section{section} {
    }

    int ConfigReader::getInt(const std::string& key, std::optional<int> default_value) const{

        auto entry = section[key];

        if (default_value.has_value()){
            return entry.as_int_or_default(*default_value);
        }else{
            return entry.as_int_or_die();
        }


    }

    double ConfigReader::getDouble(const std::string& key, std::optional<double> default_value) const{

        auto entry = section[key];

        if (default_value.has_value()){
            return entry.as_double_or_default(*default_value);
        }else{
            return entry.as_double_or_die();
        }
    }

    std::string ConfigReader::getString(const std::string &key) const {
        return section[key].as_string_or_die();
    }

    ini::DoubleTuple ConfigReader::getDoubleTuple(const std::string &key) const {
        return section[key].as_double_tuple_or_die();
    }

    bool ConfigReader::getBool(const std::string &key) const {
        return section[key].as_bool_or_default(false);
    }

    Color ConfigReader::getColor(const std::string &key) const{

        ini::DoubleTuple color_tup = section[key].as_double_tuple_or_default({0, 0, 0});
        Color result_color = Color(color_tup[0], color_tup[1], color_tup[2]);

        return result_color;
    }

    Vector3D ConfigReader::getPoint(const std::string &key, const std::optional<Vector3D>& default_value) const {
        ini::DoubleTuple double_tup;
        if (default_value.has_value()){
            bool exists = section[key].as_double_tuple_if_exists(double_tup);

            if (!exists){
                return *default_value;
            }

        }else{
            double_tup = getDoubleTuple(key);
        }

        return Vector3D::point(double_tup[0], double_tup[1], double_tup[2]);
    }
}