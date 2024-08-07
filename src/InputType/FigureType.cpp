//
// Created by tibov on 03/08/24.
//

#include "FigureType.h"

FigureType::FigureType(std::string &figure_type): figure_type{figure_type} {

}

bool FigureType::isFractal() const {
    /**
     * Check if the keyword 'Fractal' is in the figure type
     * */
    return (figure_type.find("Fractal") != std::string::npos) || figure_type == "MengerSponge";
}

std::string FigureType::getBaseType() const {
    /*&
     * Get the Part of the substring without the keyword fractal, or keyword Thick
     * */

    std::string s = figure_type;

    std::vector<std::string> remove = {"Fractal", "Thick"};
    for (const std::string& r: remove){
        int f_pos = s.find(r);
        if (f_pos != std::string::npos){
            s = s.substr(0, f_pos)+s.substr(f_pos+r.length());
        }
    }

    return s;
}

bool FigureType::isThick() {
    return figure_type.substr(0, 5) == "Thick";
}
