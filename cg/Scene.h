#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "Camera.h"
#include "Transformation.h"
#include <list>

// плоскость
class Scene
{
private:
public:
    //HDC hdc;
	double A, B, C, D;
	std::list<Object> objects;
	Camera camera;

	int ar;  // соотношение длины и ширины
	int fov; // поле зрения, всегда 90
	int d;   // расстояние до плоскости проекции

    Scene()
    {
		ar = 1;
		fov = 90;
		d = 1;
	}

	// 430
	void localToWorld()
	{
		Point point_tmp;
		for (Object obj : objects)
		{
			obj.vertex_trans.clear();
			for (Point point : obj.vertex_local)
			{
				point_tmp = Point(point.x + obj.center.x,
					point.y + obj.center.y, point.z + obj.center.z, point.w);
				obj.vertex_trans.push_back(point_tmp);
			}
		}
	}

	// 435
	void worldToCam()
	{
		Rotate rotate;
		RotateOptions ropX(AXIS_X, camera.ang_x, true);
		RotateOptions ropY(AXIS_Y, camera.ang_y, true);
		RotateOptions ropZ(AXIS_Z, camera.ang_z, true);
	
		MoveOptions mop(camera.point, true);
		Move move;

		for (Object obj : objects)
		{
			for (Point point : obj.vertex_trans)
			{
				point = Point(point.x - camera.point.x,
					point.y - camera.point.y, point.z - camera.point.z, point.w);
				
				//YXZ поворот 437
				Transformation::apply(point, move, mop);
				Transformation::apply(point, rotate, ropY);
				Transformation::apply(point, rotate, ropX);
				Transformation::apply(point, rotate, ropZ);
			}
		}
		Transformation::apply(camera.point, move, mop);
		Transformation::apply(camera.point, rotate, ropY);
		Transformation::apply(camera.point, rotate, ropX);
		Transformation::apply(camera.point, rotate, ropZ);
	}

	//450
	// d - расстояние до камеры
	/*
	void camToAxonoetric(int d = 1)
	{
		ar ...
		for (Object obj : objects)
		{
			for (Point point : obj.vertex_trans)
			{
				point.x = d * point.x / point.z;
				point.y = d * point.y / point.z;
			}
		}
	}
	*/

};

#endif
