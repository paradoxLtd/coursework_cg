#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <QColor>

#define RGB_IDX 3

// с. 660
class Material
{
public:
    Material() = delete;
    Material(int state, int id, std::string name, QColor color,
             double ka, double kd, double ks, std::string texture_name);
    ~Material() = default;

    int state; // Состояние, скорее всего не нужно
    int id; // Индекс в таблице материалов

    std::string name; // Название
    int attr; //Атрибуты, режимы затенения и т. д.

    QColor color; //Будем пока использовать для цвета qcolor
    double ka, kd, ks; // Коэффициенты общего, диффузного и зеркального отражения

    QColor ra, rd, rs; // Предварительно вычисленные произведения color на ka...

    std::string texture_name; //Файл текстуры

};

#endif // MATERIAL_H
