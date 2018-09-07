#ifndef OBJECT_H
#define OBJECT_H

//#include "Scene.h"
//#include "Triangle.h"
//#include "Vector.h"

#include <cmath>

#define OBJECT_STATE_ACTIVE 101
#define OBJECT_STATE_PASSIVE 102
#define OBJECT_STATE_VISIBLE 103
#define OBJECT_STATE_INVISIBLE 104

class Object
{
private:
	
public:
	// 478
	int id; //Числовой идентификатор объекта
	const char *name;
	static int next_id; // айди следующего элемента
	int state; // Состояние объекта
	int attr; // Атрибуты объекта

	double avg_radius; // Средний радиус объекта для обнаружения столкновений
	double max_radius; // Максимальный радиус объекта

    Point center; // Положение объекта в мировых координатах
	Vector dir; // Единичный вектор направления
	Vector ux, uy, uz;
	// Локальные оси для отслеживания ориентации объекта (обновляются
	// автоматически при вызове функции поворота)

	std::list<Point> vertex_local; // список вершин с локальными координатами
	std::list<Point> vertex_trans; // список вершин с преобразованными мировыми координатами
	int vertices_size; // размер списков

	std::list<Triangle> polygons; // список полигонов
	int polygons_size; // количество полигонов

	static int get_id()
	{
		return next_id++;
	}

	Object()
	{
		id = get_id();
		state = OBJECT_STATE_PASSIVE | OBJECT_STATE_INVISIBLE;
		attr = 0;
		avg_radius = 0;
		max_radius = 0;
		center = Point();
		dir = Vector(); ux = Vector(); uy = Vector(); uz = Vector();
		vertex_local = {};
		vertex_trans = {};
		vertices_size = 0;
		polygons = {};
		polygons_size = {};
		name = "no name";
	}

	void updateRad()
	{
		if (vertex_local.size() < 1)
			return;

        double mx = max_radius * max_radius, curr = 0;
		double px, py, pz;
		avg_radius = 0;
		for (Point p : vertex_local)
		{
			px = p.x; py = p.y; pz = p.z;
            if ((curr = (px * px + py * py + pz * pz)) > mx)
				mx = curr;
			avg_radius += curr;
		}
		max_radius = sqrt(mx);
		avg_radius /= vertex_local.size();
	}

};

int Object::next_id = 0;

// разобраться, как упорядочивать и проверять упорядочивание через список вершин
// Предлагается через полярные координаты
// http://www.gamedev.ru/code/forum/?id=40728
// http://rsdn.org/forum/alg/3461405.hot

#endif
