#ifndef GRAPHIC_PROGRAM_HPP
#define GRAPHIC_PROGRAM_HPP

#include "shape/cylinder.hpp"
#include "shape/sphere.hpp"
#include "shape/cube.hpp"
#include "shape/cone.hpp"

#include <memory>
#include <vector>
#include <algorithm>

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

    /* Предлагаю сделать вектор объектов в сцене, и отдельно в ините объектов вводить параметры*/

    struct SceneParams
    {
        float cylinderRadius;
        float cylinderHeight;
        float sphereRadius;
        float cubeSize;
        float coneRadius;
        float coneHeight;
    };

    class Scene
    {
    public:
        /* todo: change to map */
        std::vector<std::unique_ptr<Shape3D>> quadrics;

        void addQuadric(std::unique_ptr<Shape3D> quadric)
        {
            quadrics.push_back(std::move(quadric));
        }

        void draw()
        {
            std::for_each(quadrics.begin(),
                          quadrics.end(),
                          [](const std::unique_ptr<Shape3D>& q) { q->draw(); });
        }

       Scene() = default;
       ~Scene() = default;
    };

    static Scene scene1;
    static Scene scene2;
    static Scene scene3;

    /* camera pos */
    static float _cameraX;
    static float _cameraY;
    static float _cameraZ;

    static float _zoom;

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

    static void reshape(int w, int h);

    static void handleMouseButton(int button, int state, int x, int y);
    static void handleKeyPress(u_char key, int x, int y);
    static void handleSpecialKeyPress(int key, int x, int y);
};

#endif
