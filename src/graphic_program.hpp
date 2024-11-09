#ifndef GRAPHIC_PROGRAM_HPP
#define GRAPHIC_PROGRAM_HPP

#include "shape/cylinder.hpp"
#include "shape/sphere.hpp"
#include "shape/cube.hpp"
#include "shape/cone.hpp"

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

    static int _sceneIndex;

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
        Scene(const SceneParams& params)
        :   _cylinder(params.cylinderRadius, params.cylinderHeight),
            _sphere(params.sphereRadius),
            _cube(params.cubeSize),
            _cone(params.coneRadius, params.coneHeight)
        {
            _cylinder.setPosition(50.0f, 40.0f, 0.0f);
            _sphere.setPosition(50.0f, 40.0f, 0.0f);
            _cube.setPosition(0.0f, -550.0f, 0.0f);
            _cone.setPosition(0.0f, -400.0f, 0.0f);
        }

        Cylinder _cylinder;
        Sphere _sphere;
        Cube _cube;
        Cone _cone;
    };



    static Scene scene1;
    //static Scene scene2;

    static float _zoom;

    static float _cameraX;
    static float _cameraY;

    static void drawLine();
    static void drawAxes();
    static void drawGrid();
    static void display();
    static void displayScene1();
    static void displayScene2();

    static void reshape(int w, int h);

    static void handleMouseButton(int button, int state, int x, int y);
    static void handleKeyPress(u_char key, int x, int y);
    static void handleSpecialKeyPress(int key, int x, int y);
};

#endif
