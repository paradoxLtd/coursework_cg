#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <sstream>

#include "Transformation.h"
#include "Object.h"
#include "Bit.h"
#include "resource.h"
#include "Scene.h"

// Маска извлечения цвета в формате RGB или в виде индекса
#define PLX_RGB_MASK 0x8000
// Маска извлечения режима затенения
#define PLX_SHADE_MODE_MASK 0x6000
// Маска задания двусторонности
#define PLX_2SIDED_MASK 0x1000
#define PW_COLOR_MASK 0x0fff // xxxxrrrrggggbbbb,
                             // no 4 бита на каждый канал RGB
                             // xxxxxxxximiiii - 8-битовый
                             // индекс в индексном режиме
                             // Флаги сравнения, использующиеся после наложения маски
                             // Цветовой режим многоугольника
                             // Цвет многоугольника задается в формате RGB
#define PLX_COLORJ40DE_RGB_FLAG 0x8000
    // 8-битовый индексный цвет многоугольника
#define PLX_COLOR_MODEJNDEXED_FLAG 0x0000
    // Флаги двусторонности
    // Многоугольник двусторонний
#define PU_2SIDED_FLAG 0x1000
    // Многоугольник односторонний
#define PLX_1SIDED_FUG OxOOOO
    // Режим затенения многоугольника
    // Постоянное затенение
#define PLX_SHADE_MODE_PURE_FLAG 0x0000
    // Плоское затенение
#define PU_SHADE_MODE_FLAT_FLAG 0x2000
    // Затенение по Гуро
#define PLX_SHADE_MODE_GOURAUD_FLAG 0x4000
    // Затенение по Фонгу
#define PW_SHADE_MODE_PHONG_FUG 0x6000

