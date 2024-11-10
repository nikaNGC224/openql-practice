#include "graphic_program.hpp"

#include <cmath>

/* static fields */
int GraphicProgram::_sceneIndex {};

GraphicProgram::Scene GraphicProgram::scene1;
GraphicProgram::Scene GraphicProgram::scene2;
GraphicProgram::Scene GraphicProgram::scene3;

/* GraphicProgram::Scene GraphicProgram::scene1({ 50.0f, 360.0f, 300.0f });

GraphicProgram::Scene GraphicProgram::scene2({  0.0f,  0.0f,   0.0f,
                                              100.0f, 50.0f, 100.0f });

GraphicProgram::Scene GraphicProgram::scene3({ 50.0f,    50.0f,   50.0f,
                                               100.0f,  50.0f, 100.0f }); */

float GraphicProgram::_cameraX {300.0f};
float GraphicProgram::_cameraY {};
float GraphicProgram::_cameraZ {500.0f};

float GraphicProgram::_zoom {500.0f};

void GraphicProgram::init(int argc, char** argv)
{
    // Инициализация GLUT
    glutInit(&argc, argv);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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

    initScene1();
    initScene2();
    initScene3();
}

void GraphicProgram::initScene1()
{
    scene1.addQuadric(std::make_unique<Cylinder>(50.0f, 360.0f));
    scene1.addQuadric(std::make_unique<Sphere>(300.0f));

    scene1.quadrics.at(0)->setPosition(50.0f, 40.0f, 0.0f);
    scene1.quadrics.at(1)->setPosition(50.0f, 40.0f, 0.0f);
}

void GraphicProgram::initScene2()
{
    scene2.addQuadric(std::make_unique<Cube>(100.0f));
    scene2.addQuadric(std::make_unique<Cone>(50.0f, 100.0f));

    scene2.quadrics.at(0)->setPosition(0.0f, -100.0f, 50.0f);
    scene2.quadrics.at(1)->setPosition(0.0f, 100.0f, 0.0f);
}

void GraphicProgram::initScene3()
{
    scene3.addQuadric(std::make_unique<Sphere>(50.0f));
    scene3.addQuadric(std::make_unique<Cube>(100.0f));
    scene3.addQuadric(std::make_unique<Cone>(50.0f, 100.0f));

    scene3.quadrics.at(0)->setPosition(100.0f, 0.0f, 100.0f);
    scene3.quadrics.at(1)->setPosition(100.0f, -150.0f, 100.0f);
    scene3.quadrics.at(2)->setPosition(100.0f, 150.0f, 50.0f);
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

    /* todo: make universal func for  any line */
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

    // Позиция камеры
    /* Возможно, стоит менять zoom, чтобы всё было корректно */
    gluLookAt(_zoom + _cameraX, _cameraY, _zoom,  // Позиция камеры
                      _cameraX, _cameraY,  0.0f,  // Точка, на которую смотрим
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
    // Рисуем сетку
    drawGrid();

    // Рисуем оси
    drawAxes();

    // Рисуем цилиндр
    scene1.draw();
}

void GraphicProgram::displayScene2()
{
    /* todo: make longer */
    drawGrid();

    // Рисуем оси
    drawAxes();

    scene2.draw();
}

void GraphicProgram::displayScene3()
{
    drawAxes();

    scene3.draw();
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
        _zoom -= STEP_SIZE;  // Уменьшаем значение zoom, чтобы приблизить
        if (_zoom < MIN_ZOOM)
        {
            _zoom = MIN_ZOOM;  // Ограничиваем минимальное приближение
        }
    }
    else if (button == 4 && state == GLUT_UP)
    {  // Колёсико прокручено вниз
        _zoom += STEP_SIZE;  // Увеличиваем значение zoom, чтобы отдалить
        if (_zoom > MAX_ZOOM)
        {
            _zoom = MAX_ZOOM;  // Ограничиваем максимальное отдаление
        }
    }

    glutPostRedisplay();  // Перерисовываем сцену
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

    glutPostRedisplay();  // Перерисовываем сцену
}

void GraphicProgram::handleSpecialKeyPress(int key, int x, int y)
{
    if (_sceneIndex == 0)
    {
        switch (key)
        {
            case GLUT_KEY_UP:
            {
                auto sphere = dynamic_cast<Sphere*>(scene1.quadrics.at(1).get());
                sphere->incRadius(STEP_SIZE);
                break;
            }

            case GLUT_KEY_DOWN:
            {
                auto sphere = dynamic_cast<Sphere*>(scene1.quadrics.at(1).get());
                sphere->decRadius(STEP_SIZE);
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
            /* case GLUT_KEY_LEFT:
            {
                scene2._cone.incRotationAngleX(STEP_SIZE);
                auto cone = dynamic_cast<Sphere*>(scene2.quadrics.at(1).get());
                break;
            }

            case GLUT_KEY_RIGHT:
            {
                scene2._cone.decRotationAngleX(STEP_SIZE);
                break;
            } */

            default:
            {
                break;
            }
        }
    }

    glutPostRedisplay();
}
