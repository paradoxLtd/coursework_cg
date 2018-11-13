#include "bitmap.h"



Bitmap::Bitmap(QWidget *parent) : QWidget(parent)
{

}


void Bitmap::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (!m_image.isNull())
        painter.drawImage(QPoint(0, 0), m_image);



    /*QPainter p(this);
    //Set the painter to use a smooth scaling algorithm.
    p.setRenderHint(QPainter::SmoothPixmapTransform, 1);
    p.drawImage(this->rect(), this->m_image);*/


}

void Bitmap::setImage(const QImage &image)
{
    m_size = image.size();
    m_image = image.scaled(size());
    update();
}

QImage &Bitmap::get_image_ref()
{
    return m_image;
}
