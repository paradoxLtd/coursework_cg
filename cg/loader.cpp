#include "loader.h"
#include "qDebug"

//Хранить объекты надо в папке сборки ../cgg/build-cg.../objs/my_file.obj
int Loader::_load(Object *object, const char* filename)
{
    std::ifstream in;

    // https://ru.stackoverflow.com/questions/414690/Как-узнать-директорию-исполняемого-файла-в-windows
    char current_work_dir[FILENAME_MAX];
    _getcwd(current_work_dir, sizeof(current_work_dir));

    // http://qaru.site/questions/124663/how-to-concatenate-two-strings-in-c
    char rfilename[sizeof(current_work_dir) +
            sizeof(filename) + sizeof("\\objs\\")];
    strcpy (rfilename, current_work_dir) ;
    strcat (rfilename, "\\objs\\") ;
    strcat (rfilename, filename) ;
    in.open(rfilename, std::ifstream::in);
    qDebug()  << rfilename;
    if (in.fail())
    {
        return -1;
    }
    std::string line;

    std::cout << "\nlook at me";

    // для сохранения индексов точки для массива вершин
    int index, a, b, c, a1, b1, c1, a2, b2, c2;
    // максив индексов вершин для полигона
    Indexes indexes_texture;
    Indexes indexes_vertex;
    // Для вспомогательных символов
    char trash;
    // Поскольку напрямую закидывать в объект нельзя
    // Сделаем это через доп. векторы
    std::vector<Point> vertex;
    //std::vector<Vector> normal;
    std::vector<Point> texture;
    std::vector<Triangle> polygons;

    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        if (!line.compare(0, 2, "v ")) {
            // считываем вспомогательный символ 'v'
            iss >> trash;
            Point v;
            iss >> v.x >> v.y >> v.z;
            vertex.push_back(v);
        }
        else if (!line.compare(0, 3, "vn "))
        {
            //iss >> trash >> trash;
            // Point n;
            //iss >> n.x >> n.y >> n.z;
            //normal.push_back(n);
        }
        else if (!line.compare(0, 3, "vt "))
        {
            iss >> trash >> trash;
            Point uv;

            // в текстурах две координаты
            iss >> uv.x >> uv.y;

            // дыбы не создавать отдельно Point 2d
            // сохраняются в x,y z - пустой
            texture.push_back(uv);
        }
        else if (!line.compare(0, 2, "f "))
        {
            // считываем вспомогательное 'f'
            iss >> trash;

            // очистка списка индексов вершин
            indexes_texture.clear();
            indexes_vertex.clear();

            // запись элементов в массив вершин
            // существует 2 записи: 1/2/3 3/2/1 5/3/1
            // и 1 2 3, в первом случае перечислены 3 массива
            // индексов из трех элементов, надо убирать '/'.
            // Во втором задан только список верши, зато
            // его размер динамический
            if (std::regex_search (line, std::regex("/") ))
            {
                // для считывания формата 1/2/3 4/5/6 7/8/9
                iss >> a >> trash >> b >> trash >> c;
                iss >> a1 >> trash >> b1 >> trash >> c1;
                iss >> a2 >> trash >> b2 >> trash >> c2;
                indexes_vertex = Indexes(a,a1,a2);
                indexes_texture = Indexes(b,b1,b2);
            }
            else
            {
                // Для считывания формата 1 2 3 4 5 6 7
                while (iss >> index)
                {
                    indexes_vertex.push(index);
                    // список координат текстур по сути отсутсвует
                    indexes_texture.push(index);
                }
            }

            // сохранение полигона в список объекта
            polygons.push_back(
                        Triangle(object,
                                 indexes_vertex,
                                 indexes_texture));
        }
    }
    object->texture_coords = texture;
    object->vertex_trans = texture;
    //object->normal = normal;
    object->vertex_local = vertex;
    object->vertex_trans = vertex;
    object->polygons = polygons;
    object->state = OBJECT_STATE_ACTIVE;
    object->updateRad();
    in.close();
    return 0;
}

int Loader::_loadAll(Scene &scene, std::vector<std::string> names)
{
    int error = 0;

    ObjectList objects;

    for (std::string name : names)
    {
        // НЕ ВЫНОСИТЬ ОБЪЯВЛЕНИЕ ПЕРЕМЕННОЙ ИЗ ЦИКЛА
        // иначе все объекты будут с одним id
        Object object;
        error = load(&object, name);
        if (error != 0)
            break;
        objects.push(object);
    }
    if (error == 0)
        scene.objects = objects;

    return error;
}

int Loader::load(Object *object, const char* filename)
{
    return _load(object, filename);
}

int Loader::load(Object *object, std::string filename)
{
    return _load(object, filename.c_str());
}

int Loader::loadAll(Scene &scene, std::vector<std::string> names)
{
    return _loadAll(scene, names);
}
