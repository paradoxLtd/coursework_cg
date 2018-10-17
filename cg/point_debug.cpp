#include "point.h"
#include "debug.h"

#include <QDebug>

void Point::debug()
{
   //  Point();
   Point a;
   std::cout << a;

   // Point(double a, double b, double c, double d);
   Point b(2.43, 4.12, 5.32, 1);
   std::cout << b;

   // Point(Point *p);
   Point c(1,2,3);
   Point d(&c);
   c = Point();
   std::cout << d;

   // Point(Options opt);
   MoveOptions pp(1,2,3);
   Point f(pp);
   pp.set(3, 0);
   std::cout << f;

   // = ==
   Point v(d);
   Point aa = a;
   a.x = 4.4;
   a.y = 4.5;
   a.z = 4.5;
   b = a;
   bool is = (b == a);
   bool is1 = (c == f);
   std::cout << a << " \n" << aa << " \n and b == a is " <<
                is << " and c == f is " << is1;
   std::cout << v << v << d;
}
