#include "src/2DProjection/easy_image.h"
#include "src/Configuration/ini_configuration.h"
#include "src/LSystems/l_parser.h"

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include "src/Figure/Line2D.h"
#include "src/Figure/Color.h"
#include "src/2DProjection/tools2D.h"
#include "src/LSystems/LSystem.h"
#include "src/Figure/vector3d.h"
#include "src/Figure/Figure.h"
#include "src/ObjectCreation/Bodies3D.h"
#include <cmath>
#include "src/Clipping/Clipping.h"
#include "src/Lighting/Light.h"
#include "src/Lighting/LightTools.h"
#include "src/Lighting/ShadowMask.h"

#include "src/Configuration/obj_parser.h"
#include "src/CubeMapping/CubeMap.h"
#include "src/Textures/TextureCoord.h"
#include "src/InputType/FigureType.h"
#include "src/ObjectCreation/FigureFactory.h"
#include "src/Perspective/EyePerspective.h"
#include "src/Configuration/ConfigurationChecks.h"
#include "src/ConfigReaders/LightReader.h"
#include "src/ObjectCreation/LightCreator.h"


using namespace std;
using Lines2D = list<Line2D*>;

Figure* ReadObject2(const obj::OBJFile& ob){
    obj::MTLLibrary mtl;
    string mtl_path = ob.get_object().get_mtllib_file_name();
    ifstream mtl_file(mtl_path);
    mtl_file >> mtl;
    mtl_file.close();

    TextureCoord* t = new TextureCoord();

    obj::Material s = mtl["colorrect"];
    string ambient_map = s["map_Ka"].as_string_or_default("none");
    if (ambient_map != "none"){
        img::EasyImage ambient_img;
        ifstream ambient_file(ambient_map);
        ambient_file >> ambient_img;
        ambient_file.close();
        t->img_ambient = ambient_img;
    }


    string difuus_map = s["map_Kd"].as_string_or_default("none");
    if (difuus_map != "none"){
        img::EasyImage difuus_img;
        ifstream difuus_file(difuus_map);
        difuus_file >> difuus_img;
        difuus_file.close();
        t->img_difuus = difuus_img;
        t->img_dif = true;
    }

    ini::DoubleTuple d = s["Kd"].as_double_tuple_or_default({0, 0, 0});

    ini::DoubleTuple sp = s["Ks"].as_double_tuple_or_default({0, 0, 0});
    double ms = s["Ns"].as_double_or_default(1);



    vector<ini::DoubleTuple> v_group =  ob.get_object().get_vertexes();
    vector<ini::DoubleTuple> vt_group =  ob.get_object().get_texture_coordinates();
    vector<ini::DoubleTuple> vn_group =  ob.get_object().get_vertex_normals();
    vector<obj::Polygon> polygon_faces = ob.get_object().get_polygons();

    vector<Vector3D> points;
    vector<vector<int>> indexes;
    vector<vector<Vector3D>> uv;
    vector<vector<Vector3D>> v_normaal;
    for (auto v: v_group){
        Vector3D p = Vector3D::point(v[0], v[1], v[2]);
        points.push_back(p);
    }

    for (int j=0; j< polygon_faces.size(); j++){
        auto p = polygon_faces[j];
        vector<int> temp_index;
        vector<Vector3D> temp_uv;
        vector<Vector3D> temp_normaal;
        for (int i = 0; i<p.get_indexes().size(); i++){
            ini::DoubleTuple vertex_normaal_tup = vn_group[p.get_normal_indexes()[i]-1];
            ini::DoubleTuple texture_tup = vt_group[p.get_texture_indexes()[i]-1];
            Vector3D vertex_normaal = Vector3D::point(vertex_normaal_tup[0], vertex_normaal_tup[1], vertex_normaal_tup[2]);


            temp_index.push_back(p.get_indexes()[i]-1);
            temp_uv.push_back(Vector3D::point(texture_tup[0], texture_tup[1], 0));
            temp_normaal.push_back(vertex_normaal);
        }
        indexes.push_back(temp_index);
        uv.push_back(temp_uv);
        v_normaal.push_back(temp_normaal);
    }



    Figure* f = new Figure(points, indexes, uv, v_normaal, Color(255, 0, 0));
    f->texture_coord = true;
    f->texture_co = t;

    f->reflections.spectral_color = Color(sp[0], sp[1], sp[2]);
    f->reflections.diffuse_color = Color(d[0], d[1], d[2]);
    f->reflections.reflection_index = ms;

    return f;
}

