//
// Created by tibov on 07/08/24.
//

#ifndef ENGINE_CONFIGREADER_H
#define ENGINE_CONFIGREADER_H

#include "../Configuration/ini_configuration.h"
#include "../Figure/Color.h"
#include "../Figure/vector3d.h"
#include <optional>

namespace ini {
    class ConfigReader {
    public:
        explicit ConfigReader(const ini::Section& section);

        [[nodiscard]] int getInt(const std::string& key, std::optional<int> default_value = std::nullopt) const;
        [[nodiscard]] double getDouble(const std::string& key, std::optional<double> default_value = std::nullopt) const;
        [[nodiscard]] std::string getString(const std::string& key) const;
        [[nodiscard]] ini::DoubleTuple getDoubleTuple(const std::string& key) const;
        [[nodiscard]] bool getBool(const std::string& key) const;
        [[nodiscard]] Color getColor(const std::string& key) const;
        [[nodiscard]] Vector3D getPoint(const std::string& key, const std::optional<Vector3D>& default_value = std::nullopt) const;

    protected:
        ini::Section section;
    };

}


#endif //ENGINE_CONFIGREADER_H
