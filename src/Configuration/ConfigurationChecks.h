//
// Created by tibov on 06/08/24.
//

#ifndef ENGINE_CONFIGURATIONCHECKS_H
#define ENGINE_CONFIGURATIONCHECKS_H


#include "SectionReader.h"
#include "../Figure/Figure.h"

class ConfigurationChecks {
public:
    static void checkTextureMapping(Figure* f, const ini::SectionReader& sr);

};


#endif //ENGINE_CONFIGURATIONCHECKS_H
