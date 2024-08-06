

#include "tools2D.h"
#include "easy_image.h"
#include "Line2D.h"
#include "Color.h"
#include <list>
#include <string>
#include <iostream>
#include <cmath>
#include <limits>
#include "Figure.h"
#include "Z_buffer.h"
#include <tuple>
#include "BufferStorage.h"
#include <set>

using namespace std;
using Lines2D = list<Line2D*>;

namespace tool2D{

    img::EasyImage draw2DLines(const Lines2D &lines, const int size, const Color &bc, bool do_z_buf){
        vector<double> min_max = get_ranges(lines);
        pair<double, double> ranges = make_pair(min_max[1]-min_max[0],min_max[3]-min_max[2]);
        pair<double, double> image_size = get_image_size(ranges, size);


        double d = get_scale_factor(ranges, image_size, 0.95);
        use_scale_factor(lines, d);
        pair<double, double> deviation = get_deviation(image_size, min_max, d);
        use_add_factor(lines, deviation.first, deviation.second);


        img::EasyImage image(lround(image_size.first), lround(image_size.second));

        img::Color easy_bc(lround(bc.red*255), lround(bc.green*255), lround(bc.blue*255));


        image.clear(easy_bc);

        if (do_z_buf){
            Z_buffer z_buf((unsigned int) image_size.first, (unsigned int) image_size.second);
            for (Line2D* line: lines){
                img::Color easy_c(lround(line->color.red*255), lround(line->color.green*255), lround(line->color.blue*255));
                image.draw_line_zbuf(::lround(line->p1.x), ::lround(line->p1.y), line->z1, ::lround(line->p2.x), ::lround(line->p2.y), line->z2, easy_c, z_buf);
            }
        }else{
            for (Line2D* line: lines){
                img::Color easy_c(lround(line->color.red*255), lround(line->color.green*255), lround(line->color.blue*255));
                image.draw_line(::lround(line->p1.x), ::lround(line->p1.y), ::lround(line->p2.x), ::lround(line->p2.y), easy_c);
            }
        }

        return image;
    }

    tuple<double, pair<double, double>, pair<double, double>> get_scale_factor_all(const vector<Figure*> &figures, int size, double margin){
        vector<double> min_max = get_ranges(figures);
        pair<double, double> ranges = make_pair(min_max[1]-min_max[0],min_max[3]-min_max[2]);
        pair<double, double> image_size = get_image_size(ranges, size);
        double d = get_scale_factor(ranges, image_size, margin);
        pair<double, double> deviation = get_deviation(image_size, min_max, d);
        return make_tuple(d, deviation, image_size);

    }

    vector<double> get_ranges(const vector<Figure*> &figures){
        double min_x = numeric_limits<double>::max();
        double max_x = -numeric_limits<double>::max();
        double min_y = numeric_limits<double>::max();
        double max_y = -numeric_limits<double>::max();

        for (auto figure: figures){

            for (Vector3D& p : figure->points){

                if (p.x < min_x){
                    min_x = p.x;
                }

                if (p.x > max_x){
                    max_x = p.x;
                }

                if (p.y < min_y){
                    min_y = p.y;
                }

                if (p.y > max_y){
                    max_y = p.y;
                }

            }
        }


        vector<double> result = {min_x, max_x, min_y, max_y};
        return result;
    }


    img::EasyImage draw2DLines_z_buffering(const vector<Figure*> &figures, int size, const Color &bc){
        Lines2D lines;
        for (auto figure: figures){
            int index = 0;
            for (Face f: figure->faces){
                for (int i=0; i< f.points.size(); i++){
                    Line2D* l = new Line2D(figure->points[f.points[i]], figure->points[f.points[(i+1)%f.points.size()]], figure->ambient_color);
                    lines.push_back(l);
                }
                index += 1;
            }
        }

        img::EasyImage image = tool2D::draw2DLines(lines, size, bc, true);
        for (Line2D* l: lines){
            delete l;
        }


        return image;

    }

    img::EasyImage draw2DLines(const vector<Figure*> &figures, int size, const Color &bc){
        Lines2D lines;
        for (auto figure: figures){
            int index = 0;
            for (Face f: figure->faces){
                for (int i=0; i< f.points.size(); i++){
                    Line2D* l = new Line2D(figure->points[f.points[i]], figure->points[f.points[(i+1)%f.points.size()]], figure->ambient_color);
                    lines.push_back(l);
                }
                index += 1;

                //cout << l->p1.x << " " << l->p1.y << " " << l->p2.x << " " << l->p2.y << endl;


            }
        }

        img::EasyImage image = tool2D::draw2DLines(lines, size, bc, false);
        for (Line2D* l: lines){
            delete l;
        }


        return image;
    }

