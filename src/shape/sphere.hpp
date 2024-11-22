#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape_3d.hpp"

class Sphere : public Shape3D
{
public:
    Sphere(const float& radius, Mode mode = Mode::Wire)
        : Shape3D(), _radius(radius), MIN_RADIUS(radius), MAX_RADIUS(radius * 1.5f)
    {
        _mode = mode;

        if (_mode == Mode::Solid) {
            std::array<GLfloat, 4> amb = {0.2f, 0.2f, 0.2f, 1.0f};
            std::array<GLfloat, 4> dif = {0.6f, 0.6f, 0.6f, 1.0f};
            std::array<GLfloat, 4> spe = {1.0f, 1.0f, 1.0f, 1.0f};
            GLfloat shin = 128.0f;
            _material = Material(amb, dif, spe, shin);
        }
    }

    bool isTransparent() const override
    {
        return false;
    }

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

    const float SOLID_SLICES{40};
    const float SOLID_STACKS{40};

    float _radius;

    void drawShape() override
    {
        if (_mode == Mode::Wire)
        {
            glColor3f(1.0f, 1.0f, 0.0f);  // Жёлтый цвет сферы
            gluSphere(_quadric, _radius, SLICES, STACKS);
        }
        else
        {
            glEnable(GL_LIGHTING);
            applyMaterial();

            // Рисуем сферу
            glutSolidSphere(_radius, SOLID_SLICES, SOLID_STACKS);

            glDisable(GL_LIGHTING);
        }
    }
};

#endif
