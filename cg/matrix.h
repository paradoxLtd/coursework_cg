#ifndef MATRIX_H
#define MATRIX_H
#define SIZE 4
#include "vector.h"

#include <vector>
class Matrix
{
public:
    double matrix[SIZE][SIZE];
    Matrix();
    Matrix(const Matrix &a);
    Matrix(Matrix &&a);
    Matrix(double m[SIZE][SIZE]);
    Matrix(std::vector<std::vector<double>> matr);
    Matrix(Vector a);
    Matrix(Point a);

    Matrix & operator = (const Matrix &m);
    Matrix & operator=(Matrix&& m);

    Vector asVector() const;
    void eye();

    static Matrix multiplicate(Matrix a, Matrix b);
    static Vector multiplicate(Vector v, Matrix m);
    static Point multiplicate(Point p, Matrix m);

    static Matrix inv(Matrix a);

    friend std::ostream& operator<<(std::ostream& os,
                                    const Matrix& p);

};
#endif // MATRIX_H
