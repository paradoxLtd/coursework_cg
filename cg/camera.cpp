#include "camera.h"


Camera::Camera(int attr, Point position,
               Vector u, Vector v, Vector n,
               Point target,
               double n_plane,
               double f_plane,
               double viewp_w,
               double viewp_h)
{
    _init(attr, position, u, v, n, target, n_plane, f_plane, viewp_w, viewp_h);
}

Camera::Camera(const Camera &c)
{
    this->_copy(c);
}


Camera &Camera::operator =(const Camera &c)
{
    this->_copy(c);
    return *this;
}

void Camera::_init(int attr, Point &position, Vector &u, Vector &v, Vector &n, Point &target, double n_plane, double f_plane, double viewp_w, double viewp_h)
{
    this->attr = attr;
    this->position = position;
    this->u = u;
    this->v = v;
    this->n = n;
    this->target = target;
    this->near_plane = n_plane;
    this->far_plane = f_plane;
    this->fov = FOV;
    this->viewport_w = viewp_w;
    this->viewport_h = viewp_h;

    this->viewport_xc = (viewp_w - 1) / 2.;
    this->viewport_yc = (viewp_h - 1) / 2.;
    this->asp_ratio = viewp_w / viewp_h;

    this->mcam.eye(); // Матрица камеры
    this->mper.eye(); // Эти пока не сильно важны
    this->mscr.eye();

    this->viewplane_width = VIEWPLANE_WIDTH;
    this->viewplane_height = VIEWPLANE_WIDTH / this->asp_ratio;

    double tg = tan(fov * (M_PI / 180.) / 2.); //Меняем на ходу
    this->dst = 0.5 * this->viewplane_width * tg;

    //Будем исходить из позиции, что  fov равен 90 для упрощения работы с отсечениями

    //Плоскости по желанию
    //Если они будут использоваться, то для них нужно будет производить преобразования
    /*Point origin = Point(0, 0, 0, 1);
    Vector vn;
    // Правая плоскость отсечения
    vn = Vector(1., 0., -1.); // Плоскость x=z
    this->right_plane = Plane(origin, vn, true);
    //Левая плоскость отсечения
    vn = Vector(-1., 0., -1.); // Плоскость -x=z
    this->left_plane = Plane(origin, vn, true);
    // Верхняя плоскость отсечения
    vn = Vector(0., 1., -1.);// Плоскость y=z
    this->top_plane = Plane(origin, vn, true);
    // Нижняя плоскость отсечения
    vn = Vector(0., 1., -1.);// Плоскость y=z
    this->bottom_plane = Plane(origin, vn, true);*/
}

void Camera::_copy(const Camera &c)
{
    this->attr = c.attr;
    this->position = c.position;
    this->u = c.u;
    this->v = c.v;
    this->n = c.n;
    this->target = c.target;
    this->near_plane = c.near_plane;
    this->far_plane = c.far_plane;
    this->fov = c.fov;
    this->viewport_w = c.viewport_w;
    this->viewport_h = c.viewport_h;

    this->mcam = c.mcam;
    this->mper = c.mper;
    this->mscr = c.mscr;

    this->viewport_xc = c.viewport_xc;
    this->viewport_yc = c.viewport_yc;
    this->asp_ratio = c.asp_ratio;

    this->viewplane_width = c.viewplane_width;
    this->viewplane_height = c.viewplane_height;

    this->dst = c.dst;

    this->right_plane = c.right_plane;
    this->left_plane = c.left_plane;
    this->top_plane = c.top_plane;
    this->bottom_plane = c.bottom_plane;
}

void Camera::build_cam_matrix()
{
    double mtx_t[SIZE][SIZE] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {-this->position.x, -this->position.y, -this->position.z, 1}
    };

    Matrix t_matrix(mtx_t);


    //Этот кусок кода на случай если мы не передаем в камеру вектора uvn
    //а хотим их вычислить
    this->n = Vector(this->target, this->position);
    this->v = Vector(0, 1, 0);
    this->u = v * n;
    this->v = n * u;

    this->v.normalize();
    this->u.normalize();
    this->n.normalize();

    double mtx_uvn[SIZE][SIZE] = {
        { this->u.x, this->v.x, this->n.x, 0 },
        { this->u.y, this->v.y, this->n.y, 0 },
        { this->u.z, this->v.z, this->n.z, 0 },
        { 0, 0, 0, 1 }
    };

    Matrix uvn_matrix(mtx_uvn);

    this->mcam = Matrix::multiplicate(t_matrix, uvn_matrix);

    //c568, там приводится сверический режим и обычный
    //пока для простоты (возможно и не понадобится сферический) реализуем простой режим

}
