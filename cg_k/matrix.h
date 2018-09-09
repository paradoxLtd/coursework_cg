#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include "initializer_list"
#define SIZE 4

class Matrix
{
public:
    double matrix[SIZE][SIZE];
    Matrix();
    Matrix(const Matrix &a);
    Matrix(Matrix &&a);
    Matrix(double m[SIZE][SIZE]);
    Matrix(Vector a);

    Matrix & operator = (const Matrix &m);
    Matrix & operator=(Matrix&& m);

    Vector asVector() const;
    void eye();

    static Matrix multiplicate(Matrix a, Matrix b);
    static Vector multiplicate(Vector v, Matrix m);
    static Matrix inv(Matrix a);
};


#endif // MATRIX_H
