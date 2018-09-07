#include "Transformation.h"

Matrix::Matrix()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(double m[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			this->matrix[i][j] = m[i][j];
		}
	}
}

Matrix::Matrix(const Matrix &m)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			this->matrix[i][j] = m.matrix[i][j];
		}
	}
}

Matrix::Matrix(Matrix &&m)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			this->matrix[i][j] = m.matrix[i][j];
		}
	}
}

Matrix::Matrix(Vector a)
{
	this->matrix[0][0] = a.x;
	this->matrix[0][1] = a.y;
	this->matrix[0][2] = a.z;
	this->matrix[0][3] = 1;

	for (int i = 1; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
}

Vector Matrix::asVector() const
{
	Vector ret;
	ret.x = this->matrix[0][0];
	ret.y = this->matrix[0][1];
	ret.z = this->matrix[0][2];
	return ret;
}

Matrix Matrix::multiplicate(Matrix a, Matrix b)
{
	Matrix ret;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				ret.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
			}
		}
	}
}

Vector Matrix::multiplicate(Vector v, Matrix m)
{
	Matrix vec_m(v);
	Matrix result(multiplicate(vec_m, m));
	Vector vec_v(multiplicate(vec_m, m).asVector()); //порядок слева вектор, справа матрица
	return vec_v;
}

Vector Move::apply(const Vector &vector, Options &opt)
{
	double x = opt[0], y = opt[1], z = opt[2];
	if (opt.inverse)
	{
		x *= -1; y *= -1; z *= -1;
	}

	double move_matrix[SIZE][SIZE] = 
	{
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ x, y, z, 1 }
	};

    Vector ret(Matrix::multiplicate(vector, move_matrix));
    return ret;
}

Vector Scale::apply(const Vector &vector, Options &opt)
{
	double x = opt[0], y = opt[1], z = opt[2];
	if (opt.inverse)
	{
		x = 1/x; y = 1/y; z = 1/z;
	}

	double scale_matrix[SIZE][SIZE] = 
	{
		{ x, 0, 0, 0 },
		{ 0, y, 0, 0 },
		{ 0, 0, z, 0 },
		{ 0, 0, 0, 1 }
	};
    Vector ret(Matrix::multiplicate(vector, scale_matrix));
    return ret;
}

Vector Rotate::rotateX(const Vector &vector, double angle)
{
	double rotate_matrix[SIZE][SIZE] = 
	{
		{ 1,	0,				0,			0 },
		{ 0,	cos(angle),		sin(angle), 0 },
		{ 0,	-sin(angle),	cos(angle), 0 },
		{ 0,	 0,				0,			1 }
	};
    Vector ret(Matrix::multiplicate(vector, rotate_matrix));
    return ret;
}

Vector Rotate::rotateY(const Vector &vector, double angle)
{
	double rotate_matrix[SIZE][SIZE] = 
	{
		{ cos(angle), 0,	 -sin(angle), 0 },
		{ 0,		  1,	 0,			  0 },
		{ sin(angle), 0,	 cos(angle),  0 },
		{ 0,		  0,	 0,			  1 }
	}; 
    Vector ret(Matrix::multiplicate(vector, rotate_matrix));
    return ret;
}

Vector Rotate::rotateZ(const Vector &vector, double angle)
{
	double rotate_matrix[SIZE][SIZE] = 
	{
		{  cos(angle), sin(angle), 0, 0 },
		{ -sin(angle), cos(angle), 0, 0 },
		{ 0,		   0,		   1, 0 },
		{ 0,		   0,		   0, 1 } 
	}; 
    Vector ret(Matrix::multiplicate(vector, rotate_matrix));
    return ret;
}

Vector Rotate::apply(const Vector &vector, Options &opt){
	int choose = (int)opt[0];
	double angle = opt[1];
	if (opt.inverse)
		angle *= -1;
	Vector v;

	switch (choose)
	{
	case AXIS_X:
	{
		v = rotateX(vector, angle);
		break;
	}
	case AXIS_Y:
	{
		v = rotateY(vector, angle);
		break;
	}
	case AXIS_Z:
	{
		v = rotateZ(vector, angle);
		break;
	}
	}
	return v;
}

Vector Transformation::apply(const Vector &vector,
	Action &act, Options &opt)
{
	return act.apply(vector, opt);
}

Point Transformation::apply(Point &point,
	 Action &act, Options &opt)
{
    Point p;
    Vector vk;
    Vector v(point, p);
	Vector after = act.apply(v, opt);
	return v.asPoint();
}
