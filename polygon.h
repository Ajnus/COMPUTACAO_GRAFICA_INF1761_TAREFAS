#include <memory>
class Polygon;
using PolygonPtr = std::shared_ptr<Polygon>;

#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape
{
    unsigned int m_vao;
    protected: 
    Polygon (int n, float* xy, unsigned char* rgb, unsigned int* inc);
    public: 
    static PolygonPtr Make (int n, float* xy, unsigned char* rgb, unsigned int* inc);
    virtual ~Polygon ();
    virtual void Draw();
};
#endif