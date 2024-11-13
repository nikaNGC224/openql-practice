#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "shape_3d.hpp"

class Cylinder : public Shape3D
{
public:
    Cylinder() = delete;

    Cylinder(float radius, float height)
        : Shape3D(), _radius(radius), _height(height)
    {}

private:
    float _radius;
    float _height;

    void drawShape() override
    {
        glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет цилиндра
        gluCylinder(_quadric, _radius, _radius, _height, SLICES, STACKS);
    }
};

#endif
