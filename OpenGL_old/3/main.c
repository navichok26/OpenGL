/**
 * 	Взаимодействие с клавиатурой
 * 	При нажатии на 1, 2, 3 треугольник будет менять цвет.
*/
#include <GL/glut.h>

typedef struct Color {
	float red;
	float green;
	float blue;
} Color;

Color color = {1, 0, 0};

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
		break;
		
		case 49:
			color.red = 1;
			color.green = 0;
			color.blue = 0;
		break;

		case 50:
			color.red = 0;
			color.green = 1;
			color.blue = 0;
		break;

		case 51:
			color.red = 0;
			color.green = 0;
			color.blue = 1;
		break;
	}
}

// функция отрисовки
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
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

	// Функция отрисовки окна в режиме ожидания
	glutIdleFunc(display);
	
	// Для обычных клавиш
	glutKeyboardFunc(keyboard);
	// Для специальных клавиш
	glutSpecialFunc(NULL);

	glutMainLoop();
	return 0;
}