/*
class Loader
{
    // Эта небольшая вспомогательная функция считывает
    // поочередно по одной строке из файла в формате PLG и
    // пропускает комментарии и пустые строки. Функция
    // возвращает значащие строки обрабатываемого файла или
    // значение NULL, если этот файл пуст
    char *getLine(char* buffer, int maxLength,
        FILE *f)
    {
        int length, i;
        while (1)
        {
            if (!fgets(buffer, maxLength, f))
                return NULL;

            // Удаляем пробелы
            for (length = strlen(buffer), i = 0;
                isspace(buffer[i]); i++) {
            };

            // Проверяем не являеится ли строка пустой
            if ((i >= length) || (buffer[i] == '#'))
                continue;

            // Теперь понятно, что считанная строка
            // является значащей
            return (&buffer[i]);
        }
    }

    void message(char *filename, const char* text,
        const int err)
    {
        std::cout << "\n Ошибка в файле " <<
            filename << " при попытке " << text <<
            ". Код ошибки:" << err;
    }

    // посылать объект как Object obj; &obj;
    int load(Object *object, char* filename, ScaleOptions sop,
        RotateOptions rop, MoveOptions mop)
    {
        FILE *f;
        char buffer[256];
        char *token_string; // указатель на строку

        // Инициализация объекта
        object->state = OBJECT_STATE_ACTIVE | OBJECT_STATE_VISIBLE;
        object->center = Point(mop);

        // Открываем файл
        if (!(f = fopen(filename, "r")))
        {
            message(filename, "открыть файл",
                ERROR_NO_FILE);
            return ERROR_NO_FILE;
        }

        // Извлекаем первую лексему, которая должна быть
        // дескриптором объекта
        if (!(token_string = getLine(buffer, 255, f)))
        {
            message(filename, "получить дескриптор вершины",
                ERROR_WRONG_VERTEX_DESCRIPTOR);
            return ERROR_WRONG_VERTEX_DESCRIPTOR;
        }

        // Анализируем строку с информацией объекта
        sscanf(token_string, "%s %d %d",
            object->name,
            &object->vertices_size,
            &object->polygons_size);

        // Проверка на корректность количества вершин
        if (object->vertices_size < 1)
        {
            message(filename, "получить количество вершин",
                ERROR_WRONG_AMOUNT_OF_VERTEX);
            return ERROR_WRONG_AMOUNT_OF_VERTEX;
        }

        // Проверка на корректность количества полигонов
        if (object->polygons_size < 1)
        {
            message(filename, "получить количество полигонов",
                ERROR_WRONG_AMOUNT_OF_POLYGON);
            return ERROR_WRONG_AMOUNT_OF_POLYGON;
        }

        // Переменные для хранения считанных координат вершины
        double v_x, v_y, v_z;

        // Объект класса действия(масшитабирования)
        Scale scale;

        // Загружаем список вершин
        for (int v = 0; v < object->vertices_size; v++)
        {
            //Извлекаем очередную вершину
            if (!(token_string - getLine(buffer, 255, f)))
            {
                message(filename, "загрузить вершину",
                    ERROR_WRONG_VERTEX);
                return ERROR_WRONG_VERTEX;
            }

            // Записываем координаты
            sscanf(token_string, "%f %f %f",
                &v_x, &v_y, &v_z);

            // Помещаем в массив вершин объекта
            object->vertex_local.push_back(
                Point(v_x, v_y, v_z, 1));

            // Выполняем масштабирование вершины
            Transformation::apply(object->vertex_local.back(), scale, sop);
        }

        // Устанавливаем максимальный и средний радиусы
        object->updateRad();

        // дескриптор поверхности
        int surface_desc = 0;

        // количество вершин в многоугольнике, всегда 3
        int poly_num_verts = 0;

        // хранит считанную строку с информацией полигона
        char tmp_string[8];

        // переменные для хранения индексов
        int index1, index2, index3;

        // Получаем информацию о каждом полигоне
        for (int pol = 0; pol < object->polygons_size; pol++)
        {
            // Извлекаем строку информации
            if (!(token_string = getLine(buffer, 255, f)))
            {
                message(filename, "получить дескриптор полигона",
                    ERROR_WRONG_POLYGOM_DESCRIPTOR);
                return ERROR_WRONG_POLYGOM_DESCRIPTOR;
            }

            // Записываем дескриптор, количество вершин и 3 индекса
            sscanf(token_string, "%s %d %d %d %d", tmp_string,
                &poly_num_verts, &index1, &index2, &index3);

            // Проверяем, что полигон имеет 3 вершины
            if (poly_num_verts != 3)
            {
                message(filename, "определить количество вершин полигона",
                    ERROR_TOO_MUCH_VERTEX_IN_POLYGON);
                return ERROR_TOO_MUCH_VERTEX_IN_POLYGON;
            }

            // Проверяем, что индексы корректные
            if ((index1 < 0) || (index2 < 0) || (index3 < 0))
            {
                message(filename, "получить индексы",
                    ERROR_WRONG_INDEX);
                return ERROR_WRONG_INDEX;
            }

            // Создаем полигон и помещаем  ссылку на объект и 3 индекса
            object->polygons.push_back(
                Triangle(object, index1,
                    index2, index3));

            // Поскольку дескриптор поверхности может быть в
            // шестнадцатеричном формате (при этом в его начале
            // стоят символы "Ох"), нужно провести проверку
            if (
                (tmp_string[0] == '0')
                &&
                (toupper(tmp_string[1]) == 'X')
                )
                sscanf(tmp_string, "%x", &surface_desc);
            else
                surface_desc = atoi(tmp_string);

            if ((surface_desc & PLX_2SIDED_MASK))
            {
                SET_BIT(object->polygons.back().attr,
                    POLY4DV1_ATTR_2SIDED);
            }
            else
            {
                SET_BIT(object->polygons.back().attr,
                    POLY4DV1_ATTR_1SIDED);
            }//else

        }
    }
};
*/

class Loader
{
public:
    void message(char *filename, const char* text,
        const int err)
    {
        std::cout << "\n Ошибка в файле " <<
            filename << " при попытке " << text <<
            ". Код ошибки:" << err;
    }

    int load(Object *object, char* filename)
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

    // Загрузить все объекты на сцену, names - список имен
    int loadAll(Scene scene, char** names, int names_size)
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
};

#endif // LOADER_H
