//
// Created by tibov on 26/09/24.
//

#include "LightInfinite.h"

bool LightInfinite::isInfinity() const {
    return infinity;
}

LightInfinite::LightInfinite(LightColors lightColors): Light{lightColors} {

}
