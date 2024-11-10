#ifndef CUBE_HPP
#define CUBE_HPP

#include "shape_3d.hpp"

class Cube : public Shape3D
{
public:
    Cube() = delete;

    Cube(float size, Mode mode = Mode::Wire)
        : Shape3D(), _size(size)
    {
        _mode = mode;
    }

private:
    float _size;

    void drawShape() const override
    {
        if (_mode == Mode::Wire)
        {
            glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
            glutWireCube(_size);
        }
        else
        {
            glColor4f(1.0f, 0.0f, 0.0f, 0.6f);  // Красный цвет с альфа = 0.6 (полупрозрачный)
            glutSolidCube(_size);  // Рисуем куб размером 1.0
        }
    }
};

#endif
