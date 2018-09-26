#include "objectlist.h"

void ObjectList::debug()
{
    /*
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

    Camera cam = Camera(0, Point(100,100,100));

    ObjectList objlist1;
    objlist1.push(obj1);
    objlist1.prepareForConveyor();

    std::cout << "\n!!!!prepareForConveyor!!!!" << objlist1;

     objlist1.localToWorld();
     objlist1.worldToCam(cam);
     std::cout << "\n!!!! localToWorld and worldToCam !!!!" <<
                  objlist1;
*/
     ///////////////////////////////////////

     Vector cam_dir(0,0,0);
     Vector vscale(0.5,0.5,0.5);
     Vector vpos(0,0,0);
     Vector vrot(0,0,0);

     Point p1(0,50,0,1);
     Point p2(50,-50,0,1);
     Point p3(-50,-50,0,1);

     std::vector<Point> vertex{p1,p2,p3};
     Object new_obj(vertex);

     Indexes v(1,2,3);
     Indexes vt(1,2,3);

     Triangle tr(&new_obj,v,vt);
     new_obj.pushPolygon(tr);

     ObjectList objlist2;
     objlist2.push(new_obj);
     objlist2.prepareForConveyor();

     std::cout << "\n!!!!prepareForConveyor!!!!" << objlist2;

     /*

      objlist2.localToWorld();
      std::cout << "\nhere we go peple" << objlist2;

      Camera cam = Camera(0, Point(5,5,50));
      objlist2.worldToCam(cam);

      std::cout << "\n!!!!worldToCam !!!!" <<
                   objlist2;

       objlist2.camToAxonometricAndScreenObject(cam);
       std::cout << "\n!!!! Final !!!!" <<
                    objlist2;
                    */

}
