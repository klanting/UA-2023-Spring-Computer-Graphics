//
// Created by tibov on 05/08/24.
//

#ifndef ENGINE_SECTIONREADER_H
#define ENGINE_SECTIONREADER_H
#include "ini_configuration.h"
#include <string>
#include "../Figure/Color.h"

namespace ini {

    class SectionReader {
    /**
     * This class its purpose is to access the right data fields from the configuration
     * */
    public:

        explicit SectionReader(bool light_supported, const ini::Section& section, const Color& ambient);

        int getIntValue(const std::string& key) const;
        double getDoubleValue(const std::string& key) const;
        std::string getStringValue(const std::string& key) const;
        ini::DoubleTuple getDoubleTuple(const std::string& key) const;
        bool getBoolValue(const std::string& key) const;

        Color getColor() const;
        ini::Section section;
    private:
        bool light_supported;

        Color ambient;
    };

} // ini

#endif //ENGINE_SECTIONREADER_H
