#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include <cmath>
#include <algorithm>
#include <QDir>
#include <vector>
#include <limits>

#include "bitmap.h"
#include "vertex.h"
#include "gradient.h"
#include "edge.h"
#include "window_size.h"
#include "texture.h"

class RenderContext
{
public:
    RenderContext() = default;
    RenderContext(Bitmap *bitmap, int width, int height);

    void ClearDepthBuffer();

    void DrawTriangle(Vertex v1, Vertex v2,
                      Vertex v3, Texture &texture);

    bool ClipPolygonAxis(std::vector<Vertex> vertices,
                         std::vector<Vertex> auxillaryList,
                         int componentIndex);

    void ClipPolygonComponent(std::vector<Vertex> vertices,
                              int componentIndex,
                              float componentFactor,
                              std::vector<Vertex> result);


    void FillTriangle(Vertex v1, Vertex v2,
                      Vertex v3, Texture &texture);

    void ScanTriangle(Vertex minYVert, Vertex midYVert,
                      Vertex maxYVert, bool handedness,
                      Texture &texture);

    void ScanEdges(Gradients gradients, Edge a,
                   Edge b, bool handedness,
                   Texture &texture);


    void DrawScanLine(Gradients gradients, Edge left,
                      Edge right, int j,
                      Texture &texture);

    void setPixel(int x, int y, QColor color);

    void copyPixel(int destX, int destY,
                   int srcX, int srcY,
                   Texture &texture);

    int GetWidth();
    int GetHeight();

private:
    std::vector<float>  m_zBuffer;
    Bitmap *bitmap;
    int width;
    int height;

};
#endif // RENDERCONTEXT_H
