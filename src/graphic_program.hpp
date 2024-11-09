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
    static Cylinder _cylinder;
    static Sphere _sphere;
    static Cube _cube;
    static Cone _cone;

    static float _zoom;

    static float _cameraX;
    static float _cameraY;

    static void drawAxes();
    static void drawGrid();
    static void display();
    static void reshape(int w, int h);
    static void handleMouseButton(int button, int state, int x, int y);
    static void handleKeyPress(u_char key, int x, int y);
    static void handleSpecialKeyPress(int key, int x, int y);
};

#endif
