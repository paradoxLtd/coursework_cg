#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <QColor>

class Texture
{
public:
    Texture();
    Texture(QImage image);

    void setTexture(const QImage& image);

    int GetWidth();
    int GetHeight();

    QColor pixel(int x, int y);

private:
    int _width;
    int _height;
    QImage _image;
};

#endif // TEXTURE_H
