//
// Created by tibov on 08/08/24.
//

#ifndef ENGINE_L2DADAPT_H
#define ENGINE_L2DADAPT_H

#include "LSystemAdapt.h"

class L2DAdapt: public LSystemAdapt<LParser::LSystem2D> {
public:
    explicit L2DAdapt(const std::string& inputFile, const Color &c);
private:
};


#endif //ENGINE_L2DADAPT_H
