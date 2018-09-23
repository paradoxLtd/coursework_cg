#include "loader.h"

int Loader::load(Object *object, char* filename)
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return -1;
    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Point v;
            iss >> v.x; iss >> v.y; iss >> v.z;
            object->vertex_local.push_back(v);
        } else if (!line.compare(0, 3, "vn ")) {
            //iss >> trash >> trash;
            // Point n;
            //iss >> n.x; iss >> n.y; iss >> n.z;
            //object->normal.push_back(n);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Point uv;
            iss >> uv.x; iss >> uv.y; // в текстурах две координаты дыбы не создавать отдельно Poit 2d сохраняются в x,y z - пустой
            object->texture_coords.push_back(uv);
        }  else if (!line.compare(0, 2, "f ")) {

            Indexes indexes_vert; //
            Indexes indexes_text; //
            //Indexes indexes_norm;

            std::vector<int> tmp(3);
            iss >> trash;
            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
                for (int i=0; i<3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
                indexes_vert.ind.push_back(tmp[0]);
                indexes_text.ind.push_back(tmp[1]);
                //indexes_norm.ind.push_back(tmp[2]);
            }
            Triangle tr(object, indexes_vert, indexes_text);
            object->polygons.push_back(tr);
        }
    }

    object->updateRad();
    in.close();
    return NOERROR;
}

int Loader::loadAll(Scene scene, char** names, int names_size)
{
    ObjectList objects;
    int error = NOERROR;
    for(int i = 0; i < names_size; i++)
    {
        // НЕ ВЫНОСИТЬ ОБЪЯВЛЕНИЕ ПЕРЕМЕННОЙ ИЗ ЦИКЛА
        // иначе функция load будет переопределять
        // один и тот же объект все время
        Object object;
        error = load(&object, names[i]);
        if (error != NOERROR)
            break;
        objects.push(object);
    }
    if (error == NOERROR)
        scene.objects = objects;
    return error;
}
