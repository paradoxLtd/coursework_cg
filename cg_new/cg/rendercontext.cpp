#include <qDebug>
#include "rendercontext.h"

RenderContext::RenderContext(Bitmap *bitmap,
                             int width, int height) {
    this->bitmap = bitmap;
    this->width = width;
    this->height = height;
    m_zBuffer.resize(width * height);
}

void RenderContext::ClearDepthBuffer() {
    for(int i = 0; i < m_zBuffer.size(); i++) {
        m_zBuffer[i] = std::numeric_limits<float>::max();
    }
}

void RenderContext::DrawTriangle(Vertex v1, Vertex v2,
                                 Vertex v3, Texture &texture) {

    /*
    qDebug() << v1.GetX() << v1.GetY();
    qDebug() << v2.GetX() << v2.GetY();
    qDebug() << v3.GetX() << v3.GetY();
    qDebug() << "--------";*/

    if(v1.IsInsideViewFrustum() &&
            v2.IsInsideViewFrustum() &&
            v3.IsInsideViewFrustum()) {
        FillTriangle(v1, v2, v3, texture);

        //qDebug() << "Returned";

        return;
    }

    std::vector<Vertex> vertices;
    std::vector<Vertex> auxillaryList;

    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);

    if(ClipPolygonAxis(vertices, auxillaryList, 0) &&
            ClipPolygonAxis(vertices, auxillaryList, 1) &&
            ClipPolygonAxis(vertices, auxillaryList, 2)) {
        Vertex initialVertex = vertices[0];

        for(int i = 1; i < vertices.size() - 1; i++) {
            FillTriangle(initialVertex, vertices[i], vertices[i + 1], texture);
        }
    }
}

bool RenderContext::ClipPolygonAxis(std::vector<Vertex> vertices,
                     std::vector<Vertex> auxillaryList,
                     int componentIndex)
{
    ClipPolygonComponent(vertices, componentIndex, 1.0f, auxillaryList);
    vertices.clear();

    if(auxillaryList.empty()) {
        return false;
    }

    ClipPolygonComponent(auxillaryList, componentIndex, -1.0f, vertices);
    auxillaryList.clear();

    return !vertices.empty();
}

void RenderContext::ClipPolygonComponent(std::vector<Vertex> vertices,
                                         int componentIndex,
                                         float componentFactor,
                                         std::vector<Vertex> result)
{
    Vertex previousVertex = vertices[vertices.size() - 1];
    float previousComponent = previousVertex.Get(componentIndex) * componentFactor;
    bool previousInside = previousComponent <= previousVertex.GetPosition().GetW();

    //Iterator<Vertex> it = vertices.iterator();
    for(int i = 0; i < vertices.size(); i++)//while(it.hasNext())
    {
        Vertex currentVertex = vertices[i];//it.next();
        float currentComponent = currentVertex.Get(componentIndex) * componentFactor;
        bool currentInside = currentComponent <= currentVertex.GetPosition().GetW();

        if(currentInside ^ previousInside) {
            float lerpAmt = (previousVertex.GetPosition().GetW() - previousComponent) /
                ((previousVertex.GetPosition().GetW() - previousComponent) -
                 (currentVertex.GetPosition().GetW() - currentComponent));

            result.push_back(previousVertex.Lerp(currentVertex, lerpAmt));
        }

        if(currentInside) {
            result.push_back(currentVertex);
        }

        previousVertex = currentVertex;
        previousComponent = currentComponent;
        previousInside = currentInside;
    }
}

void RenderContext::FillTriangle(Vertex v1, Vertex v2,
                                 Vertex v3, Texture &texture)
{
    Matrix4f screenSpaceTransform = Matrix4f().InitScreenSpaceTransform(this->width / 2, this->height / 2);
    Matrix4f identity = Matrix4f().InitIdentity();
    Vertex minYVert = v1.Transform(screenSpaceTransform, identity).PerspectiveDivide();
    Vertex midYVert = v2.Transform(screenSpaceTransform, identity).PerspectiveDivide();
    Vertex maxYVert = v3.Transform(screenSpaceTransform, identity).PerspectiveDivide();

    /*
    qDebug() << "v1 x:" << v1.GetX() << " y:"
             << v1.GetY() << " z:" <<
                v1.GetZ();
    qDebug() << "v2 x:" << v2.GetX() << " y:"
             << v2.GetY() << " z:" <<
                v2.GetZ();
    qDebug() << "v3 x:" << v3.GetX() << " y:"
             << v3.GetY() << " z:" <<
                v3.GetZ();

    qDebug() << "TriangleAreaTimesTwo: " << minYVert.TriangleAreaTimesTwo(maxYVert, midYVert);

     */
    if(minYVert.TriangleAreaTimesTwo(maxYVert, midYVert) >= 0) {
        //qDebug() << "we re in ret";
        return;
    }

    //qDebug() << "+++";

    if(maxYVert.GetY() < midYVert.GetY()) {
        Vertex temp = maxYVert;
        maxYVert = midYVert;
        midYVert = temp;
    }

    if(midYVert.GetY() < minYVert.GetY()) {
        Vertex temp = midYVert;
        midYVert = minYVert;
        minYVert = temp;
    }

    if(maxYVert.GetY() < midYVert.GetY())
    {
        Vertex temp = maxYVert;
        maxYVert = midYVert;
        midYVert = temp;
    }

    ScanTriangle(minYVert, midYVert, maxYVert,
            minYVert.TriangleAreaTimesTwo(maxYVert, midYVert) >= 0,
            texture);
}

