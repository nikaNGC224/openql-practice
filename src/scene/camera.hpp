#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <algorithm>
#include <cmath>

#include "../shape/shape_3d.hpp"

class Camera
{
public:
    static constexpr float MIN_ZOOM = 100.0f;
    static constexpr float MAX_ZOOM = 2000.0f;

    Camera()
    {
        updatePosition();
    }

    void setAzimuth(float azimuth)
    {
        _azimuth = ::fmod(azimuth, 360.0f);
        updatePosition();
    }

    void setZenith(float zenith)
    {
        _zenith = std::clamp(zenith, -89.0f, 89.0f);
        updatePosition();
    }

    void setRadius(float radius)
    {
        _radius = std::clamp(radius, MIN_ZOOM, MAX_ZOOM);
        updatePosition();
    }

    void adjustAzimuth(float delta)
    {
        setAzimuth(_azimuth + delta);
    }

    void adjustZenith(float delta)
    {
        setZenith(_zenith + delta);
    }

    void adjustRadius(float delta)
    {
        setRadius(_radius + delta);
    }

    Vector3 getPosition() const
    {
        return Vector3(_x, _y, _z);
    }

    float distanceToCamera(const Vector3& other) const
    {
        return std::sqrt(std::pow(_x - other.x, 2) + std::pow(_y - other.y, 2) + std::pow(_z - other.z, 2));
    }

private:
    float _x {300.0f};
    float _y {};
    float _z {500.0f};

    float _azimuth {}; // Угол в градусах вокруг оси Y
    float _zenith {45.0f};  // Угол в градусах вверх/вниз
    float _radius {500.0f};  // Расстояние от камеры до начала координат

    float _zoom{500.0f};

    static float degToRad(float degrees)
    {
        return degrees * static_cast<float>(M_PI) / 180.0f;
    }

    void updatePosition()
    {
        _x = _radius * std::sin(degToRad(_zenith)) * std::cos(degToRad(_azimuth));
        _y = _radius * std::sin(degToRad(_zenith)) * std::sin(degToRad(_azimuth));
        _z = _radius * std::cos(degToRad(_zenith));
    }
};

#endif
