//
// Created by tibov on 26/09/24.
//

#ifndef ENGINE_LIGHTPOSITION_H
#define ENGINE_LIGHTPOSITION_H
#include "Light.h"

class LightPosition: public Light{
public:
    explicit LightPosition(LightColors lightColors);
    [[nodiscard]] bool isInfinity() const override;
private:

};


#endif //ENGINE_LIGHTPOSITION_H
