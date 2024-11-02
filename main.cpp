#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

// Параметры цилиндра
GLUquadric* quadric = nullptr;
float radius = 50.0f;  // Радиус цилиндра
float height = 360.0f; // Высота цилиндра
int slices = 20;       // Количество сегментов по окружности
int stacks = 10;       // Количество сегментов по высоте
float zoom = 700.0f;

// Параметры сферы
GLUquadric* sphereQuadric = nullptr;
float sphereRadius = 300.0f;  // Радиус сферы

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

int main(int argc, char** argv)
{
    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Wireframe Cylinder with Z Axis Up and Grid");

    // Инициализация OpenGL
    init();

    // Регистрация функций обратного вызова
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouseButton);

    // Основной цикл GLUT
    glutMainLoop();

    // Удаляем объект цилиндра при завершении
    gluDeleteQuadric(quadric);
}

void init()
{
    // Задаем цвет фона
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Инициализируем объект цилиндра
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_LINE);  // Устанавливаем режим каркасного отображения

    // Инициализируем объект сферы
    sphereQuadric = gluNewQuadric();
    gluQuadricDrawStyle(sphereQuadric, GLU_LINE);  // Устанавливаем режим каркасного отображения
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

    // Позиция камеры с учётом угла поворота вокруг оси Z
    gluLookAt(std::cos(cameraAngleZ) * zoom,
              std::sin(cameraAngleZ) * zoom,
              zoom + cameraOffsetZ, // Позиция камеры
              0.0f, 0.0f, 0.0f,     // Точка, на которую смотрим
              0.0f, 0.0f, 1.0f);    // Вектор "вверх" вдоль оси Z
    // @todo fix камеру, работает не очень
    // Подумать как будет удобнее

    // Рисуем сетку
    drawGrid();

    // Рисуем оси
    drawAxes();

    // Рисуем цилиндр
    glPushMatrix();  // Сохраняем текущую матрицу
    // Сместим цилиндр так, чтобы его центр основания был в точке (50, 40)
    glTranslatef(50.0f, 40.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);  // Белый цвет цилиндра
    gluCylinder(quadric, radius, radius, height, slices, stacks);
    glPopMatrix();  // Восстанавливаем матрицу

    // Рисуем сферу
    glPushMatrix();  // Сохраняем текущую матрицу
    glTranslatef(50.0f, 40.0f, 0.0f);  // Сместим сферу так, чтобы её центр был в точке (50, 40)
    glColor3f(1.0f, 1.0f, 0.0f);  // Жёлтый цвет сферы
    gluSphere(sphereQuadric, sphereRadius, slices, stacks);
    glPopMatrix();  // Восстанавливаем матрицу

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

    cameraAngleZ += dx * 0.001f;    // Регулируйте множитель для чувствительности
    cameraOffsetZ += dy * 1.0f;     // Обновляем смещение камеры вдоль оси Z

    lastMouseX = x;                // Обновляем последнюю позицию X
    lastMouseY = y;                // Обновляем последнюю позицию Y

    glutPostRedisplay();           // Перерисовываем сцену
}
