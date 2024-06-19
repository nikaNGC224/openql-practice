#include <GL/glut.h>
#include <iostream>

void renderScene();
void changeSize(int width, int height);

int main(int argc, char **argv)
{
    std::cout << "OpenGL Practice\n";

    /* init GLUT and create window */
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 500);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutCreateWindow("OpenGL Practice");

	/* register callbacks */
    glutReshapeFunc(changeSize);
    glutDisplayFunc(renderScene);

	/* enter GLUT event processing cycle */
    glutMainLoop();
}

void renderScene()
{
    glClearColor(0.0, 0.749, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    {
        glVertex3f(-0.5, -0.5, -5.0);
        glVertex3f(0.5, 0.0, -5.0);
        glVertex3f(0.0, 0.5, -5.0);
    }
    glEnd();

    glutSwapBuffers();
}

void changeSize(int width, int height)
{
    // Prevent a divide by zero
    if (height == 0)
    {
        height = 1;
    }
    double ratio = 1.0 * width / height;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, width, height);

    // Set the correct perspective
    gluPerspective(45, ratio, 1, 1000);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}
