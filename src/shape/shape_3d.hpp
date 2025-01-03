#ifndef SHAPE_3D_HPP
#define SHAPE_3D_HPP

#include <GL/glut.h>
#include <GL/glu.h>

#include <array>

struct Vector3
{
    float x, y, z;

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
};

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

    virtual bool isTransparent() const
    {
        return false;
    }

    void draw()
    {
        glPushMatrix();  // Сохраняем текущую матрицу
        glTranslatef(_x, _y, _z);
        drawShape();
        glPopMatrix();  // Восстанавливаем матрицу
    }

    Vector3 getPosition() const
    {
        return Vector3(_x, _y, _z);
    }

    void setPosition(const Vector3& pos)
    {
        _x = pos.x;
        _y = pos.y;
        _z = pos.z;
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

    struct Material
    {
        std::array<GLfloat, 4> ambient;
        std::array<GLfloat, 4> diffuse;
        std::array<GLfloat, 4> specular;
        GLfloat shininess;

        Material()
            : ambient(),
              diffuse(),
              specular(),
              shininess() {}

        Material(const std::array<GLfloat, 4>& amb,
                 const std::array<GLfloat, 4>& dif,
                 const std::array<GLfloat, 4>& spe,
                 GLfloat shin)
            : ambient(amb),
              diffuse(dif),
              specular(spe),
              shininess(shin) {}
    };

    Material _material;

    void applyMaterial() const
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _material.ambient.data());
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _material.diffuse.data());
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _material.specular.data());
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _material.shininess);
    }

    Shape3D()
    {
        _quadric = gluNewQuadric();
        gluQuadricDrawStyle(_quadric, GLU_LINE);
    }

private:
    virtual void drawShape() = 0;
};

#endif
