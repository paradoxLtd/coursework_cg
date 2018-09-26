#include "matrix.h"
#include <cmath>

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

Matrix::Matrix(std::vector<std::vector<double>> matr)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            this->matrix[i][j] = matr[i][j];
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

Matrix::Matrix(Point a)
{
    std::cout << "i see " << a;
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
    this->matrix[0][0] = a.x;
    this->matrix[0][1] = a.y;
    this->matrix[0][2] = a.z;
    this->matrix[0][3] = a.w;
}

Matrix::Matrix(Vector a)
{
    *this = Matrix(a.asPoint());
}

Matrix& Matrix::operator = (const Matrix &m)
{
    std::copy(&m.matrix[0][0],
            &m.matrix[0][0] + SIZE * SIZE,
            &this->matrix[0][0]);
    return *this;
}

Matrix & Matrix::operator=(Matrix&& m)
{
    std::move(&m.matrix[0][0],
            &m.matrix[0][0] + SIZE * SIZE,
            &this->matrix[0][0]);
    return *this;
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
    return ret;
}

Vector Matrix::multiplicate(Vector v, Matrix m)
{
    Matrix vec_m = Matrix(v);
    std::cout << "i create it " << vec_m << "cause i" << v;
    Vector vec_v(multiplicate(vec_m, m).asVector()); //порядок слева вектор, справа матрица
    return vec_v;
}

Point Matrix::multiplicate(Point p, Matrix m)
{
    Matrix vec_m(p);
    Vector vec_v(multiplicate(vec_m, m).asVector()); //порядок слева вектор, справа матрица
    return vec_v.asPoint();
}

Matrix Matrix::inv(Matrix a)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            a.matrix[i][j] *= -1;
        }
    }
    return a;
}

void Matrix::eye()
{
    double m[SIZE][SIZE] =
    {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };

    std::copy(
                &m[0][0],
            &m[0][0] + SIZE * SIZE,
            &this->matrix[0][0]);
}

std::ostream& operator<<(std::ostream& os,
                                const Matrix& matrix)
{
    os << "\nMatrix:";
    for (int i = 0; i < SIZE; i++)
    {
       os << "\n";
       for (int j = 0; j < SIZE; j++)
       {
           os << matrix.matrix[i][j] << "; ";
       }
    }
    return os;
}
