//
// Created by tibov on 08/08/24.
//

#ifndef ENGINE_L3DADAPT_H
#define ENGINE_L3DADAPT_H
#include "LSystemAdapt.h"

class L3DAdapt: public LSystemAdapt<LParser::LSystem3D>{
public:
    explicit L3DAdapt(const std::string& inputFile, const Color &c);
private:
};


#endif //ENGINE_L3DADAPT_H
