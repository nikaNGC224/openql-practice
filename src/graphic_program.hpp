#ifndef GRAPHIC_PROGRAM_HPP
#define GRAPHIC_PROGRAM_HPP

#include "shape/cylinder.hpp"
#include "shape/sphere.hpp"
#include "shape/cube.hpp"
#include "shape/cone.hpp"
#include "scene/scene.hpp"
#include "light.hpp"

class GraphicProgram
{
public:
    GraphicProgram() = default;
    ~GraphicProgram() = default;

    void init(int argc, char** argv);
    void start();

private:
    static constexpr float STEP_SIZE {10.0f};
    static constexpr float SENSITIVITY = 0.1f;

    static int _sceneIndex;

    static Scene _scene1;
    static Scene _scene2;
    static Scene _scene3;

    static float _lightX;
    static float _lightY;
    static float _lightZ;

    static Light _light;

    static bool _isDragging; // Флаг удержания кнопки мыши
    static int _lastMouseX;      // Последняя позиция мыши по X
    static int _lastMouseY;      // Последняя позиция мыши по Y

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
    static void handleMouseMotion(int x, int y);
    static void handleKeyPress(u_char key, int x, int y);
    static void handleSpecialKeyPress(int key, int x, int y);
};

#endif
