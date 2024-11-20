#include "graphic_program.hpp"

#include <cmath>
#include <iostream>

/* static fields */
int GraphicProgram::_sceneIndex {};

GraphicProgram::Scene GraphicProgram::scene1;
GraphicProgram::Scene GraphicProgram::scene2;
GraphicProgram::Scene GraphicProgram::scene3;

float GraphicProgram::_cameraX {300.0f};
float GraphicProgram::_cameraY {};
float GraphicProgram::_cameraZ {500.0f};

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
    glDepthFunc(GL_LESS);

    glutInitWindowSize(800, 600);
    glutCreateWindow("Graphics");

    // Задаем цвет фона
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Регистрация функций обратного вызова
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
    glEnable(GL_LIGHT0);         // Включаем источник света 0

    // Настраиваем базовые параметры света
    GLfloat light_ambient[] {0.2f, 0.2f, 0.2f, 1.0f};  // Фоновый свет
    GLfloat light_diffuse[] {1.0f, 1.0f, 1.0f, 1.0f};  // Диффузное освещение
    GLfloat light_specular[] {1.0f, 1.0f, 1.0f, 1.0f}; // Зеркальное освещение

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Включаем материал для объектов, которые будут освещаться
    GLfloat mat_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat mat_diffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {128.0f};  // Уровень блеска

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void GraphicProgram::initScene1()
{
    scene1.addQuadric(ShapeType::Cylinder, std::make_unique<Cylinder>(50.0f, 360.0f));
    scene1.addQuadric(ShapeType::Sphere, std::make_unique<Sphere>(300.0f));

    scene1.getQuadric(ShapeType::Cylinder)->setPosition(50.0f, 40.0f, 0.0f);
    scene1.getQuadric(ShapeType::Sphere)->setPosition(50.0f, 40.0f, 0.0f);
}

void GraphicProgram::initScene2()
{
    scene2.addQuadric(ShapeType::Cube, std::make_unique<Cube>(100.0f));
    scene2.addQuadric(ShapeType::Cone, std::make_unique<Cone>(50.0f, 100.0f));

    scene2.getQuadric(ShapeType::Cube)->setPosition(0.0f, -100.0f, 50.0f);
    scene2.getQuadric(ShapeType::Cone)->setPosition(0.0f, 100.0f, 0.0f);
}

void GraphicProgram::initScene3()
{
    scene3.addQuadric(ShapeType::Cube, std::make_unique<Cube>(100.0f, Shape3D::Mode::Solid));
    scene3.addQuadric(ShapeType::Sphere, std::make_unique<Sphere>(50.0f, Shape3D::Mode::Solid));
    scene3.addQuadric(ShapeType::Cone, std::make_unique<Cone>(50.0f, 100.0f));

    scene3.addQuadric(ShapeType::Light, std::make_unique<Sphere>(5.0f));

    scene3.getQuadric(ShapeType::Cube)->setPosition(100.0f, -150.0f, 100.0f);
    scene3.getQuadric(ShapeType::Sphere)->setPosition(100.0f, 0.0f, 100.0f);
    scene3.getQuadric(ShapeType::Cone)->setPosition(100.0f, 150.0f, 50.0f);

    scene3.getQuadric(ShapeType::Light)->setPosition(_lightX, _lightY, _lightZ);
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
    // Позиция камеры
    gluLookAt(_zoom + _cameraX, _cameraY, _zoom,  // Позиция камеры
                      _cameraX, _cameraY,  0.0f,  // Точка, на которую смотрим
                          0.0f,     0.0f,  1.0f); // Вектор "вверх" вдоль оси Z

    // Рисуем сетку
    drawGrid();

    // Рисуем оси
    drawAxes();

    // Рисуем цилиндр
    scene1.draw();
}

void GraphicProgram::displayScene2()
{
    // Позиция камеры
    gluLookAt(_zoom + _cameraX, _cameraY, _zoom,  // Позиция камеры
                      _cameraX, _cameraY,  0.0f,  // Точка, на которую смотрим
                          0.0f,     0.0f,  1.0f); // Вектор "вверх" вдоль оси Z

    /* todo: make longer */
    drawGrid();

    // Рисуем оси
    drawAxes();

    scene2.draw();
}

