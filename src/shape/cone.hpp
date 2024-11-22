#ifndef CONE_HPP
#define CONE_HPP

#include "shape_3d.hpp"

class Cone : public Shape3D
{
public:
    Cone() = delete;

    Cone(float radius, float height, Mode mode = Mode::Wire)
        : Shape3D(), _radius(radius), _height(height)
    {
        _mode = mode;

        if (_mode == Mode::Solid)
        {
            std::array<GLfloat, 4> amb {0.2f, 0.2f, 0.2f, 1.0f};
            std::array<GLfloat, 4> dif {0.6f, 0.6f, 0.6f, 1.0f};
            std::array<GLfloat, 4> spe {0.0f, 0.0f, 0.0f, 1.0f};
            GLfloat shin {};
            _material = Material(amb, dif, spe, shin);
        }
    }

    bool isTransparent() const override
    {
        return false;
    }

    void incRotationAngleX(float incStep)
    {
        _rotationAngleX += incStep;
        if (_rotationAngleX >= MAX_DEGREE)
        {
            _rotationAngleX -= MAX_DEGREE;
        }
    }

    void decRotationAngleX(float decStep)
    {
        _rotationAngleX -= decStep;
        if (_rotationAngleX <= -MAX_DEGREE)
        {
            _rotationAngleX += MAX_DEGREE;
        }
    }

private:
    const float MAX_DEGREE {360.0f};

    float _radius;
    float _height;
    float _rotationAngleX{};

    void drawShape() override
    {
        if (_mode == Mode::Wire)
        {
            glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
            glRotatef(_rotationAngleX, 1.0f, 0.0f, 0.0f);
            glutWireCone(_radius, _height, SLICES, STACKS);
        }
        else
        {
            glEnable(GL_LIGHTING);
            applyMaterial();
            glutSolidCone(_radius, _height, SLICES, STACKS);

            glDisable(GL_LIGHTING);
        }
    }
};

#endif
