#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape_3d.hpp"

class Sphere : public Shape3D
{
public:
    Sphere(const float& radius)
        : Shape3D(), _radius(_radius), MIN_RADIUS(radius), MAX_RADIUS(radius * 1.5f)
    {}

    void incRadius(float incStep)
    {
        _radius += incStep;
        if (_radius > MAX_RADIUS)
        {
            _radius = MAX_RADIUS;
        }
    }

    void decRadius(float decStep)
    {
        _radius -= decStep;
        if (_radius < MIN_RADIUS)
        {
            _radius = MIN_RADIUS;
        }
    }

private:
    const float MIN_RADIUS;
    const float MAX_RADIUS;

    float _radius;

    void drawShape() const override
    {
        glColor3f(1.0f, 1.0f, 0.0f);  // Жёлтый цвет сферы
        gluSphere(_quadric, _radius, SLICES, STACKS);
    }
};

#endif
