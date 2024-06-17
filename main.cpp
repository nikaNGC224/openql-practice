#include <GL/glut.h>
#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "OpenGL Practice\n";

    /* init GLUT and create window */
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutCreateWindow("OpenGL Practice");

    while (true)
    {
        /* see black window */
    }

	/* register callbacks */

	/* enter GLUT event processing cycle */
}
