#ifndef CUBE_HPP
#define CUBE_HPP

#include "shape_3d.hpp"

class Cube : public Shape3D
{
public:
    Cube() = delete;

    Cube(float size)
        : Shape3D(), _size(size)
    {}

private:
    float _size;

    void drawShape() const override
    {
        glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
        glutWireCube(_size);
    }
};

#endif
