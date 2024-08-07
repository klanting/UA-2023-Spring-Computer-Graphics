//
// Created by tibov on 26/04/23.
//

#include "LightTools.h"
#include <cmath>
namespace LightTools {
    Color SumAmbient(const vector<Light*>& lights){
        double red = 0;
        double green = 0;
        double blue = 0;
        for (auto l: lights){
            red += l->getAmbient().red;
            green += l->getAmbient().green;
            blue += l->getAmbient().blue;
        }

        return Color(red, green, blue);
    }

    Color SumDifuusInf(const vector<Light*>& lights, const vector<double> &angles){
        double red = 0;
        double green = 0;
        double blue = 0;
        for (int i = 0; i < lights.size(); i++){
            Light* l = lights[i];

            if (angles[i] > 0){
                red += l->getDiffuse().red*angles[i];
                green += l->getDiffuse().green*angles[i];
                blue += l->getDiffuse().blue*angles[i];
            }

        }

        return Color(red, green, blue);
    }

    double getIntensity(Light* l, double angle){
        return (angle-l->spot_angle)/(1.0-l->spot_angle);
    }

    Color SumDifuus(const vector<Light*>& lights, const vector<double> &angles){
        double red = 0;
        double green = 0;
        double blue = 0;
        for (int i = 0; i < lights.size(); i++){
            Light* l = lights[i];

            double intensity = getIntensity(l, angles[i]);
            if (angles[i] >= l->spot_angle){
                red += l->getDiffuse().red*intensity;
                green += l->getDiffuse().green*intensity;
                blue += l->getDiffuse().blue*intensity;
            }

        }

        return Color(red, green, blue);
    }

    Color SumSpecular(const vector<Light*>& lights, const vector<double> &angles, double reflectie_index){
        double red = 0;
        double green = 0;
        double blue = 0;
        for (int i = 0; i < lights.size(); i++){
            Light* l = lights[i];
            if (angles[i] > 0){
                red += l->getSpectral().red*pow(angles[i], reflectie_index);
                green += l->getSpectral().green*pow(angles[i], reflectie_index);
                blue += l->getSpectral().blue*pow(angles[i], reflectie_index);
            }

        }

        return Color(red, green, blue);
    }

    Color DifuusSpecularLicht(const vector<Light*>& lights, const Vector3D& normaal, const Vector3D& point, const Color& difuus_ref, const Color& specular_ref, double reflectie_index){
        vector<double> angles;
        angles.reserve(lights.size());
        vector<double> anglesbeta;
        anglesbeta.reserve(lights.size());

        for (auto l: lights){
            if (!l->impact){
                angles.push_back(0);
                anglesbeta.push_back(0);
                continue;
            }

            Vector3D ld = l->location - point;
            Vector3D ld_copy = ld;
            ld_copy.normalise();

            double angle;
            Vector3D r;
            if (l->inf){
                angle = l->direction.x*-1*normaal.x+l->direction.y*-1*normaal.y+l->direction.z*-1*normaal.z;


                angles.push_back(0);
                r = 2*normaal*angle+l->direction;


            }else{
                angle = ld_copy.x*normaal.x+ld_copy.y*normaal.y+ld_copy.z*normaal.z;
                angles.push_back(angle);
                r = 2*normaal*angle-ld_copy;


            }

            Vector3D t = -point;

            r.normalise();
            t.normalise();
            double anglebeta = r.x*t.x+r.y*t.y+r.z*t.z;

            if(angle < 0){
                anglebeta = 0;
            }

            anglesbeta.push_back(anglebeta);

        }
        Color result = SumDifuus(lights, angles);
        Color result_spiegeld = SumSpecular(lights, anglesbeta, reflectie_index);
        return Color(result.red*difuus_ref.red+result_spiegeld.red*specular_ref.red,
                     result.green*difuus_ref.green+result_spiegeld.green*specular_ref.green,
                     result.blue*difuus_ref.blue+result_spiegeld.blue*specular_ref.blue);
    }
};
