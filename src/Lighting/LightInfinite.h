//
// Created by tibov on 26/09/24.
//

#ifndef ENGINE_LIGHTINFINITE_H
#define ENGINE_LIGHTINFINITE_H
#include "Light.h"

class LightInfinite: public Light{
public:
    explicit LightInfinite(LightColors lightColors);
    [[nodiscard]] bool isInfinity() const override;
private:
    bool infinity;
};


#endif //ENGINE_LIGHTINFINITE_H
