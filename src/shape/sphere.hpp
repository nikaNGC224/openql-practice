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
            setShiny();

            // Рисуем сферу
            glutSolidSphere(_radius, SLICES, STACKS);

            removeShiny();
        }
    }

    void setShiny()
    {
        // Устанавливаем блестящий материал для сферы
        GLfloat mat_specular[]  {1.0f, 1.0f, 1.0f, 1.0f};   // Яркий белый блик
        GLfloat mat_diffuse[]   {0.6f, 0.6f, 0.6f, 1.0f};    // Основной цвет сферы
        GLfloat mat_ambient[]   {0.2f, 0.2f, 0.2f, 1.0f};    // Фоновый цвет
        GLfloat mat_shininess[] {128.0f};                  // Максимальное значение блеска

        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    }

    void removeShiny()
    {
        // Сбрасываем материал на стандартные параметры для других фигур
        GLfloat mat_specular[] {0.0f, 0.0f, 0.0f, 1.0f};   // Нет бликов
        GLfloat mat_diffuse[]  {0.8f, 0.8f, 0.8f, 1.0f};    // Светло-серый цвет
        GLfloat mat_ambient[]  {0.2f, 0.2f, 0.2f, 1.0f};    // Фоновый цвет
        GLfloat mat_shininess[] {0.0f};                    // Без блеска

        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    }
};

#endif
