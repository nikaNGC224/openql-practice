#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>


/* @todo move to other files */
/* @todo change to eng comments */
/* @todo fix camera to more convenient usage */
class Shape3D
{
public:
    virtual ~Shape3D() = default;

    void draw() const
    {
        glPushMatrix();  // Сохраняем текущую матрицу
        glTranslatef(_x, _y, _z);
        drawShape();
        glPopMatrix();  // Восстанавливаем матрицу
    }

    void setPosition(float x, float y, float z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

protected:
    const int SLICES {20}; // Количество сегментов по окружности
    const int STACKS {10}; // Количество сегментов по высоте

    float _x{}, _y{}, _z{};
private:
    virtual void drawShape() const = 0;
};

class Cylinder : public Shape3D
{
public:
    Cylinder() = delete;

    Cylinder(float radius, float height)
        : _radius(radius), _height(height)
    {
        _quadric = gluNewQuadric();
        gluQuadricDrawStyle(_quadric, GLU_LINE);
    }

    ~Cylinder()
    {
        gluDeleteQuadric(_quadric);
    }

private:
    GLUquadric* _quadric;
    float _radius;
    float _height;

    void drawShape() const override
    {
        glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет цилиндра
        gluCylinder(_quadric, _radius, _radius, _height, SLICES, STACKS);
    }
};

class Sphere : public Shape3D
{
public:
    Sphere()
    {
        _quadric = gluNewQuadric();
        gluQuadricDrawStyle(_quadric, GLU_LINE);
    }

    ~Sphere()
    {
        gluDeleteQuadric(_quadric);
    }

    float getRadius() const
    {
        return _radius;
    }

    void setRadius(float radius)
    {
        _radius = radius;
    }

    float getMinRadius() const
    {
        return MIN_RADIUS;
    }

    float getMaxRadius() const
    {
        return MAX_RADIUS;
    }

private:
    const float MIN_RADIUS {300.0f};
    const float MAX_RADIUS {MIN_RADIUS * 1.5f};

    GLUquadric* _quadric;
    float _radius {MIN_RADIUS};

    void drawShape() const override
    {
        glColor3f(1.0f, 1.0f, 0.0f);  // Жёлтый цвет сферы
        gluSphere(_quadric, _radius, SLICES, STACKS);
    }
};

/* Global objects */
Cylinder cylinder(50.0f, 360.0f);
Sphere sphere;

/* @todo mb remove from global? */
float zoom = 700.0f;

float cameraAngleZ = 0.0f;  // Угол поворота камеры вокруг оси Z
float cameraOffsetZ = 0.0f;  // Смещение камеры вдоль оси Z
int lastMouseX;             // Последняя координата X мыши
int lastMouseY;

void init();
void drawAxes();
void drawGrid();
void display();
void reshape(int w, int h);
void handleMouseButton(int button, int state, int x, int y);
void handleMouseMove(int x, int y);
void handleKeyPress(u_char key, int x, int y);

int main(int argc, char** argv)
{
    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Graphics");

    // Инициализация OpenGL
    init();

    // Регистрация функций обратного вызова
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouseButton);
    glutKeyboardFunc(handleKeyPress);

    // Основной цикл GLUT
    glutMainLoop();
}

void init()
{
    // Задаем цвет фона
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    cylinder.setPosition(50.0f, 40.0f, 0.0f);
    sphere.setPosition(50.0f, 40.0f, 0.0f);
}

void drawAxes()
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

    glEnd();

    glLineWidth(1.0f);
}

void drawGrid()
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

void display()
{
    // Очищаем буфер цвета и буфер глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Позиция камеры
    gluLookAt(std::cos(cameraAngleZ) * zoom,
              std::sin(cameraAngleZ) * zoom,
              zoom + cameraOffsetZ, // Позиция камеры
              0.0f, 0.0f, 0.0f,     // Точка, на которую смотрим
              0.0f, 0.0f, 1.0f);    // Вектор "вверх" вдоль оси Z

    // Рисуем сетку
    drawGrid();

    // Рисуем оси
    drawAxes();

    // Рисуем цилиндр
    cylinder.draw();

    // Рисуем сферу
    sphere.draw();

    // Переключаем буферы
    glutSwapBuffers();
}

void reshape(int w, int h)
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

void handleMouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        lastMouseX = x;
        lastMouseY = y;
        glutMotionFunc(handleMouseMove);  // Включаем обработчик движения мыши
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        glutMotionFunc(nullptr);  // Отключаем обработчик при отпускании
    }

    // Проверяем, прокручено ли колёсико вверх или вниз
    if (button == 3 && state == GLUT_UP)
    {  // Колёсико прокручено вверх
        zoom -= 10.0f;  // Уменьшаем значение zoom, чтобы приблизить
        if (zoom < 100.0f)
        {
            zoom = 100.0f;  // Ограничиваем минимальное приближение
        }
    }
    else if (button == 4 && state == GLUT_UP)
    {  // Колёсико прокручено вниз
        zoom += 10.0f;  // Увеличиваем значение zoom, чтобы отдалить
        if (zoom > 2000.0f) // @todo мах и мин значения можно вынести в константы
        {
            zoom = 2000.0f;  // Ограничиваем максимальное отдаление
        }
    }

    glutPostRedisplay();  // Перерисовываем сцену
}

void handleMouseMove(int x, int y)
{
    int dx = x - lastMouseX;       // Изменение координаты X
    int dy = y - lastMouseY;        // Изменение координаты Y

    cameraAngleZ -= dx * 0.001f;    // Регулируйте множитель для чувствительности
    cameraOffsetZ += dy * 1.0f;     // Обновляем смещение камеры вдоль оси Z

    lastMouseX = x;                // Обновляем последнюю позицию X
    lastMouseY = y;                // Обновляем последнюю позицию Y

    glutPostRedisplay();           // Перерисовываем сцену
}

void handleKeyPress(u_char key, int x, int y)
{
    if (key == 'a' || key == 'A')  // Проверяем нажатие клавиши A
    {
        if (sphere.getRadius() > sphere.getMinRadius())
        {
            sphere.setRadius(sphere.getRadius() - 10.0f);
        }
        else
        {
            sphere.setRadius(sphere.getMinRadius());
        }
    }
    else if (key == 'd' || key == 'D')  // Проверяем нажатие клавиши D
    {
        if (sphere.getRadius() < sphere.getMaxRadius())
        {
            sphere.setRadius(sphere.getRadius() + 10.0f);
        }
        else
        {
            sphere.setRadius(sphere.getMaxRadius());

        }
    }

    glutPostRedisplay();  // Перерисовываем сцену
}
