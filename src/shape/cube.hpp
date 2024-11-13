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

    void drawShape() override
    {
        if (_mode == Mode::Wire)
        {
            glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
            glutWireCube(_size);
        }
        else
        {
            glDepthMask(GL_FALSE);                              // Отключаем запись в буфер глубины
            glEnable(GL_BLEND);                                 // Включаем смешивание
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // Настраиваем функцию смешивания

            glColor4f(0.0117f, 0.5859f, 0.367f, 0.7f);
            glutSolidCube(_size);

            glDisable(GL_BLEND);                      // Отключаем смешивание
            glDepthMask(GL_TRUE);                     // Включаем запись в буфер глубины
        }
    }
};

#endif
