//
// Created by tibov on 03/08/24.
//

#ifndef ENGINE_FIGURETYPE_H
#define ENGINE_FIGURETYPE_H
#include <string>


class FigureType {
    /*
     * This class represents a class containing information about the figure type
     * */
public:
    explicit FigureType(std::string &figure_type);

    bool isFractal() const;

    std::string getFractalFree() const;

private:
    std::string figure_type;
};


#endif //ENGINE_FIGURETYPE_H
