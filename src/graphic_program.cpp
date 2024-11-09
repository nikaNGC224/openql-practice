#include "graphic_program.hpp"

Cylinder GraphicProgram::_cylinder(50.0f, 360.0f);
Sphere   GraphicProgram::_sphere;
Cube     GraphicProgram::_cube(100.0f);
Cone     GraphicProgram::_cone(50.0f, 100.0f);

float GraphicProgram::_zoom {500.0f};

float GraphicProgram::_cameraX {100.0f};
float GraphicProgram::_cameraY {};

void GraphicProgram::init(int argc, char** argv)
{
    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Graphics");

    // Задаем цвет фона
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    _cylinder.setPosition(50.0f, 40.0f, 0.0f);
    _sphere.setPosition(50.0f, 40.0f, 0.0f);
    _cube.setPosition(0.0f, -550.0f, 0.0f);
    _cone.setPosition(0.0f, -400.0f, 0.0f);

    // Регистрация функций обратного вызова
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouseButton);
    glutKeyboardFunc(handleKeyPress);
    glutSpecialFunc(handleSpecialKeyPress);
}

void GraphicProgram::start()
{
    // Основной цикл GLUT
    glutMainLoop();
}

void GraphicProgram::drawAxes()
{
    glLineWidth(2.0f);

    // Рисуем оси координат
    glBegin(GL_LINES);

    // Ось X (красная)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    // Ось Y (зеленая)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    // Ось Z (синяя)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    // Ось X под примитивом (красная)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, -400.0f, 0.0f);
    glVertex3f(100.0f, -400.0f, 0.0f);

    glEnd();

    glLineWidth(1.0f);
}

void GraphicProgram::drawGrid()
{
    glColor3f(0.5f, 0.5f, 0.5f);  // Серый цвет для сетки
    glBegin(GL_LINES);

    // Рисуем горизонтальные линии
    for (float y = -100.0f; y <= 100.0f; y += 10.0f)
    {
        glVertex3f(-100.0f, y, 0.0f);
        glVertex3f(100.0f, y, 0.0f);
    }

    // Рисуем вертикальные линии
    for (float x = -100.0f; x <= 100.0f; x += 10.0f)
    {
        glVertex3f(x, -100.0f, 0.0f);
        glVertex3f(x, 100.0f, 0.0f);
    }

    glEnd();
}

void GraphicProgram::display()
{
    // Очищаем буфер цвета и буфер глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Позиция камеры
    gluLookAt(_zoom + _cameraX, _cameraY, _zoom,  // Позиция камеры
              _cameraX, _cameraY, 0.0f,           // Точка, на которую смотрим
              0.0f, 0.0f, 1.0f);                  // Вектор "вверх" вдоль оси Z

    // Рисуем сетку
    drawGrid();

    // Рисуем оси
    drawAxes();

    // Рисуем цилиндр
    _cylinder.draw();
    _sphere.draw();
    _cube.draw();
    _cone.draw();

    // Переключаем буферы
    glutSwapBuffers();
}

void GraphicProgram::reshape(int w, int h)
{
    // Устанавливаем окно просмотра
    glViewport(0, 0, w, h);

    // Переходим в матрицу проекций
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 2000.0);

    // Возвращаемся к модельной матрице
    glMatrixMode(GL_MODELVIEW);
}

void GraphicProgram::handleMouseButton(int button, int state, int x, int y)
{
    // Проверяем, прокручено ли колёсико вверх или вниз
    if (button == 3 && state == GLUT_UP)
    {  // Колёсико прокручено вверх
        _zoom -= 10.0f;  // Уменьшаем значение zoom, чтобы приблизить
        if (_zoom < 100.0f)
        {
            _zoom = 100.0f;  // Ограничиваем минимальное приближение
        }
    }
    else if (button == 4 && state == GLUT_UP)
    {  // Колёсико прокручено вниз
        _zoom += 10.0f;  // Увеличиваем значение zoom, чтобы отдалить
        if (_zoom > 2000.0f) // @todo мах и мин значения можно вынести в константы
        {
            _zoom = 2000.0f;  // Ограничиваем максимальное отдаление
        }
    }

    glutPostRedisplay();  // Перерисовываем сцену
}

void GraphicProgram::handleKeyPress(u_char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
        {
            _cameraX -= 10.0f;
            break;
        }

        case 's':
        case 'S':
        {
            _cameraX += 10.0f;
            break;
        }

        case 'a':
        case 'A':
        {
            _cameraY -= 10.0f;
            break;
        }

        case 'd':
        case 'D':
        {
            _cameraY += 10.0f;
            break;
        }

        default:
        {
            break;
        }
    }

    glutPostRedisplay();  // Перерисовываем сцену
}

void GraphicProgram::handleSpecialKeyPress(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
        {
            if (_sphere.getRadius() < _sphere.getMaxRadius())
            {
                _sphere.setRadius(_sphere.getRadius() + 10.0f);
            }
            else
            {
                _sphere.setRadius(_sphere.getMaxRadius());

            }
            break;
        }

        case GLUT_KEY_DOWN:
        {
            if (_sphere.getRadius() > _sphere.getMinRadius())
            {
                _sphere.setRadius(_sphere.getRadius() - 10.0f);
            }
            else
            {
                _sphere.setRadius(_sphere.getMinRadius());
            }

            break;
        }

        case GLUT_KEY_LEFT:
        {
            _cone.setRotationAngleX(_cone.getRotationAngleX() + 10.0f);
            break;
        }

        case GLUT_KEY_RIGHT:
        {
            _cone.setRotationAngleX(_cone.getRotationAngleX() - 10.0f);
            break;
        }

        default:
        {
            break;
        }
    }

    glutPostRedisplay();
}
