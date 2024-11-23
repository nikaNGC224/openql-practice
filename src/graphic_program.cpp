#include "graphic_program.hpp"

/* static fields */
int GraphicProgram::_sceneIndex {};

Scene GraphicProgram::_scene1;
Scene GraphicProgram::_scene2;
Scene GraphicProgram::_scene3;

Camera Scene::camera;

float GraphicProgram::_lightX {};
float GraphicProgram::_lightY {};
float GraphicProgram::_lightZ {};

Light GraphicProgram::_light(GL_LIGHT0);

bool GraphicProgram::_isDragging {false};
int GraphicProgram::_lastMouseX {};
int GraphicProgram::_lastMouseY {};

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
    glutMotionFunc(handleMouseMotion);
    glutKeyboardFunc(handleKeyPress);
    glutSpecialFunc(handleSpecialKeyPress);

    initLight();

    initScene1();
    initScene2();
    initScene3();
}

void GraphicProgram::initLight()
{
    _light.enable();
    _light.setAmbient({0.2f, 0.2f, 0.2f, 1.0f});
    _light.setDiffuse({1.0f, 1.0f, 1.0f, 1.0f});
    _light.setSpecular({1.0f, 1.0f, 1.0f, 1.0f});
    _light.setPosition({_lightX, _lightY, _lightZ, 1.0f});
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
    //_scene3.addShape(Scene::ShapeType::Cone, std::make_unique<Cone>(50.0f, 100.0f, Shape3D::Mode::Solid));
    _scene3.addShape(Scene::ShapeType::Cube, std::make_unique<Cube>(100.0f, Shape3D::Mode::Solid));

    _scene3.addShape(Scene::ShapeType::Light, std::make_unique<Sphere>(5.0f));

    _scene3.getQuadric(Scene::ShapeType::Sphere)->setPosition(100.0f, 0.0f, 100.0f);
    //_scene3.getQuadric(Scene::ShapeType::Cone)->setPosition(100.0f, 150.0f, 50.0f);
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

    Vector3 cameraPos = Scene::camera.getPosition();

    gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,  // Позиция камеры
              0.0f, 0.0f, 0.0f,                      // Точка, на которую смотрим
              0.0f, 0.0f, 1.0f);                     // Вектор "вверх"

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

    _light.setPosition({_lightX, _lightY, _lightZ, 1.0f});

    _scene3.draw();
}

void GraphicProgram::moveLightAndSphere(float dx, float dy, float dz)
{
    _lightX += dx;
    _lightY += dy;
    _lightZ += dz;

    _light.updatePosition({_lightX, _lightY, _lightZ, 1.0f});
    _scene3.getQuadric(Scene::ShapeType::Light)->setPosition(_lightX, _lightY, _lightZ);
}

void GraphicProgram::reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(w) / static_cast<double>(h), Camera::MIN_ZOOM, Camera::MAX_ZOOM);

    glMatrixMode(GL_MODELVIEW);
}

void GraphicProgram::handleMouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            _isDragging = true;
            _lastMouseX = x;
            _lastMouseY = y;
        }
        else if (state == GLUT_UP)
        {
            _isDragging = false;
        }
    }

    // Управление зумом через колёсико мыши
    if (button == 3 && state == GLUT_UP) // Прокрутка вверх
    {
        Scene::camera.adjustRadius(-STEP_SIZE);
    }
    else if (button == 4 && state == GLUT_UP) // Прокрутка вниз
    {
        Scene::camera.adjustRadius(STEP_SIZE);
    }

    glutPostRedisplay();
}

void GraphicProgram::handleMouseMotion(int x, int y)
{
    if (_isDragging)
    {
        int deltaX = x - _lastMouseX;
        int deltaY = y - _lastMouseY;

        Scene::camera.adjustAzimuth(static_cast<float>(-deltaX) * SENSITIVITY); // Горизонтальное вращение
        Scene::camera.adjustZenith(static_cast<float>(-deltaY) * SENSITIVITY); // Вертикальный наклон

        _lastMouseX = x;
        _lastMouseY = y;

        glutPostRedisplay();
    }
}


void GraphicProgram::handleKeyPress(u_char key, int x, int y)
{
    /* enum class or smth like that */
    switch (key)
    {
        case '\t':
        {
            _sceneIndex = (_sceneIndex + 1) % 3;
            break;
        }

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
