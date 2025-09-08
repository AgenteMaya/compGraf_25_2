#pragma once

#include <memory>
#include "shape.h"

class Polygon;
using PolygonPtr = std::unique_ptr<Polygon>;

class Polygon : public Shape 
{
    unsigned int m_vao;

protected:
    Polygon();

public:
    static PolygonPtr Make();
    virtual ~Polygon();
    virtual void Draw();
};