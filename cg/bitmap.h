#ifndef BITMAP_H
#define BITMAP_H

#include <QObject>
#include <QWidget>
#include <QPainter>
//#include <QtOpenGL>

class Bitmap : public QWidget
{
    Q_OBJECT
public:
    explicit Bitmap(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

public slots:
    void setImage(const QImage& image);
    QImage& get_image_ref();

private:
    QImage m_image;
    QSize m_size;



};

#endif // BITMAP_H
