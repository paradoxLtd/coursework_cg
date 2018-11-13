#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H
/*
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
*/
#include <cmath>
#include <algorithm>
#include "bitmap.h"

#include "float.h"
#include <QDir>
#include <vector>
#include "vertex.h"
#include "rendercontext.h"
#include "gradient.h"
#include "float.h"

class RenderContext
{
public:
    RenderContext(Bitmap *bitmap, int width, int height );

    void ClearDepthBuffer();

    void DrawTriangle(Vertex v1, Vertex v2, Vertex v3, Bitmap texture);

    bool ClipPolygonAxis(std::vector<Vertex> vertices, std::vector<Vertex> auxillaryList,
                int componentIndex);

    void ClipPolygonComponent(std::vector<Vertex> vertices, int componentIndex,
                float componentFactor, std::vector<Vertex> result);


    void FillTriangle(Vertex v1, Vertex v2, Vertex v3, Bitmap texture);

    void ScanTriangle(Vertex minYVert, Vertex midYVert,
                Vertex maxYVert, boolean handedness, Bitmap texture);

    void ScanEdges(Gradients gradients, Edge a, Edge b, boolean handedness, Bitmap texture);


    void DrawScanline(Gradients gradients, Edge left, Edge right, int j, Bitmap texture);

    void setPixel(int x, int y, QColor color);

    void copyPixel(int destX, int destY, int srcX, int srcY, Bitmap& texture);

private:
    std::vector<float>  m_zBuffer;
    Bitmap *bitmap;
    int width;
    int height;

};
#endif // RENDERCONTEXT_H
