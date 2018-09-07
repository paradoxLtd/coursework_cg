#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Point;
class Vector;
class Options;

#include "Point.h"
#include "Vector.h"
#include "Options.h"
#include <iostream>

#define SIZE 4

class Action
{
public:
	virtual Vector apply(const Vector &v, Options &opt) = 0;
};

class Move : public Action
{
	Vector apply(const Vector &v, Options &opt) override;
};

class Rotate : public Action
{
private:
	Vector rotateX(const Vector &v, double angle);
	Vector rotateY(const Vector &v, double angle);
	Vector rotateZ(const Vector &v, double angle);
public:
	Vector apply(const Vector &v, Options &opt) override;
};

class Scale : public Action
{
	Vector apply(const Vector &v, Options &opt) override;
};

class Transformation
{
public:
	static Vector apply(const Vector &vector,
		Action &act, Options &opt);
	static Point apply(Point &point,
		Action &act, Options &opt);
};

class Matrix
{
public:
	double matrix[SIZE][SIZE];
	Matrix();
	Matrix(const Matrix &a);
	Matrix(Matrix &&a);
	Matrix(double m[SIZE][SIZE]);
	Matrix(Vector a);

	Vector asVector() const;
	
	static Matrix multiplicate(Matrix a, Matrix b);
	static Vector multiplicate(Vector v, Matrix m);
};

#endif

