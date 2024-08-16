//
// Created by tibov on 08/08/24.
//

#ifndef ENGINE_LSYSTEMADAPT_H
#define ENGINE_LSYSTEMADAPT_H

#include "string"
#include "../../../libraries/l_parser.h"
template <typename T>
class LSystemAdapt {


protected:
    LSystemAdapt(const std::string& input_file);

    T l_system;


};




#endif //ENGINE_LSYSTEMADAPT_H
