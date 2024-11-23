#ifndef SCENE_HPP
#define SCENE_HPP

#include "camera.hpp"

#include <memory>
#include <unordered_map>
#include <map>
#include <vector>

class Scene
{
public:
    static Camera camera;

    enum class ShapeType
    {
        Cylinder,
        Sphere,
        Cube,
        Cone,
        Light
    };

    Scene() = default;
    ~Scene() = default;

    void addShape(ShapeType type, std::unique_ptr<Shape3D> shape)
    {
        if (shape->isTransparent())
        {
            _hasTransparentShape = true;
        }

        _shapes.emplace_back(0.0f, shape.get());
        _shapeStorage.emplace(type, std::move(shape));
    }

    bool hasTransparentObjects() const
    {
        return _hasTransparentShape;
    }

    Shape3D* getQuadric(ShapeType type) const
    {
        auto it = _shapeStorage.find(type);

        return (it != _shapeStorage.end()) ? it->second.get() : nullptr;
    }

    void draw()
    {
        for (auto& entry : _shapes)
        {
            entry.distance = camera.distanceToCamera(entry.shape->getPosition());
        }

        std::sort(_shapes.begin(), _shapes.end(), [](const ShapeEntry& a, const ShapeEntry& b)
        {
            return a.distance > b.distance; // От большего к меньшему
        });

        for (const auto& entry : _shapes)
        {
            entry.shape->draw();
        }
    }

private:
    struct ShapeEntry
    {
        float distance;
        Shape3D* shape;

        ShapeEntry(float dist, Shape3D* sh)
            : distance(dist), shape(sh) {}
    };

    std::vector<ShapeEntry> _shapes;
    std::unordered_map<ShapeType, std::unique_ptr<Shape3D>> _shapeStorage;

    bool _hasTransparentShape {false};
};

#endif
