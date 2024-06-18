#include <GL/glut.h>
#include <iostream>

void renderScene()
{
    glClearColor(0.0, 0.749, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    {
        glVertex3f(-0.5, -0.5, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    std::cout << "OpenGL Practice\n";

    /* init GLUT and create window */
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutCreateWindow("OpenGL Practice");

	/* register callbacks */
    glutDisplayFunc(renderScene);

	/* enter GLUT event processing cycle */
    glutMainLoop();
}
