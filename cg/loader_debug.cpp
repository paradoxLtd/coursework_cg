#include "Loader.h"

void Loader::debug()
{
    // http://people.sc.fsu.edu/~jburkardt/data/obj/obj
    Loader loader;
    Object object;
    int err = loader.load(&object, "loader_test_one.obj");
    SET_BIT(object.state, OBJECT_DETAILED);
    std::cout << "error:" << err << " and " << object.state << "\n ";
    std::cout << object;

    err = loader.load(&object, "loader_test_one.obj");
    SET_BIT(object.state, OBJECT_DETAILED);
    std::cout << "\n!!!i try again" << object;

    /* Вызывает ошибку!!!
    Camera camera;
    Scene scene(camera);
    std::vector<std::string> vec;
    vec.push_back("loader_test_one.obj");
    vec.push_back("loader_test_two.obj");
    err = loader.loadAll(scene, vec);
    */
}
