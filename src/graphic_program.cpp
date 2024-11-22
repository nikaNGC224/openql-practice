#include "graphic_program.hpp"

#include <cmath>
#include <iostream>

/* static fields */
int GraphicProgram::_sceneIndex {};

Scene GraphicProgram::_scene1;
Scene GraphicProgram::_scene2;
Scene GraphicProgram::_scene3;

float CameraPos::cameraX {300.0f};
float CameraPos::cameraY {};
float CameraPos::cameraZ {500.0f};

float GraphicProgram::_lightX {};
float GraphicProgram::_lightY {};
float GraphicProgram::_lightZ {};

float GraphicProgram::_zoom {500.0f};

void GraphicProgram::init(int argc, char** argv)
{
    // Инициализация GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glutInitWindowSize(800, 600);
    glutCreateWindow("Graphics");

    /* background color */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /* callback funcs */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouseButton);
    glutKeyboardFunc(handleKeyPress);
    glutSpecialFunc(handleSpecialKeyPress);

    initLight();

    initScene1();
    initScene2();
    initScene3();
}

void GraphicProgram::initLight()
{
    glEnable(GL_LIGHT0);

    /* base parameters of light */
    GLfloat light_ambient[] {0.2f, 0.2f, 0.2f, 1.0f};  // Фоновый свет
    GLfloat light_diffuse[] {1.0f, 1.0f, 1.0f, 1.0f};  // Диффузное освещение
    GLfloat light_specular[] {1.0f, 1.0f, 1.0f, 1.0f}; // Зеркальное освещение

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void GraphicProgram::initScene1()
{
    _scene1.addShape(Scene::ShapeType::Cylinder, std::make_unique<Cylinder>(50.0f, 360.0f));
    _scene1.addShape(Scene::ShapeType::Sphere, std::make_unique<Sphere>(300.0f));

    _scene1.getQuadric(Scene::ShapeType::Cylinder)->setPosition(50.0f, 40.0f, 0.0f);
    _scene1.getQuadric(Scene::ShapeType::Sphere)->setPosition(50.0f, 40.0f, 0.0f);
}

void GraphicProgram::initScene2()
{
    _scene2.addShape(Scene::ShapeType::Cube, std::make_unique<Cube>(100.0f));
    _scene2.addShape(Scene::ShapeType::Cone, std::make_unique<Cone>(50.0f, 100.0f));

    _scene2.getQuadric(Scene::ShapeType::Cube)->setPosition(0.0f, -100.0f, 50.0f);
    _scene2.getQuadric(Scene::ShapeType::Cone)->setPosition(0.0f, 100.0f, 0.0f);
}

void GraphicProgram::initScene3()
{
    _scene3.addShape(Scene::ShapeType::Sphere, std::make_unique<Sphere>(50.0f, Shape3D::Mode::Solid));
    _scene3.addShape(Scene::ShapeType::Cone, std::make_unique<Cone>(50.0f, 100.0f, Shape3D::Mode::Solid));
    _scene3.addShape(Scene::ShapeType::Cube, std::make_unique<Cube>(100.0f, Shape3D::Mode::Solid));

    _scene3.addShape(Scene::ShapeType::Light, std::make_unique<Sphere>(5.0f));

    _scene3.getQuadric(Scene::ShapeType::Sphere)->setPosition(100.0f, 0.0f, 100.0f);
    _scene3.getQuadric(Scene::ShapeType::Cone)->setPosition(100.0f, 150.0f, 50.0f);
    _scene3.getQuadric(Scene::ShapeType::Cube)->setPosition(100.0f, -150.0f, 100.0f);

    _scene3.getQuadric(Scene::ShapeType::Light)->setPosition(_lightX, _lightY, _lightZ);
}

void GraphicProgram::start()
{
    // Основной цикл GLUT
    glutMainLoop();
}

void GraphicProgram::drawLine()
{
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    /* todo: make universal func for any line */
    // Ось X под примитивом (красная)
    glColor3f(    1.0f,    0.0f, 0.0f);
    glVertex3f(-100.0f, -400.0f, 0.0f);
    glVertex3f( 100.0f, -400.0f, 0.0f);

    glEnd();

    glLineWidth(1.0f);
}

void GraphicProgram::drawAxes()
{
    glLineWidth(2.0f);

    // Рисуем оси координат
    glBegin(GL_LINES);

    // Ось X (красная)
    glColor3f(   1.0f, 0.0f, 0.0f);
    glVertex3f(  0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    // Ось Y (зеленая)
    glColor3f( 0.0f,   1.0f, 0.0f);
    glVertex3f(0.0f,   0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    // Ось Z (синяя)
    glColor3f( 0.0f, 0.0f,   1.0f);
    glVertex3f(0.0f, 0.0f,   0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();

    glLineWidth(1.0f);
}

void GraphicProgram::drawGrid()
{
    glColor3f(0.5f, 0.5f, 0.5f);  // Серый цвет для сетки
    glBegin(GL_LINES);

    // Рисуем горизонтальные линии
    for (float y = -100.0f; y <= 100.0f; y += STEP_SIZE)
    {
        glVertex3f(-100.0f, y, 0.0f);
        glVertex3f( 100.0f, y, 0.0f);
    }

    // Рисуем вертикальные линии
    for (float x = -100.0f; x <= 100.0f; x += STEP_SIZE)
    {
        glVertex3f(x, -100.0f, 0.0f);
        glVertex3f(x,  100.0f, 0.0f);
    }

    glEnd();
}

void GraphicProgram::display()
{
    /* clear color buffer & depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(_zoom + CameraPos::cameraX, CameraPos::cameraY, _zoom,  // Позиция камеры
                      CameraPos::cameraX, CameraPos::cameraY,  0.0f,  // Точка, на которую смотрим
                          0.0f,     0.0f,  1.0f); // Вектор "вверх" вдоль оси Z

    /* add map */
    switch (_sceneIndex)
    {
        case 0:
        {
            displayScene1();
            break;
        }

        case 1:
        {
            displayScene2();
            break;
        }

        case 2:
        {
            displayScene3();
        }

        default:
        {
            break;
        }
    }

    // Переключаем буферы
    glutSwapBuffers();
}

void GraphicProgram::displayScene1()
{
    drawGrid();
    drawAxes();
    _scene1.draw();
}

void GraphicProgram::displayScene2()
{
    /* todo: make longer */
    drawGrid();
    drawAxes();
    _scene2.draw();
}

void GraphicProgram::displayScene3()
{
    glEnable(GL_NORMALIZE);

    drawGrid();
    drawAxes();

    GLfloat light_position[] {_lightZ, _lightY, _lightX, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    _scene3.draw();
}

void GraphicProgram::moveLightAndSphere(float dx, float dy, float dz)
{
    _lightX += dx;
    _lightY += dy;
    _lightZ += dz;

    _scene3.getQuadric(Scene::ShapeType::Light)->setPosition(_lightX, _lightY, _lightZ);
}

void GraphicProgram::reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(w) / static_cast<double>(h), MIN_ZOOM, MAX_ZOOM);

    glMatrixMode(GL_MODELVIEW);
}

void GraphicProgram::handleMouseButton(int button, int state, int x, int y)
{
    /* check scroll */
    if (button == 3 && state == GLUT_UP)
    {
        _zoom -= STEP_SIZE;
        if (_zoom < MIN_ZOOM)
        {
            _zoom = MIN_ZOOM;
        }
    }
    else if (button == 4 && state == GLUT_UP)
    {
        _zoom += STEP_SIZE;
        if (_zoom > MAX_ZOOM)
        {
            _zoom = MAX_ZOOM;
        }
    }

    glutPostRedisplay();
}

void GraphicProgram::handleKeyPress(u_char key, int x, int y)
{
    /* enum class or smth like that */
    switch (key)
    {
        case 'w':
        case 'W':
        {
            CameraPos::cameraX -= STEP_SIZE;
            break;
        }

        case 's':
        case 'S':
        {
            CameraPos::cameraX += STEP_SIZE;
            break;
        }

        case 'a':
        case 'A':
        {
            CameraPos::cameraY -= STEP_SIZE;
            break;
        }

        case 'd':
        case 'D':
        {
            CameraPos::cameraY += STEP_SIZE;
            break;
        }

        case '\t':
            _sceneIndex = (_sceneIndex + 1) % 3;

        default:
        {
            break;
        }
    }

    glutPostRedisplay();
}

void GraphicProgram::handleSpecialKeyPress(int key, int x, int y)
{
    if (_sceneIndex == 0)
    {
        switch (key)
        {
            case GLUT_KEY_UP:
            {
                if (auto* sphere = dynamic_cast<Sphere*>(_scene1.getQuadric(Scene::ShapeType::Sphere)))
                {
                    sphere->incRadius(STEP_SIZE);
                }

                break;
            }

            case GLUT_KEY_DOWN:
            {
                if (auto* sphere = dynamic_cast<Sphere*>(_scene1.getQuadric(Scene::ShapeType::Sphere)))
                {
                    sphere->decRadius(STEP_SIZE);
                }

                break;
            }

            default:
            {
                break;
            }
        }
    }
    else if (_sceneIndex == 1)
    {
        switch (key)
        {
            case GLUT_KEY_LEFT:
            {
                if (auto* cone = dynamic_cast<Cone*>(_scene2.getQuadric(Scene::ShapeType::Cone)))
                {
                    cone->incRotationAngleX(STEP_SIZE);
                }

                break;
            }

            case GLUT_KEY_RIGHT:
            {
                if (auto* cone = dynamic_cast<Cone*>(_scene2.getQuadric(Scene::ShapeType::Cone)))
                {
                    cone->decRotationAngleX(STEP_SIZE);
                }

                break;
            }

            default:
            {
                break;
            }
        }
    }
    else if (_sceneIndex == 2)
    {
        switch (key)
        {
            case GLUT_KEY_UP:
            {
                moveLightAndSphere(0.0f, 0.0f, STEP_SIZE);
                break;
            }

            case GLUT_KEY_DOWN:
            {
                moveLightAndSphere(0.0f, 0.0f, -STEP_SIZE);
                break;
            }

            case GLUT_KEY_LEFT:
            {
                moveLightAndSphere(0.0f, -STEP_SIZE, 0.0f);
                break;
            }

            case GLUT_KEY_RIGHT:
            {
                moveLightAndSphere(0.0f, STEP_SIZE, 0.0f);
                break;
            }

            default:
            {
                break;
            }
        }
    }

    glutPostRedisplay();
}
