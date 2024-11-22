#ifndef SCENE_HPP
#define SCENE_HPP

#include "shape/shape_3d.hpp"

#include <algorithm>
#include <memory>
#include <unordered_map>
#include <vector>

struct CameraPos
{
    static float cameraX;
    static float cameraY;
    static float cameraZ;
};

class Scene
{
public:
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

    void addShape(ShapeType type, std::unique_ptr<Shape3D> quadric)
    {
        if (quadric->isTransparent())
        {
            _hasTransparentShape = true;
        }

        _shapes.emplace(type, std::move(quadric));
    }

    bool hasTransparentObjects() const
    {
        return _hasTransparentShape;
    }

    Shape3D* getQuadric(ShapeType type) const
    {
        auto it = _shapes.find(type);

        return (it != _shapes.end()) ? it->second.get() : nullptr;
    }

    void draw() const
    {
        for (const auto& [type, shape] : _shapes)
        {
            if (!shape->isTransparent())
            {
                shape->draw();
            }
        }

        // Подготовка для рендеринга прозрачных объектов
        glDepthMask(GL_FALSE); // Отключаем запись в буфер глубины
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Сортируем прозрачные объекты и рисуем их
        std::vector<std::pair<float, Shape3D*>> transparentShapes;

        for (const auto& [type, shape] : _shapes)
        {
            if (shape->isTransparent())
            {
                float distance = shape->distanceToCamera(CameraPos::cameraX,
                                                         CameraPos::cameraY,
                                                         CameraPos::cameraZ);
                transparentShapes.emplace_back(distance, shape.get());
            }
        }

        std::sort(transparentShapes.begin(), transparentShapes.end(), [](const auto& a, const auto& b)
        {
            return a.first > b.first; // Дальше — первыми
        });

        for (const auto& [distance, shape] : transparentShapes)
        {
            shape->draw();
        }

        // Завершаем настройки
        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
    }

private:
    std::unordered_map<ShapeType, std::unique_ptr<Shape3D>> _shapes;

    bool _hasTransparentShape {false};
};

#endif
