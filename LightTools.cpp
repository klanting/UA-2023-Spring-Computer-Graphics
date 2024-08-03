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
            red += l->ambient.red;
            green += l->ambient.green;
            blue += l->ambient.blue;
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
                red += l->difuus_infinity.red*angles[i];
                green += l->difuus_infinity.green*angles[i];
                blue += l->difuus_infinity.blue*angles[i];
            }

        }

        return Color(red, green, blue);
    }

    Color SumDifuus(const vector<Light*>& lights, const vector<double> &angles){
        double red = 0;
        double green = 0;
        double blue = 0;
        for (int i = 0; i < lights.size(); i++){
            Light* l = lights[i];
            if (angles[i] >= l->spot_angle){
                red += l->difuus.red*(angles[i]-l->spot_angle)/(1.0-l->spot_angle);
                green += l->difuus.green*(angles[i]-l->spot_angle)/(1.0-l->spot_angle);
                blue += l->difuus.blue*(angles[i]-l->spot_angle)/(1.0-l->spot_angle);
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
                red += l->spiegelend.red*pow(angles[i], reflectie_index);
                green += l->spiegelend.green*pow(angles[i], reflectie_index);
                blue += l->spiegelend.blue*pow(angles[i], reflectie_index);
            }

        }

        return Color(red, green, blue);
    }

    Color DifuusSpecularLicht(const vector<Light*>& lights, const Vector3D& normaal, const Vector3D& point, const Color& difuus_ref, const Color& specular_ref, double reflectie_index, bool normaal_inversed){
        vector<double> angles;
        vector<double> anglesbeta;
        Vector3D normaal_copy = normaal;



        normaal_copy.normalise();
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
                angle = l->direction.x*-1*normaal_copy.x+l->direction.y*-1*normaal_copy.y+l->direction.z*-1*normaal_copy.z;


                angles.push_back(0);
                r = 2*normaal_copy*angle+l->direction;


            }else{
                angle = ld_copy.x*normaal_copy.x+ld_copy.y*normaal_copy.y+ld_copy.z*normaal_copy.z;
                angles.push_back(angle);
                r = 2*normaal_copy*angle-ld_copy;


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
