/**
 * 	Отрисовка простых приметивов
*/
#include <GL/glut.h>

// функция отрисовки
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(3);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(-1, 1);
	glVertex2d(1, -1);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2f(0.5, 1);
	glVertex2d(1, 0);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	// Инициализация glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	// Устанавливает начало системы координат в центр экрана
	glLoadIdentity();
	// Функция для отрисовки, при обновлении экрана
	glutDisplayFunc(display);
	// Начало цикла программы
	glutMainLoop();
	return 0;
}
