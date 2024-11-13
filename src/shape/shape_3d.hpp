#ifndef SHAPE_3D_HPP
#define SHAPE_3D_HPP

#include <GL/glut.h>
#include <GL/glu.h>

class Shape3D
{
public:
    enum class Mode
    {
        Wire,
        Solid
    };

    virtual ~Shape3D()
    {
        gluDeleteQuadric(_quadric);
    }

    void draw()
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
    const int SLICES {20}; // Количество сегментов по окружности
    const int STACKS {10}; // Количество сегментов по высоте

    GLUquadric* _quadric;
    Mode _mode;

    float _x{}, _y{}, _z{};

    Shape3D()
    {
        _quadric = gluNewQuadric();
        gluQuadricDrawStyle(_quadric, GLU_LINE);
    }

private:
    virtual void drawShape() = 0;
};

#endif
