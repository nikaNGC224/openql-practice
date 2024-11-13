#ifndef CONE_HPP
#define CONE_HPP

#include "shape_3d.hpp"

class Cone : public Shape3D
{
public:
    Cone() = delete;

    Cone(float radius, float height)
        : Shape3D(), _radius(radius), _height(height)
    {}

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
        glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
        glRotatef(_rotationAngleX, 1.0f, 0.0f, 0.0f);
        glutWireCone(_radius, _height, SLICES, STACKS);
    }
};

#endif
