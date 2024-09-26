//
// Created by tibov on 26/09/24.
//

#include "LightPosition.h"

bool LightPosition::isInfinity() const {
    return false;
}

LightPosition::LightPosition(LightColors lightColors) : Light(lightColors) {

}
