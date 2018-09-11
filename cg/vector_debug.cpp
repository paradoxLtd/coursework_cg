#include "Vector.h"

// Vector
void Vector::debug()
{
     //normalize

    Vector norm(1,2,3);
    norm.normalize();
    std::cout << norm;
    // 0.2672 0.5345 0.8017

    //Vector(Point p1, Point p2)
    Vector vec1(Point(3.6, 3.8, 3.7),
                Point(3.1, 3.3, 3.2));
    std::cout << vec1;

    //Vector(double x1, double y1, double z1,
    //double x2, double y2, double z2)
    Vector vec2(5.1, 5.2, 5.3, 0.1, 0.2, 0.3);
    std::cout << vec2;

    Vector vec3(3.3, 3.2, 3.0);
    std::cout << vec3;

    // =
    Vector vec4(vec3);
    vec3.x = 1;
    Vector vec5 = vec3;
    vec3.x = 0;
    std::cout << vec4;
    std::cout << vec5;


    std::cout << "\nvectorMultiplication  ";
    Vector vec6(4.3, 5.4, 5.5);
    Vector vec7(12.3, 10.3, 0.3);
    Vector vec8(vec6, vec7);
    std::cout << vec8;
    // https://ru.onlinemschool.com/math/assistance/vector/multiply1/
    // -55.03; 66.36; -22.13

    Vector vec9(3.2, 4.5, 2.5);
    Vector vec10(8.8, 9.3, 6.5);
    Vector vec11(vec9, vec10);
    std::cout << vec11;
    // 6; 1.2; -9.84

    Vector vec12(1.2, 2.5, -4.5);
    Vector vec13(-2.8, 2.3, 1.2);
    //Vector vec16(13.35, 11.16, 9.76);
    Vector vec14(1.8, 1.3, 3);
    Vector vec15 = vec12 * vec13 * vec14;

    std::cout << vec15;
    // 13.35; 11.16. 9.76 после первого умножения
    // 20.792; -22.482; -2.733

    std::cout << "\nscalarMultiplication  ";
    double d1 = scalarMultiplication(vec9, vec10);
    double d2 = scalarMultiplication(vec12, vec13);
    double d3 = scalarMultiplication(vec13, vec12);
    std::cout << "real values are 86.26, -3.01, -3.01 but i got:" << d1
              << " and " << d2 << " and " << d3;

    std::cout << "\n asPoint  ";
    Vector vec_(1.2, 3.4, 6.5);
    Point point_(1.2, 3.4, 6.5);
    bool compare = vec_.asPoint() == point_;
    std::cout << compare << point_ << vec_.asPoint();

    std::cout << "\n compare  ";
    Vector c1(3.3, 2.3, 0.001);
    Vector c2(3.3, 2.3, 0.001);
    std::cout << Vector::areEqual(c1, c2) << (c1 == c2) << (c1 != c2);

    Vector cc1(3.3, 2.3, 0.1);
    Vector cc2(3.3, 2.3, 0);
    Vector ccc1(3.3, 2.31, 0);
    Vector ccc2(3.3, 2.3, 0);
    Vector cccc1(3.31, 2.3, 0);
    Vector cccc2(3.3, 2.3, 0);
    std::cout <<  (cc1 == cc2) << (ccc1 == ccc2) << (cccc1 == cccc2);

}
