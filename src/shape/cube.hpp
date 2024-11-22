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

        if (_mode == Mode::Solid)
        {
            _transparent = true;
        }
    }

    bool isTransparent() const override
    {
        return _transparent;
    }

private:
    float _size;
    bool _transparent {false};

    void drawShape() override
    {
        if (_mode == Mode::Wire)
        {
            glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
            glutWireCube(_size);
        }
        else
        {
            glColor4f(0.0117f, 0.5859f, 0.367f, 0.6f);
            glutSolidCube(_size);
        }
    }
};

#endif
