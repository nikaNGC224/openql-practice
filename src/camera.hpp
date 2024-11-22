#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glut.h>
#include <GL/glu.h>

class Camera
{
public:
    Camera(float x = 300.0f,
           float y = 0.0f,
           float z = 500.0f,
           float zoom = 500.0f)
        : _x(x), _y(y), _z(z), _zoom(zoom) {}

    void applyView() const
    {
        gluLookAt(_zoom + _x, _y, _zoom,  // Позиция камеры
                  _x, _y, 0.0f,          // Точка, на которую смотрим
                  0.0f, 0.0f, 1.0f);     // Вектор "вверх" вдоль оси Z
    }

    void moveX(float dx)
    {
        _x += dx;
    }

    void moveY(float dy)
    {
        _y += dy;
    }

    void moveZoom(float dz)
    {
        _zoom += dz;
        if (_zoom < MIN_ZOOM) _zoom = MIN_ZOOM;
        if (_zoom > MAX_ZOOM) _zoom = MAX_ZOOM;
    }

private:
    static constexpr float MIN_ZOOM = 100.0f;
    static constexpr float MAX_ZOOM = 2000.0f;

    float _x, _y, _z, _zoom;
};

#endif