void RenderContext::ScanTriangle(Vertex minYVert, Vertex midYVert,
        Vertex maxYVert, bool handedness, Texture &texture)
{

    Gradients gradients(minYVert, midYVert, maxYVert);
    Edge topToBottom(gradients, minYVert, maxYVert, 0);
    Edge topToMiddle(gradients, minYVert, midYVert, 0);
    Edge middleToBottom(gradients, midYVert, maxYVert, 1);

    ScanEdges(gradients, topToBottom, topToMiddle,
              handedness, texture);
    ScanEdges(gradients, topToBottom, middleToBottom,
              handedness, texture);
}

void RenderContext::ScanEdges(Gradients gradients,
                              Edge a, Edge b, bool handedness,
                              Texture &texture)
{
    Edge left = a;
    Edge right = b;
    if(handedness)
    {
        Edge temp = left;
        left = right;
        right = temp;
    }

    int yStart = b.GetYStart();
    int yEnd   = b.GetYEnd();
    for(int j = yStart; j < yEnd; j++)
    {
        DrawScanLine(gradients, left, right, j, texture);
        left.Step();
        right.Step();
    }
}

void RenderContext::copyPixel(int destX, int destY,
                              int srcX, int srcY, Texture &texture)
{

    setPixel(destX, destY, QColor(texture.pixel(srcX, srcY)));
}

int RenderContext::GetWidth()
{
    return this->width;
}

int RenderContext::GetHeight()
{
    return this->height;
}

void RenderContext::setPixel(int x, int y, QColor color)
{
    //qDebug() << "X Y" << x << " " << y;

    this->bitmap->get_image_ref().setPixelColor(x, y, color);
}

void RenderContext::DrawScanLine(Gradients gradients, Edge left,
                                 Edge right, int j, Texture &texture)
{
    int xMin = (int)ceil(left.GetX());
    int xMax = (int)ceil(right.GetX());
    float xPrestep = xMin - left.GetX();

    float texCoordXXStep = gradients.GetTexCoordXXStep();
    float texCoordYXStep = gradients.GetTexCoordYXStep();
    float oneOverZXStep = gradients.GetOneOverZXStep();
    float depthXStep = gradients.GetDepthXStep();
    float lightAmtXStep = gradients.GetLightAmtXStep();

    float texCoordX = left.GetTexCoordX() + texCoordXXStep * xPrestep;
    float texCoordY = left.GetTexCoordY() + texCoordYXStep * xPrestep;
    float oneOverZ = left.GetOneOverZ() + oneOverZXStep * xPrestep;
    float depth = left.GetDepth() + depthXStep * xPrestep;
    float lightAmt = left.GetLightAmt() + lightAmtXStep * xPrestep;

    for(int i = xMin; i < xMax; i++)
    {
        int index = i + j * this->width;
        if(depth < m_zBuffer[index])
        {
            m_zBuffer[index] = depth;
            float z = 1.0f/oneOverZ;
            int srcX = (int)((texCoordX * z) * (float)(texture.GetWidth() - 1) + 0.5f);
            int srcY = (int)((texCoordY * z) * (float)(texture.GetHeight() - 1) + 0.5f);

            //CopyPixel(i, j, srcX, srcY, texture, lightAmt); Пока забудем про свет
            copyPixel(i, j, srcX, srcY, texture);
        }

        oneOverZ += oneOverZXStep;
        texCoordX += texCoordXXStep;
        texCoordY += texCoordYXStep;
        depth += depthXStep;
        lightAmt += lightAmtXStep;
    }
}