CubeMap* ReadObject(const obj::MTLLibrary& mtl, double max){


    obj::Material s = mtl["colorrect"];
    string ambient_map = s["map_Ka"].as_string_or_die();

    img::EasyImage ambient_img;
    ifstream ambient_file(ambient_map);
    ambient_file >> ambient_img;
    ambient_file.close();


    CubeMap* c_map = new CubeMap(max);
    c_map->ambient_img = ambient_img;

    return c_map;

}

img::EasyImage generate_image(const ini::Configuration &configuration)
{

    string type = configuration["General"]["type"].as_string_or_die();
    int size = configuration["General"]["size"].as_int_or_die();
    ini::DoubleTuple bc_tuple = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    Color bc(bc_tuple[0], bc_tuple[1], bc_tuple[2]);

    bool clipping = configuration["General"]["clipping"].as_bool_or_default(false);

    bool light_support = type == "LightedZBuffering";
    bool z_buffering = type == "ZBufferedWireframe";
    bool triangulate = type == "ZBuffering" || light_support;



    bool shadow_support = configuration["General"]["shadowEnabled"].as_bool_or_default(false);
    int shadow_size = configuration["General"]["shadowMask"].as_int_or_default(0);


    if (type == "2DLSystem"){
        ini::ConfigReader cr = ini::ConfigReader(configuration["2DLSystem"]);

        string input_file = cr.getString("inputfile");
        Color c = cr.getColor("color");
        bool do_random = cr.getBool("stochastic");

        LParser::LSystem2D l_system;
        l_system.SetRandom(do_random);

        std::ifstream input_stream(input_file);
        input_stream >> l_system;
        input_stream.close();

        LSystem l(l_system, c);
        Lines2D lines = l.get_lines();
        img::EasyImage image = tool2D::draw2DLines(lines, size, bc, false);
        return image;
    }else if (type == "Wireframe" || type == "ZBufferedWireframe" || type == "ZBuffering" || type == "LightedZBuffering"){

        vector<Light*> Lights;

        Color a_int(0, 0, 0);
        if (light_support){
            int lights = configuration["General"]["nrLights"].as_int_or_die();
            Lights.reserve(lights);

            for (int i=0; i<lights; i++){

                ini::LightReader lr = ini::LightReader(configuration["Light"+to_string(i)]);
                Light* l = LightCreator::create(lr, shadow_support, shadow_size);

                Lights.push_back(l);
            }

            /*
             * Decide ambient color
             * */
            a_int = LightTools::SumAmbient(Lights);
        }


        int figure_amount = configuration["General"]["nrFigures"].as_int_or_die();
        ini::DoubleTuple eye_tup = configuration["General"]["eye"].as_double_tuple_or_die();
        Vector3D eye = Vector3D::point(eye_tup[0], eye_tup[1], eye_tup[2]);

        Vector3D view_dir;
        if (clipping){
            ini::DoubleTuple view_dir_tup = configuration["General"]["viewDirection"].as_double_tuple_or_die();
            view_dir = Vector3D::point(view_dir_tup[0], view_dir_tup[1], view_dir_tup[2]);
        }

        vector<Figure*> figures;


        for (int i=0; i<figure_amount; i++){

            ini::FigureReader fr = ini::FigureReader(light_support, configuration["Figure" + to_string(i)], a_int);

            auto section = configuration["Figure"+to_string(i)];

            bool has_object = fr.getBool("Object");
            bool do_cube_mapping = fr.getBool("cubeMapping");

            double cube_mapping_size = fr.getDouble("cubeMapSize", 1);

            if (has_object){

                string object_path = fr.getString("objectPath");
                obj::OBJFile ob;
                ifstream ob_file(object_path);
                ob_file >> ob;
                ob_file.close();
                Figure* f = ReadObject2(ob);
                figures.push_back(f);

                f->cube_mapping = do_cube_mapping;
                if (do_cube_mapping){
                    string mtl_path = fr.getString("cubeMapPath");
                    obj::MTLLibrary mtl;
                    ifstream mtl_file(mtl_path);
                    mtl_file >> mtl;
                    mtl_file.close();

                    CubeMap* c_map = ReadObject(mtl, cube_mapping_size);
                    f->cube_map = c_map;
                }


                f->reflections.reflection_index = 10;
                f->reflections.ambient_intensity = LightTools::SumAmbient(Lights);

                f->fix_round = fr.getBool("fixRound");

                continue;
            }

            string figure_type_string = fr.getString("type");

            FigureType figure_type = FigureType(figure_type_string);

            Reflections reflections = fr.getReflections();

            double rot_x = fr.getDouble("rotateX");
            double rot_y = fr.getDouble("rotateY");
            double rot_z = fr.getDouble("rotateZ");
            double scale = fr.getDouble("scale");

            Vector3D center = fr.getPoint("center");

            Figure* f = FigureFactory::create(figure_type, fr);
            f->FullRotScaleMove(rot_x, rot_y, rot_z, scale, center);

            f->reflections = reflections;

            ConfigurationChecks::checkTextureMapping(f, fr);

            if (figure_type.isFractal()){
                double fractal_scale;

                int it = section["nrIterations"].as_int_or_die();
                if (figure_type.getBaseType() != "MengerSponge"){
                    fractal_scale = section["fractalScale"].as_double_or_die();
                }else{
                    fractal_scale = 3;
                }

                Bodies3D::generateFractal(f, figures, it, fractal_scale, fractal_scale, figure_type.getBaseType());
            }else{
                figures.push_back(f);

            }

            f->cube_mapping = do_cube_mapping;
            if (do_cube_mapping){
                string mtl_path = fr.getString("cubeMapPath");
                obj::MTLLibrary mtl;
                ifstream mtl_file(mtl_path);
                mtl_file >> mtl;
                mtl_file.close();

                CubeMap* c_map = ReadObject(mtl, cube_mapping_size);
                f->cube_map = c_map;
            }

            if(figure_type.isThick()){
                double thick_scale = fr.getDouble("radius");
                int m = fr.getInt("m");
                int n = fr.getInt("n");
                Bodies3D::makeThick(f, figures, thick_scale, m, n);
            }


        }
        /**
         * projectie hier
         * */

        for (Figure* f: figures) {
            if (triangulate) {
                f->Triangulate();
            }
        }


        if (shadow_support){
            for (auto light: Lights){
                light->shadow_transform(figures);
            }
        }

        EyePerspective* eye_position = new EyePerspective{eye};
        for (Figure* f: figures){

            f->setEye(eye_position);

            if (clipping){
                f->EyePerspectifTransform(eye, view_dir);
                double hfov = M_PI/180*configuration["General"]["hfov"].as_double_or_die();
                double dNear = configuration["General"]["dNear"].as_double_or_die();
                double dFar = configuration["General"]["dFar"].as_double_or_die();
                double dRight = dNear * tan(hfov/2.0);
                double aspect_ratio = configuration["General"]["aspectRatio"].as_double_or_die();
                double dTop = dRight/aspect_ratio;

                Clipping::clipNear(f, dNear);
                Clipping::clipFar(f, dFar);

                Clipping::clipRight(f, dNear, dRight);
                Clipping::clipLeft(f, dNear, dRight*-1);


                Clipping::clipTop(f, dNear, dTop);
                Clipping::clipBottom(f, dNear, dTop*-1);

            }else{
                f->EyePerspectifTransform(eye);
            }

            f->EyeTransformFace();
            f->DoProjection(1);
        }



        for (auto light: Lights){
            if (clipping){
                light->EyePerspectifTransform(eye, view_dir);
            }else{
                light->EyePerspectifTransform(eye);
            }

        }

        img::EasyImage image;
        if (triangulate){
            tuple<double, pair<double, double>, pair<double, double>> relocate_data = tool2D::get_scale_factor_all(figures, size, 0.95);

            double d = get<0>(relocate_data);
            pair<double, double> deviation = get<1>(relocate_data);

            pair<double, double> image_size = get<2>(relocate_data);
            for (auto figure: figures){
                figure->UndoProjection(1);
            }

            image = tool2D::draw2DTriangle(figures, bc, d, deviation, image_size, Lights);

        }else{
            if (z_buffering){
                image = tool2D::draw2DLines_z_buffering(figures, size, bc);
            }else{
                image = tool2D::draw2DLines(figures, size, bc);
            }

        }

        for (auto f: figures){
            delete f;
        }

        return image;


    }


	return img::EasyImage();
}

int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                std::vector<std::string> args = std::vector<std::string>(argv+1, argv+argc);
                if (args.empty()) {
                        std::ifstream fileIn("filelist");
                        std::string filelistName;
                        while (std::getline(fileIn, filelistName)) {
                                args.push_back(filelistName);
                        }
                }
                for(std::string fileName : args)
                {
                        std::cout << "checking file: " << fileName << std::endl;
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(fileName);
                                if (fin.peek() == std::istream::traits_type::eof()) {
                                    std::cout << "Ini file appears empty. Does '" <<
                                    fileName << "' exist?" << std::endl;
                                    continue;
                                }
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << fileName << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
