//
// Created by tibov on 05/08/24.
//

#ifndef ENGINE_FIGUREREADER_H
#define ENGINE_FIGUREREADER_H
#include "../../libraries/ini_configuration.h"
#include <string>
#include "../Figure/Color.h"
#include "ConfigReader.h"
#include "../Figure/Figure.h"

namespace ini {

    class FigureReader: public ConfigReader {
    /**
     * This class its purpose is to access the right data fields from the configuration
     * */
    public:

        explicit FigureReader(bool light_supported, const ini::Section& section, const Color& ambient);

        [[nodiscard]] Color getFigureColor() const;
        [[nodiscard]] Reflections getReflections() const;
    private:
        bool light_supported;

        Color ambient;
    };

} // ini

#endif //ENGINE_FIGUREREADER_H
