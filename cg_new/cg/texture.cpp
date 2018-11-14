#include "texture.h"

Texture::Texture()
{

}

Texture::Texture(QImage image)
{
    this->_image = image;
}

void Texture::setTexture(const QImage &image)
{
    this->_image = image;
}

int Texture::GetWidth()
{
    return this->_image.width();
}

int Texture::GetHeight()
{
    return this->_image.height();
}

QColor Texture::pixel(int x, int y)
{
    return this->_image.pixelColor(x, y);
}
