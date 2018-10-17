#include "triangle.h"

void Triangle::debug()
{
    Point a(1, 2, 3);
    Point b(5, -3, 4);
    Point c(-3.4, 4.3, 1.11);

    Point d(0, 9, 3);
    Point g(12, 3.44, 4);
    Point h(4, 7, -1);

    Object obj1;
    obj1.vertex_local.push_back(a);
    obj1.vertex_local.push_back(b);
    obj1.vertex_local.push_back(c);
    obj1.vertex_local.push_back(d);
    obj1.vertex_local.push_back(g);
    obj1.vertex_local.push_back(h);
    obj1.update();

    Object obj2;
    obj2.vertex_local.push_back(c);
    obj2.vertex_local.push_back(g);
    obj2.vertex_local.push_back(a);
    obj2.vertex_local.push_back(g);
    obj2.vertex_local.push_back(g);
    obj2.vertex_local.push_back(a);
    obj2.update();

    Triangle tr1(&obj2, Indexes(1,2,3), Indexes(1,2,3));
    Triangle tr2(&obj1, Indexes(4,2,3), Indexes(1,2,3));
    Triangle tr3(&obj1, Indexes(1,3,2), Indexes(1,2,3));
    Triangle tr5(&obj1, Indexes(1,2,3), Indexes(1,2,3));
    Triangle tr6(&obj1, Indexes(1,2,3), Indexes(1,3,2));

    Triangle tr4 = tr1;
    tr1.indexes_text = Indexes(6,5,4);
    std::cout << "tr4" << tr4;
    std::cout << "tr1" << tr1;
    tr4.indexes_text = Indexes(6,5,4);
    tr1.normalTrans();
    std::cout << " normal " <<tr1.normal;
    //https://ru.onlinemschool.com/math/assistance/cartesian_coordinate/plane/
    // 5.0216 -16.39 -31.636

    std::cout << " \n" << (tr1 != tr2) << (tr1 == tr4) <<
                 (tr2 != tr4) << (tr1 != tr5) << (tr6 != tr5);
}
