#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GL/glut.h>
#include <array>

class Light
{
public:
    Light(GLenum id)
        : _id(id)
    {
        // Установка стандартных параметров
        setAmbient({0.2f, 0.2f, 0.2f, 1.0f});
        setDiffuse({1.0f, 1.0f, 1.0f, 1.0f});
        setSpecular({1.0f, 1.0f, 1.0f, 1.0f});
        setPosition({0.0f, 0.0f, 1.0f, 1.0f});
    }

    void enable() const
    {
        glEnable(_id);
    }

    void disable() const
    {
        glDisable(_id);
    }

    void setAmbient(const std::array<GLfloat, 4>& ambient)
    {
        _ambient = ambient;
        glLightfv(_id, GL_AMBIENT, _ambient.data());
    }

    void setDiffuse(const std::array<GLfloat, 4>& diffuse)
    {
        _diffuse = diffuse;
        glLightfv(_id, GL_DIFFUSE, _diffuse.data());
    }

    void setSpecular(const std::array<GLfloat, 4>& specular)
    {
        _specular = specular;
        glLightfv(_id, GL_SPECULAR, _specular.data());
    }

    void setPosition(const std::array<GLfloat, 4>& position)
    {
        _position = position;
        glLightfv(_id, GL_POSITION, _position.data());
    }

    void updatePosition(const std::array<GLfloat, 4>& position)
    {
        _position = position;
    }

    const std::array<GLfloat, 4>& getPosition() const
    {
        return _position;
    }

private:
    GLenum _id;
    std::array<GLfloat, 4> _ambient;
    std::array<GLfloat, 4> _diffuse;
    std::array<GLfloat, 4> _specular;
    std::array<GLfloat, 4> _position;
};

#endif
