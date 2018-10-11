#include "object.h"

void Object::debug()
{
    /*
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    */
    Point v1(1, -1, -1);
    Point v2(1, -1, 1);
    Point v3(-1, -1, 1);
    Point v4(-1, -1, -1);

    Point v5(1, 1, -1);
    Point v6(1, 1, 1);
    Point v7(-1, 1, 1);
    Point v8(-1, 1, -1);

    Object obj1;
    obj1.vertex_local.push_back(v1);
    obj1.vertex_local.push_back(v2);
    obj1.vertex_local.push_back(v3);
    obj1.vertex_local.push_back(v4);
    obj1.vertex_local.push_back(v5);
    obj1.vertex_local.push_back(v6);
    obj1.vertex_local.push_back(v7);
    obj1.vertex_local.push_back(v8);
    obj1.update();
    /*
    std::cout << "\nLook at indexes array:";
    std::vector<int> indexes = obj1.jarvis();
    for (int i = 0; i < indexes.size(); i++)
    {
        std::cout << " " << indexes[i] << ";";
    }
*/
}