    vector<double> get_ranges(const Lines2D &lines){
        double min_x = numeric_limits<double>::max();
        double max_x = numeric_limits<double>::min();
        double min_y = numeric_limits<double>::max();
        double max_y = numeric_limits<double>::min();
        for (Line2D* line: lines){
            if (line->get_value_smallest_x() < min_x){
                min_x = line->get_value_smallest_x();
            }

            if (line->get_value_largest_x() > max_x){
                max_x = line->get_value_largest_x();
            }

            if (line->get_value_smallest_y() < min_y){
                min_y = line->get_value_smallest_y();
            }

            if (line->get_value_largest_y() > max_y){
                max_y = line->get_value_largest_y();
            }
        }
        vector<double> result = {min_x, max_x, min_y, max_y};
        return result;
    }

    pair<double, double> get_image_size(const pair<double, double> &ranges, int size){
        double max_range = max(ranges.first, ranges.second);
        double image_x = size*ranges.first/max_range;
        double image_y = size*ranges.second/max_range;
        return make_pair(image_x, image_y);

    }

    double get_scale_factor(const pair<double, double> &ranges, const pair<double, double> &images_size, double margin){
        double d = margin*images_size.first/ranges.first;
        return d;
    }

    void use_scale_factor(const Lines2D &lines, double d){
        for (Line2D* line: lines){
            line->p1.x = line->p1.x*d;
            line->p1.y = line->p1.y*d;
            line->p2.x = line->p2.x*d;
            line->p2.y = line->p2.y*d;

        }
    }

    pair<double, double> get_deviation(const pair<double, double> &image_size, const vector<double> &min_max, double d){
        double dc_x = d*(min_max[0]+min_max[1])/2.0;
        double dc_y = d*(min_max[2]+min_max[3])/2.0;

        double dx = image_size.first/2.0 - dc_x;
        double dy = image_size.second/2.0 - dc_y;

        return make_pair(dx, dy);
    }

    void use_add_factor(const Lines2D &lines, double dx, double dy){
        for (Line2D* line: lines){
            line->p1.x = line->p1.x+dx;
            line->p1.y = line->p1.y+dy;
            line->p2.x = line->p2.x+dx;
            line->p2.y = line->p2.y+dy;

        }
    }

    void doFigureProjection(Figure* figure, double d, const pair<double, double>& deviation){
        /*
         * Do projection
         * */
        figure->DoProjection(d);


        for (auto &p: figure->points){
            p.x += deviation.first;
            p.y += deviation.second;


        }
    }

    void determineFaceData(Figure* figure, double d){
        for (auto& face: figure->faces){
            Vector3D A = figure->points[face.points[0]];
            Vector3D B = figure->points[face.points[1]];
            Vector3D C = figure->points[face.points[2]];
            vector<Vector3D> temp_fases = {A, B, C};

            Vector3D u = B-A;
            Vector3D v = C-A;

            double w1 = u.y*v.z-u.z*v.y;
            double w2 = u.z*v.x-u.x*v.z;
            double w3 = u.x*v.y-u.y*v.x;
            double k = w1*A.x+w2*A.y+w3*A.z;
            face.dzdx = w1/(-d*k);
            face.dzdy = w2/(-d*k);
            if (k <= 0){
                face.normaal = Vector3D::point(w1, w2, w3);
            }else{
                face.normaal = -1*Vector3D::point(w1, w2, w3);
                face.inversed = true;
            }

        }
    }

    void faceActions(Figure* figure, Z_buffer& z_buf, BufferStorage& buf_store){
        int face_counter = 0;
        for (auto face: figure->faces){
            Vector3D A = figure->points[face.points[0]];
            Vector3D B = figure->points[face.points[1]];
            Vector3D C = figure->points[face.points[2]];

            vector<Vector3D> temp_fases = {A, B, C};

            double xG = (A.x+B.x+C.x)/3;
            double yG = (A.y+B.y+C.y)/3;
            double diff_zG = 1/(3*A.z)+1/(3*B.z)+1/(3*C.z);

            double dzdx = face.dzdx;
            double dzdy = face.dzdy;

            double y_min = min(A.y, B.y);
            y_min = min(C.y, y_min);

            double y_max = max(A.y, B.y);
            y_max = max(C.y, y_max);

            for (int y_i= lround(y_min+0.5); y_i <= lround(y_max-0.5); y_i++){
                vector<double> valid_x_i;
                valid_x_i.reserve(2);

                for (int i = 0; i<3; i++){
                    auto t1 = temp_fases[i%3];
                    auto t2 = temp_fases[(i+1)%3];

                    double x_1 = t1.x;
                    double x_2 = t2.x;
                    double y_1 = t1.y;
                    double y_2 = t2.y;

                    if ((y_i-y_1)*(y_i-y_2) <= 0 && y_1 != y_2){
                        double x_i = x_2 + (x_1-x_2)*(y_i-y_2)/(y_1-y_2);
                        valid_x_i.push_back(x_i);
                    }
                }
                if (valid_x_i.empty()){
                    continue;
                }

                int x_l = lround(min(valid_x_i[0], valid_x_i[1]) + 0.5);
                int x_r = lround(max(valid_x_i[0], valid_x_i[1]) - 0.5);
                for (int x_i = x_l; x_i<=x_r; x_i++){
                    double diff_zi = diff_zG+(x_i-xG)*dzdx+(y_i-yG)*dzdy;

                    if (diff_zi < z_buf.get(x_i, y_i)){
                        buf_store[x_i][y_i] = make_pair(figure, face_counter);
                        z_buf.set(x_i, y_i, diff_zi);
                    }

                }
            }

            face_counter += 1;
        }
    }

