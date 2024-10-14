#include <GL/glut.h>
#include <GL/glu.h>

// Параметры цилиндра
GLUquadric* quadric = nullptr;
float radius = 1.0f;  // Радиус цилиндра
float height = 2.0f;  // Высота цилиндра
int slices = 20;      // Количество сегментов по окружности
int stacks = 10;      // Количество сегментов по высоте

void init()
{
    // Задаем цвет фона
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Инициализируем объект цилиндра
    gluNewQuadric();
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_LINE);  // Устанавливаем режим каркасного отображения
}

void drawAxes() {
    // Рисуем оси координат
    glBegin(GL_LINES);

    // Ось X (красная)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    // Ось Y (зеленая)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    // Ось Z (синяя)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);

    glEnd();
}

void display()
{
    // Очищаем буфер цвета и буфер глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Настраиваем камеру
    gluLookAt(4.0f, 4.0f, 4.0f,  // Позиция камеры
              0.0f, 0.0f, 0.0f,  // Точка, на которую смотрим
              0.0f, 1.0f, 0.0f); // Вектор "вверх"

    drawAxes();

    // Поворачиваем на -90 градусов вокруг оси X
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    // Рисуем цилиндр
    glColor3f(1.0f, 1.0f, 1.0f);  // Белый цвет цилиндра
    gluCylinder(quadric, radius, radius, height, slices, stacks);

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
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);

    // Возвращаемся к модельной матрице
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Wireframe Cylinder");

    // Инициализация OpenGL
    init();

    // Регистрация функций
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Основной цикл GLUT
    glutMainLoop();

    // Удаляем объект цилиндра при завершении
    gluDeleteQuadric(quadric);

    return 0;
}
