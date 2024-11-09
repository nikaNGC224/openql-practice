#ifndef SHAPE_3D_HPP
#define SHAPE_3D_HPP

#include <GL/glut.h>
#include <GL/glu.h>

class Shape3D
{
public:
    void draw() const
    {
        glPushMatrix();  // Сохраняем текущую матрицу
        glTranslatef(_x, _y, _z);
        drawShape();
        glPopMatrix();  // Восстанавливаем матрицу
    }

    void setPosition(float x, float y, float z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

protected:
    GLUquadric* _quadric;
    const int SLICES {20}; // Количество сегментов по окружности
    const int STACKS {10}; // Количество сегментов по высоте

    float _x{}, _y{}, _z{};

    Shape3D()
    {
        _quadric = gluNewQuadric();
        gluQuadricDrawStyle(_quadric, GLU_LINE);
    }

    virtual ~Shape3D()
    {
        gluDeleteQuadric(_quadric);
    }

private:
    virtual void drawShape() const = 0;
};

#endif