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

std::string FigureType::getFractalFree() const {
    /*&
     * Get the Part of the substring without the keyword fractal
     * */
    if (!isFractal() || figure_type == "MengerSponge"){
        return figure_type;
    }

    int f_pos = figure_type.find("Fractal");

    return figure_type.substr(0, f_pos)+figure_type.substr(f_pos+7);
}
