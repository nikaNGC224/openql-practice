#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape_3d.hpp"

class Sphere : public Shape3D
{
public:
    Sphere()
        : Shape3D()
    {}

    float getRadius() const
    {
        return _radius;
    }

    void setRadius(float radius)
    {
        _radius = radius;
    }

    float getMinRadius() const
    {
        return MIN_RADIUS;
    }

    float getMaxRadius() const
    {
        return MAX_RADIUS;
    }

private:
    const float MIN_RADIUS {300.0f};
    const float MAX_RADIUS {MIN_RADIUS * 1.5f};

    float _radius {MIN_RADIUS};

    void drawShape() const override
    {
        glColor3f(1.0f, 1.0f, 0.0f);  // Жёлтый цвет сферы
        gluSphere(_quadric, _radius, SLICES, STACKS);
    }
};

#endif
