/**
 * 	Отрисовка градиентного треугольника
*/
#include <GL/glut.h>

// функция отрисовки
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	// Отрисовка пямоугольника
	// glColor3f(1.0, 0.0, 0.0);
	// glBegin(GL_QUADS);
    //             glVertex3f(-0.5, 0.5, 0.0);
    //             glVertex3f( 0.5, 0.5, 0.0);
    //             glVertex3f( 0.5, -0.5, 0.0);
    //             glVertex3f(-0.5, -0.5, 0.0);
    //     glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-0.5, -0.5);
		
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(0.5, -0.5);

		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(0, 0.5);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
