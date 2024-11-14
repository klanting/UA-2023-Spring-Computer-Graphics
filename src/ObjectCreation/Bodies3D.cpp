//
// Created by tibov on 17/03/23.
//

#include "Bodies3D.h"
#include "../Figure/Color.h"
#include <math.h>
#include <algorithm>
#include <map>
namespace Bodies3D{
    Figure* CreateCubes(const Color &c){
        vector<Vector3D> points;

        points.push_back(Vector3D::point(1, -1, -1));
        points.push_back(Vector3D::point(-1, 1, -1));
        points.push_back(Vector3D::point(1, 1, 1));
        points.push_back(Vector3D::point(-1, -1, 1));
        points.push_back(Vector3D::point(1, 1, -1));
        points.push_back(Vector3D::point(-1, -1, -1));
        points.push_back(Vector3D::point(1, -1, 1));
        points.push_back(Vector3D::point(-1, 1, 1));

        vector<vector<int>> faces;

        faces.push_back({0, 4, 2, 6});
        faces.push_back({4, 1, 7, 2});
        faces.push_back({1, 5, 3, 7});
        faces.push_back({5, 0, 6, 3});
        faces.push_back({6, 2, 7, 3});
        faces.push_back({0, 5, 1, 4});

        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateIcosahedron(const Color &c){
        vector<Vector3D> points;


        for (int i=1; i <= 12; i++){
            if (i == 1){
                points.push_back(Vector3D::point(0, 0, sqrt(5)/2.0));
            }else if (2 <= i && i <= 6){
                double xi = cos((i-2)*2*M_PI/5.0);
                double yi = sin((i-2)*2*M_PI/5.0);
                double zi = 0.5;
                points.push_back(Vector3D::point(xi, yi, zi));
            }else if (7 <= i && i <= 11){
                double xi = cos(M_PI/5.0+(i-7)*2*M_PI/5.0);
                double yi = sin(M_PI/5.0+(i-7)*2*M_PI/5.0);
                double zi = -0.5;
                points.push_back(Vector3D::point(xi, yi, zi));
            }else{
                points.push_back(Vector3D::point(0, 0, -sqrt(5)/2.0));
            }
        }

        vector<vector<int>> faces;
        faces.push_back({0, 1, 2});
        faces.push_back({0, 2, 3});
        faces.push_back({0, 3, 4});
        faces.push_back({0, 4, 5});
        faces.push_back({0, 5, 1});
        faces.push_back({1, 6, 2});
        faces.push_back({2, 6, 7});
        faces.push_back({2, 7, 3});
        faces.push_back({3, 7, 8});
        faces.push_back({3, 8, 4});
        faces.push_back({4, 8, 9});
        faces.push_back({4, 9, 5});
        faces.push_back({5, 9, 10});
        faces.push_back({5, 10, 1});
        faces.push_back({1, 10, 6});
        faces.push_back({11, 7, 6});
        faces.push_back({11, 8, 7});
        faces.push_back({11, 9, 8});
        faces.push_back({11, 10, 9});
        faces.push_back({11, 6, 10});

        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateOctahedron(const Color &c){
        vector<Vector3D> points;
        points.push_back(Vector3D::point(1, 0, 0));
        points.push_back(Vector3D::point(0, 1, 0));
        points.push_back(Vector3D::point(-1, 0, 0));
        points.push_back(Vector3D::point(0, -1, 0));
        points.push_back(Vector3D::point(0, 0, -1));
        points.push_back(Vector3D::point(0, 0, 1));

        vector<vector<int>> faces;
        faces.push_back({0, 1, 5});
        faces.push_back({1, 2, 5});
        faces.push_back({2, 3, 5});
        faces.push_back({3, 0, 5});

        faces.push_back({1, 0, 4});
        faces.push_back({2, 1, 4});
        faces.push_back({3, 2, 4});
        faces.push_back({0, 3, 4});


        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateDodecahedron(const Color &c){
        vector<Vector3D> points;
        Figure* iso = CreateIcosahedron(c);
        for (auto face: iso->faces){
            Vector3D a1 = iso->points[face.points[0]];
            Vector3D a2 = iso->points[face.points[1]];
            Vector3D a3 = iso->points[face.points[2]];

            points.push_back(Vector3D::point((a1.x+a2.x+a3.x)/3.0, (a1.y+a2.y+a3.y)/3.0, (a1.z+a2.z+a3.z)/3.0));
        }

        vector<vector<int>> faces;
        faces.push_back({0, 1, 2, 3, 4});
        faces.push_back({0, 5, 6, 7, 1});
        faces.push_back({1, 7, 8, 9, 2});
        faces.push_back({2, 9, 10, 11, 3});
        faces.push_back({3, 11, 12, 13, 4});
        faces.push_back({4, 13, 14, 5, 0});
        faces.push_back({19, 18, 17, 16, 15});
        faces.push_back({19, 14, 13, 12, 18});
        faces.push_back({18, 12, 11, 10, 17});
        faces.push_back({17, 10, 9, 8, 16});
        faces.push_back({16, 8, 7, 6, 15});
        faces.push_back({15, 6, 5, 14, 19});

        delete iso;

        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateCone(const Color &c, int n, double height){
        vector<Vector3D> points;
        vector<vector<int>> faces;
        vector<int> base;
        for (int i =0; i<n; i++){
            double px = cos(2*M_PI*i/(double) n);
            double py = sin(2*M_PI*i/(double) n);

            points.push_back(Vector3D::point(px, py, 0));
            base.push_back(i);
        }

        points.push_back(Vector3D::point(0, 0, height));

        for (int i =0; i<n; i++){
            vector<int> temp;
            int i2 = (i+1)%n;
            int i3 = (int) points.size()-1;
            faces.push_back({i2, i3, i});
        }

        faces.push_back(base);
        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateCylinder(const Color &c, int n, double height, bool all){
        vector<Vector3D> points;
        vector<vector<int>> faces;
        vector<int> base;
        vector<int> roof;
        for (int i =0; i<n; i++){
            double px = cos(2*M_PI*i/(double) n);
            double py = sin(2*M_PI*i/(double) n);

            points.push_back(Vector3D::point(px, py, 0));
            points.push_back(Vector3D::point(px, py, height));
            base.push_back(i*2);
            roof.push_back(i*2+1);
        }



        for (int i =0; i<n; i++){
            vector<int> temp;
            int i2 = (i*2+2)%(n*2);
            faces.push_back({i2, i2+1, i*2+1 ,i*2});
        }

        if (all){
            faces.push_back(base);
            faces.push_back(roof);
        }

        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateSphere(const Color &c, int n){
        Figure* iso = CreateIcosahedron(c);
        for (int i=0; i<n; i++){
            vector<Face> new_faces;
            for (auto &face: iso->faces){

                Vector3D A = iso->points[face.points[0]];
                Vector3D B = iso->points[face.points[1]];
                Vector3D C = iso->points[face.points[2]];

                Vector3D D = Vector3D::point((A.x+B.x)/2.0, (A.y+B.y)/2.0, (A.z+B.z)/2.0);
                Vector3D E = Vector3D::point((C.x+B.x)/2.0, (C.y+B.y)/2.0, (C.z+B.z)/2.0);
                Vector3D F = Vector3D::point((A.x+C.x)/2.0, (A.y+C.y)/2.0, (A.z+C.z)/2.0);

                iso->points.push_back(D);
                iso->points.push_back(E);
                iso->points.push_back(F);

                new_faces.push_back(Face({face.points[1], (int) iso->points.size()-2, (int) iso->points.size()-3}));
                new_faces.push_back(Face({face.points[2], (int) iso->points.size()-1, (int) iso->points.size()-2}));
                new_faces.push_back(Face({(int) iso->points.size()-3, (int) iso->points.size()-2, (int) iso->points.size()-1}));

                face.points[0] = face.points[0];
                face.points[1] = (int) iso->points.size()-3;
                face.points[2] = (int) iso->points.size()-1;

            }

            for (auto &face : new_faces){
                iso->faces.push_back(face);
            }
        }

        for (int i=0; i<iso->points.size(); i++){
            iso->points[i].normalise();
        }

        return iso;
    }

    Figure* CreateTorus(const Color &c, int n, int m, double r, double R){
        vector<Vector3D> points;
        vector<vector<int>> faces;
        for (int i = 0; i<n; i++){
            for (int j = 0; j<m; j++){
                double u = 2*M_PI*i/(double)n;
                double v = 2*M_PI*j/(double)m;
                double x_uv = (R+r* cos(v))*cos(u);
                double y_uv = (R+r* cos(v))*sin(u);
                double z_uv = r* sin(v);
                points.push_back(Vector3D::point(x_uv, y_uv, z_uv));
            }
        }

        for (int i = 0; i<n; i++){
            for (int j = 0; j<m; j++){
                faces.push_back({i*m+j, ((i+1)%n)*m+j, ((i+1)%n)*m+(j+1)%m, i*m+(j+1)%m});
            }
        }


        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateTetrahedron(const Color &c){
        vector<Vector3D> points;
        vector<vector<int>> faces;

        points.push_back(Vector3D::point(1, -1, -1));
        points.push_back(Vector3D::point(-1, 1, -1));
        points.push_back(Vector3D::point(1, 1, 1));
        points.push_back(Vector3D::point(-1, -1, 1));

        faces.push_back({0, 1, 2});
        faces.push_back({1, 3, 2});
        faces.push_back({0, 3, 1});
        faces.push_back({0, 2, 3});

        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateMobiusStrip(const Color &c, int n, int m){
        vector<Vector3D> points;
        vector<vector<int>> faces;
        for (int i = 0; i<n; i++){
            for (int j = 0; j<m; j++){

                double u = 2*M_PI*i/(double)n;

                double dis = 2/((double)m-1);
                double v = dis*j -1;
                //double v = (4*j/(double)m)-1;
                double x_uv = (1+v/2.0*cos(u/2.0)) * cos(u);
                double y_uv = (1+v/2.0*cos(u/2.0)) * sin(u);
                double z_uv = v/2.0*sin(u/2.0);


                points.push_back(Vector3D::point(x_uv, y_uv, z_uv));
            }
        }


        for (int i = 0; i<n; i++){
            for (int j = 0; j<m; j++){
                if (i == n-1){
                    if (j < m-1){
                        faces.push_back({ ((i+1)%n)*m+j, (n-1)*m+m-(((i+1)%n)*m+j)-1, (n-1)*m+m-(((i+1)%n)*m+j)-2, ((i+1)%n)*m+j+1});
                    }
                    continue;
                }
                faces.push_back({i*m+j, ((i+1)%n)*m+j, ((i+1)%n)*m+(j+1)%m, i*m+(j+1)%m});
            }
        }


        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateUmbilical(const Color &c, int n, int m){
        vector<Vector3D> points;
        vector<vector<int>> faces;
        for (int i = 0; i<n; i++){
            for (int j = 0; j<m; j++){

                double dis_v = 2*M_PI/((double)m);
                double v = dis_v*j -M_PI;
                double dis_u = 2*M_PI/((double)n);
                double u = dis_u*i - M_PI;
                double x_uv = sin(u)*(7+cos(u/3.0-2.0*v)+2.0*cos(u/3.0+v));
                double y_uv = cos(u)*(7+cos(u/3.0-2.0*v)+2.0*cos(u/3.0+v));
                double z_uv = sin(u/3.0-2.0*v)+2.0*sin(u/3.0+v);
                points.push_back(Vector3D::point(x_uv, y_uv, z_uv));
            }
        }

        for (int i = 0; i<n-1; i++){
            for (int j = 0; j<m; j++){
                faces.push_back({i*m+j, ((i+1)%n)*m+j, ((i+1)%n)*m+(j+1)%m, i*m+(j+1)%m});
            }
        }

        for (int j = 0; j<m; j++){
            double dis_v = 2*M_PI/((double)m);
            double v = dis_v*j -M_PI;
            double dis_u = 2*M_PI/((double)n);
            double u = dis_u*n - M_PI;
            double x_uv = sin(u)*(7+cos(u/3.0-2.0*v)+2.0*cos(u/3.0+v));
            double y_uv = cos(u)*(7+cos(u/3.0-2.0*v)+2.0*cos(u/3.0+v));
            double z_uv = sin(u/3.0-2.0*v)+2.0*sin(u/3.0+v);
            points.push_back(Vector3D::point(x_uv, y_uv, z_uv));
        }

        int i = n-1;
        for (int j = 0; j<m; j++){
            faces.push_back({i*m+j, ((i+1)%(n+1))*m+j, ((i+1)%(n+1))*m+(j+1)%m, i*m+(j+1)%m});
        }




        Figure* fig = new Figure(points, faces, c);
        return fig;
    }

    Figure* CreateBuckyBall(const Color &c){
        vector<Vector3D> new_points;
        vector<vector<int>> new_faces;
        map<int, map<int, int>> change_pos;
        map<pair<int, int>, int> point_side;

        Figure* iso = CreateIcosahedron(c);

        for (auto face: iso->faces){
            Vector3D A = iso->points[face.points[0]];
            Vector3D B = iso->points[face.points[1]];
            Vector3D C = iso->points[face.points[2]];

            Vector3D D = Vector3D::point((2*A.x+B.x)/3, (2*A.y+B.y)/3, (2*A.z+B.z)/3);
            Vector3D E = Vector3D::point((A.x+2*B.x)/3, (A.y+2*B.y)/3, (A.z+2*B.z)/3);

            Vector3D F = Vector3D::point((2*B.x+C.x)/3, (2*B.y+C.y)/3, (2*B.z+C.z)/3);
            Vector3D G = Vector3D::point((B.x+2*C.x)/3, (B.y+2*C.y)/3, (B.z+2*C.z)/3);

            Vector3D H = Vector3D::point((2*C.x+A.x)/3, (2*C.y+A.y)/3, (2*C.z+A.z)/3);
            Vector3D I = Vector3D::point((C.x+2*A.x)/3, (C.y+2*A.y)/3, (C.z+2*A.z)/3);

            //D.normalise();
            //E.normalise();
            //F.normalise();
            //G.normalise();
            //H.normalise();
            //I.normalise();

            if (point_side.find(make_pair(face.points[0], face.points[1])) == point_side.end()){
                new_points.push_back(D); //size -6
            }
            if (point_side.find(make_pair(face.points[1], face.points[0])) == point_side.end()){
                new_points.push_back(E); //size -5
            }

            if (point_side.find(make_pair(face.points[1], face.points[2])) == point_side.end()){
                new_points.push_back(F); //size -4
            }

            if (point_side.find(make_pair(face.points[2], face.points[1])) == point_side.end()){
                new_points.push_back(G); //size -3
            }

            if (point_side.find(make_pair(face.points[2], face.points[0])) == point_side.end()){
                new_points.push_back(H); //size -2
            }
            if (point_side.find(make_pair(face.points[0], face.points[2])) == point_side.end()){
                new_points.push_back(I); //size -1
            }

            int change = 0;

            int H_index = (int) new_points.size()-2+change;
            if (point_side.find(make_pair(face.points[2], face.points[0])) != point_side.end()){
                H_index = point_side.at(make_pair(face.points[2], face.points[0]));
                change += 1;
            }

            int I_index = (int) new_points.size()-1+change;
            if (point_side.find(make_pair(face.points[0], face.points[2])) != point_side.end()){
                I_index = point_side.at(make_pair(face.points[0], face.points[2]));
                change += 1;
            }

            int F_index = (int) new_points.size()-4+change;
            if (point_side.find(make_pair(face.points[1], face.points[2])) != point_side.end()){
                F_index = point_side.at(make_pair(face.points[1], face.points[2]));
                change += 1;
            }

            int G_index = (int) new_points.size()-3+change;
            if (point_side.find(make_pair(face.points[2], face.points[1])) != point_side.end()){
                G_index = point_side.at(make_pair(face.points[2], face.points[1]));
                change += 1;
            }

            int D_index = (int) new_points.size()-6+change;
            if (point_side.find(make_pair(face.points[0], face.points[1])) != point_side.end()){
                D_index = point_side.at(make_pair(face.points[0], face.points[1]));
                change += 1;
            }

            int E_index = (int) new_points.size()-5+change;
            if (point_side.find(make_pair(face.points[1], face.points[0])) != point_side.end()){
                E_index = point_side.at(make_pair(face.points[1], face.points[0]));
                change += 1;
            }





            change_pos[face.points[0]].insert({D_index, I_index}); //LINK D to I for A

            change_pos[face.points[1]].insert({F_index, E_index}); //LINK F to E for B

            change_pos[face.points[2]].insert({H_index, G_index}); //LINK H to G for C

            new_faces.push_back({D_index, E_index, F_index,
                             G_index, H_index, I_index}); //D, E, F, G, H, I


            point_side[make_pair(face.points[0], face.points[1])] = D_index; // store D at 2/3A and 1/3B
            point_side[make_pair(face.points[1], face.points[0])] = E_index; // store E at 2/3B and 1/3A

            point_side[make_pair(face.points[1], face.points[2])] = F_index; // store F at 2/3B and 1/3C
            point_side[make_pair(face.points[2], face.points[1])] = G_index; // store G at 2/3C and 1/3B

            point_side[make_pair(face.points[2], face.points[0])] = H_index; // store H at 2/3C and 1/3A
            point_side[make_pair(face.points[0], face.points[2])] = I_index; // store I at 2/3A and 1/3C



        }


        for (auto entry: change_pos){
            int next = (*entry.second.begin()).second;
            vector<int> order = {};
            for (int i=0; i< entry.second.size(); i++){
                next = entry.second.at(next);
                order.push_back(next);
            }
            new_faces.push_back(order);

        }

        Figure* fig = new Figure(new_points, new_faces, c);


        return fig;

    }

    Figure* CreateMengerSponge(const Color &c){
        Figure* fig = CreateCubes(c);
        fig->points.push_back(Vector3D::point(-1, 0, -1));
        fig->points.push_back(Vector3D::point(-1, 0, 1));
        fig->points.push_back(Vector3D::point(1, 0, -1));
        fig->points.push_back(Vector3D::point(1, 0, 1));

        fig->points.push_back(Vector3D::point(0, -1, -1));
        fig->points.push_back(Vector3D::point(0, -1, 1));
        fig->points.push_back(Vector3D::point(0, 1, -1));
        fig->points.push_back(Vector3D::point(0, 1, 1));

        fig->points.push_back(Vector3D::point(-1, -1,  0));
        fig->points.push_back(Vector3D::point(-1, 1, 0));
        fig->points.push_back(Vector3D::point(1, -1, 0));
        fig->points.push_back(Vector3D::point(1, 1, 0));

        return fig;
    }

    void generateFractal(Figure* fig, vector<Figure*>& fractal_output, int nr_iterations, double scale, double original_scale, const string& type){
        if (nr_iterations == 0){
            fractal_output.push_back(fig);
            return;
        }
        for (int i=0; i <fig->points.size(); i++){
            auto p = fig->points[i];
            Figure* new_sub_figure;
            if (type == "Cube"){
                new_sub_figure = CreateCubes(fig->ambient_color);
            }else if(type == "Tetrahedron"){
                new_sub_figure = CreateTetrahedron(fig->ambient_color);
            } else if(type == "Icosahedron"){
                new_sub_figure = CreateIcosahedron(fig->ambient_color);
            }else if (type == "Octahedron"){
                new_sub_figure = CreateOctahedron(fig->ambient_color);
            }else if (type == "Dodecahedron"){
                new_sub_figure = CreateDodecahedron(fig->ambient_color);
            }else if (type =="BuckyBall"){
                new_sub_figure = CreateBuckyBall(fig->ambient_color);
            }else if (type =="MengerSponge"){
                new_sub_figure = CreateMengerSponge(fig->ambient_color);
            }


            vector<vector<int>> faces;
            new_sub_figure->Scalar(1/scale);
            new_sub_figure->reflections = fig->reflections;
            new_sub_figure->texture = fig->texture;
            new_sub_figure->useTexture = fig->useTexture;
            new_sub_figure->texture_co = fig->texture_co;
            new_sub_figure->texture_coord = fig->texture_coord;
            new_sub_figure->cube_mapping = fig->cube_mapping;
            new_sub_figure->cube_map = fig->cube_map;
            auto link_p = new_sub_figure->points[i];

            double diff_x = p.x-link_p.x;
            double diff_y = p.y-link_p.y;
            double diff_z = p.z-link_p.z;

            new_sub_figure->Translatie(Vector3D::point(diff_x, diff_y, diff_z));

            generateFractal(new_sub_figure, fractal_output, nr_iterations-1, scale*original_scale, scale, type);
        }

        delete fig;


    }

    void makeThick(Figure* fig, vector<Figure*>& fractal_output, double radius, int m, int n){
        fractal_output.pop_back();
        for (auto p: fig->points){
            Figure* bol = CreateSphere(fig->ambient_color, m);
            bol->FullRotScaleMove(0, 0, 0, radius, p);
            bol->reflections = fig->reflections;
            bol->useTexture = fig->useTexture;
            bol->texture = fig->texture;

            fractal_output.push_back(bol);
        }

        for (Face f: fig->faces){
            //f = fig->faces[2];
            for (int i=0; i< f.points.size(); i++){
                Vector3D p1 = fig->points[f.points[i]];
                Vector3D p2 = fig->points[f.points[(i+1)%f.points.size()]];

                Vector3D verschil = p2-p1;

                double length = verschil.length() / radius;

                double r = sqrt(pow(verschil.x, 2)+pow(verschil.y, 2)+pow(verschil.z, 2));
                double temp = verschil.z/r;

                double theta = atan2(verschil.y, verschil.x);

                double phi = acos(temp);

                Figure* cylinder = CreateCylinder(fig->ambient_color, n, length, false);

                cylinder->RotateX(phi*180/M_PI*-1);
                cylinder->RotateZ((theta-M_PI/2)*180/M_PI);

                cylinder->reflections = fig->reflections;
                cylinder->useTexture = fig->useTexture;
                cylinder->texture = fig->texture;

                cylinder->FullRotScaleMove(0, 0, 0, radius, p1);

                fractal_output.push_back(cylinder);


            }
            //break;
        }
    }


}