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

    void setRotationAngleX(const float& angle)
    {
        if (angle >= 360.0f)
        {
            _rotationAngleX = angle - 360.0f;
        }
        else if (angle <= -360.0f)
        {
            _rotationAngleX = angle + 360.0f;
        }
        else
        {
            _rotationAngleX = angle;
        }
    }

    float getRotationAngleX() const
    {
        return _rotationAngleX;
    }

private:
    float _radius;
    float _height;
    float _rotationAngleX{};

    void drawShape() const override
    {
        glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
        glRotatef(_rotationAngleX, 1.0f, 0.0f, 0.0f);
        glutWireCone(_radius, _height, SLICES, STACKS);
    }
};

#endif
