//
// Created by tibov on 26/04/23.
//

#ifndef ENGINE_LIGHTTOOLS_H
#define ENGINE_LIGHTTOOLS_H
#include "Light.h"
#include <vector>
using namespace std;
namespace LightTools {
    Color SumAmbient(const vector<Light*>& lights);
    Color SumDifuusInf(const vector<Light*>& lights, const vector<double>& angles);
    Color SumDifuus(const vector<Light*>& lights, const vector<double> &angles);
    Color DifuusSpecularLicht(const vector<Light*>& lights, const Vector3D& normaal, const Vector3D& point, const Color& difuus_ref, const Color& specular_ref, double reflectie_index, bool normaal_inversed);
    Color SumSpecular(const vector<Light*>& lights, const vector<double> &angles, double reflectie_index);
};


#endif //ENGINE_LIGHTTOOLS_H
