//
// Created by tibov on 08/08/24.
//

#ifndef ENGINE_L2DADAPT_H
#define ENGINE_L2DADAPT_H

#include "LSystemAdapt.h"

class L2DAdapt: public LSystemAdapt<LParser::LSystem2D> {
public:
    L2DAdapt(const std::string& input_file);
private:
};


#endif //ENGINE_L2DADAPT_H