void GraphicProgram::displayScene3()
{
    // Позиция камеры
    gluLookAt(_zoom + _cameraX, _cameraY, _zoom,  // Позиция камеры
                      _cameraX, _cameraY,  0.0f,  // Точка, на которую смотрим
                          0.0f,     0.0f,  1.0f); // Вектор "вверх" вдоль оси Z

    glEnable(GL_NORMALIZE);

    drawGrid();
    drawAxes();

    // Обновляем позицию источника света
    GLfloat light_position[] {_lightX, _lightY, _lightZ, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    scene3.draw();
}

void GraphicProgram::moveLightAndSphere(float dx, float dy, float dz)
{
    _lightX += dx;
    _lightY += dy;
    _lightZ += dz;

    scene3.getQuadric(ShapeType::Light)->setPosition(_lightX, _lightY, _lightZ);
}

void GraphicProgram::reshape(int w, int h)
{
    // Устанавливаем окно просмотра
    glViewport(0, 0, w, h);

    // Переходим в матрицу проекций
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(w) / static_cast<double>(h), MIN_ZOOM, MAX_ZOOM);

    // Возвращаемся к модельной матрице
    glMatrixMode(GL_MODELVIEW);
}

void GraphicProgram::handleMouseButton(int button, int state, int x, int y)
{
    // Проверяем, прокручено ли колёсико вверх или вниз
    if (button == 3 && state == GLUT_UP)
    {  // Колёсико прокручено вверх
        _zoom -= STEP_SIZE;
        if (_zoom < MIN_ZOOM)
        {
            _zoom = MIN_ZOOM;
        }
    }
    else if (button == 4 && state == GLUT_UP)
    {  // Колёсико прокручено вниз
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
            _cameraX -= STEP_SIZE;
            break;
        }

        case 's':
        case 'S':
        {
            _cameraX += STEP_SIZE;
            break;
        }

        case 'a':
        case 'A':
        {
            _cameraY -= STEP_SIZE;
            break;
        }

        case 'd':
        case 'D':
        {
            _cameraY += STEP_SIZE;
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
                if (auto* sphere = dynamic_cast<Sphere*>(scene1.getQuadric(ShapeType::Sphere)))
                {
                    sphere->incRadius(STEP_SIZE);
                }

                break;
            }

            case GLUT_KEY_DOWN:
            {
                if (auto* sphere = dynamic_cast<Sphere*>(scene1.getQuadric(ShapeType::Sphere)))
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
                if (auto* cone = dynamic_cast<Cone*>(scene2.getQuadric(ShapeType::Cone)))
                {
                    cone->incRotationAngleX(STEP_SIZE);
                }

                break;
            }

            case GLUT_KEY_RIGHT:
            {
                if (auto* cone = dynamic_cast<Cone*>(scene2.getQuadric(ShapeType::Cone)))
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
                //_lightZ += STEP_SIZE;
                moveLightAndSphere(0.0f, 0.0f, STEP_SIZE);
                std::cout << _lightX << " " << _lightY << " " << _lightZ << "\n";
                break;
            }

            case GLUT_KEY_DOWN:
            {
                //_lightZ -= STEP_SIZE;
                moveLightAndSphere(0.0f, 0.0f, -STEP_SIZE);
                std::cout << _lightX << " " << _lightY << " " << _lightZ << "\n";
                break;
            }

            case GLUT_KEY_LEFT:
            {
                //_lightY -= STEP_SIZE;
                moveLightAndSphere(0.0f, -STEP_SIZE, 0.0f);
                std::cout << _lightX << " " << _lightY << " " << _lightZ << "\n";
                break;
            }

            case GLUT_KEY_RIGHT:
            {
                //_lightY += STEP_SIZE;
                moveLightAndSphere(0.0f, STEP_SIZE, 0.0f);
                std::cout << _lightX << " " << _lightY << " " << _lightZ << "\n";
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