    img::EasyImage draw2DTriangle(const vector<Figure*> &figures, const Color &bc, double d, pair<double, double> deviation, pair<int, int> image_size, const vector<Light*>& lights){
        img::EasyImage image(image_size.first, image_size.second);
        Z_buffer z_buf((unsigned int) image_size.first, (unsigned int) image_size.second);
        BufferStorage buf_store((unsigned int) image_size.first, (unsigned int) image_size.second);
        img::Color easy_bc(lround(bc.red*255), lround(bc.green*255), lround(bc.blue*255));
        image.clear(easy_bc);
        for (auto& figure: figures){
            determineFaceData(figure, d);

            figure->DifuusLichtInf(lights);

            doFigureProjection(figure, d, deviation);

            faceActions(figure, z_buf, buf_store);
        }


        for (int x_i = 0; x_i<image.get_width(); x_i++){
            for (int y_i = 0; y_i<image.get_height(); y_i++){
                pair<Figure*, int> data_pair = buf_store[x_i][y_i];

                if (data_pair.first == nullptr){
                    continue;
                }

                Figure* figure = data_pair.first;
                Face face = figure->faces[data_pair.second];



                Vector3D original_point_eye = Vector3D::point(-(x_i-deviation.first)*(1.0/z_buf.get(x_i, y_i))/d, -(y_i-deviation.second)*(1.0/z_buf.get(x_i, y_i))/d, 1.0/z_buf.get(x_i, y_i));
                Vector3D original_point = figure->getOriginal(original_point_eye, true);

                if (figure->useTexture){
                    Color tex = figure->texture->getColor(original_point);
                    Color ambient_ref = tex;
                    ambient_ref.multiply(figure->ambient_intensiteit);
                    figure->ambient_color = ambient_ref;
                    figure->difuus_color = tex;
                    figure->spiegeld_color = tex;
                }


                if (figure->texture_coord || figure->cube_mapping){
                    double z_a = 1.0/figure->points[face.points[0]].z;
                    double z_b = 1.0/figure->points[face.points[1]].z;
                    double z_c = 1.0/figure->points[face.points[2]].z;;
                    Vector3D A = Vector3D::point(-(figure->points[face.points[0]].x-deviation.first)*(1.0/z_a)/d, -(figure->points[face.points[0]].y-deviation.second)*(1.0/z_a)/d, 1.0/z_a);
                    Vector3D B = Vector3D::point(-(figure->points[face.points[1]].x-deviation.first)*(1.0/z_b)/d, -(figure->points[face.points[1]].y-deviation.second)*(1.0/z_b)/d, 1.0/z_b);
                    Vector3D C = Vector3D::point(-(figure->points[face.points[2]].x-deviation.first)*(1.0/z_c)/d, -(figure->points[face.points[2]].y-deviation.second)*(1.0/z_c)/d, 1.0/z_c);
                    pair<Vector3D, Vector3D> vect = face.getUV(original_point_eye, A, B, C);
                    if (figure->fix_round){
                        face.normaal = vect.second;
                    }

                    if (!figure->cube_mapping){
                        Color tex = figure->texture_co->getAmbient(vect.first.x, vect.first.y);

                        Color ambient_ref = tex;
                        ambient_ref.multiply(figure->ambient_intensiteit);
                        figure->ambient_color = ambient_ref;
                        if (figure->texture_co->img_dif){
                            figure->difuus_color = figure->texture_co->getDifuus(vect.first.x, vect.first.y);
                        }

                    }

                }

                if (figure->cube_mapping){
                    Vector3D normaal_original = figure->getOriginal(face.normaal, false);
                    normaal_original.normalise();
                    Color tex = figure->cube_map->getColor(original_point, normaal_original)[0];
                    Color ambient_ref = tex;
                    ambient_ref.multiply(figure->ambient_intensiteit);
                    figure->ambient_color = ambient_ref;
                }

                for(auto light: lights){
                    bool b = true;
                    if (light->shadow){
                        b = light->same(original_point);
                    }

                    light->impact = b;


                }

                Color diffusSpec_color = LightTools::DifuusSpecularLicht(lights, face.normaal,
                                                                         original_point_eye,
                                                                         figure->difuus_color, figure->spiegeld_color, figure->reflectie_index);

                double red = figure->ambient_color.red + face.difuus_inf.red + diffusSpec_color.red;
                double green = figure->ambient_color.green + face.difuus_inf.green + diffusSpec_color.green;
                double blue = figure->ambient_color.blue + face.difuus_inf.blue + diffusSpec_color.blue;

                if (red > 1){
                    red = 1;
                }

                if (green > 1){
                    green = 1;
                }

                if (blue > 1){
                    blue = 1;
                }
                Color result_color = Color(red,green,blue);

                img::Color c(lround(result_color.red * 255), lround(result_color.green * 255), lround(result_color.blue * 255));
                image(x_i , y_i) = c;
            }
        }

        return image;
    }


}


