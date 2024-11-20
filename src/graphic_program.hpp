#ifndef GRAPHIC_PROGRAM_HPP
#define GRAPHIC_PROGRAM_HPP

#include "shape/cylinder.hpp"
#include "shape/sphere.hpp"
#include "shape/cube.hpp"
#include "shape/cone.hpp"

#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_map>

class GraphicProgram
{
public:
    GraphicProgram() = default;
    ~GraphicProgram() = default;

    void init(int argc, char** argv);
    void start();

private:
    static constexpr float STEP_SIZE {10.0f};
    static constexpr float MIN_ZOOM {100.0f};
    static constexpr float MAX_ZOOM {2000.0f};
    static constexpr float LOOK_RADIUS {20.f};

    static int _sceneIndex;

    enum class ShapeType
    {
        Cylinder,
        Sphere,
        Cube,
        Cone,
        Light
    };

    class Scene
    {
    public:
        void addQuadric(ShapeType type, std::unique_ptr<Shape3D> quadric)
        {
            _quadrics.emplace(type, std::move(quadric));
        }

        Shape3D* getQuadric(ShapeType type) const
        {
            auto it = _quadrics.find(type);

            return (it != _quadrics.end()) ? it->second.get() : nullptr;
        }

        void draw()
        {
            for (const auto& [type, shape] : _quadrics)
            {
                shape->draw();
            }
        }

       Scene() = default;
       ~Scene() = default;

    private:
        std::unordered_map<ShapeType, std::unique_ptr<Shape3D>> _quadrics;
    };

    static Scene scene1;
    static Scene scene2;
    static Scene scene3;

    /* camera pos */
    static float _cameraX;
    static float _cameraY;
    static float _cameraZ;

    static float _lightX;
    static float _lightY;
    static float _lightZ;

    static float _zoom;

    void initLight();

    void initScene1();
    void initScene2();
    void initScene3();

    static void drawLine();
    static void drawAxes();
    static void drawGrid();
    static void display();
    static void displayScene1();
    static void displayScene2();
    static void displayScene3();

    static void moveLightAndSphere(float dx, float dy, float dz);

    static void reshape(int w, int h);

    static void handleMouseButton(int button, int state, int x, int y);
    static void handleKeyPress(u_char key, int x, int y);
    static void handleSpecialKeyPress(int key, int x, int y);
};

#endif
