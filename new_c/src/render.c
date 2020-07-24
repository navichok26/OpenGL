#include "render.h"

void glfw_init()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Ошибка инициализации GLFW\n");
		exit(-1);
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
    glfwWindowHint(GLFW_VERSION_MAJOR, 3); // Мы хотим использовать OpenGL 3.3
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
}

void key_callback(GLFWwindow *window,
		int key,
		int scancode,
		int action,
		int mode) 
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwDestroyWindow(window);
	}
}

void window_init(uint16_t width, uint16_t hight, char *title)
{
	main_window.p = glfwCreateWindow(width, hight, title, NULL, NULL);
	if (main_window.p == NULL) 
	{
        fprintf(stderr, "Ошибка создания окна\n");
        exit(-1);
    }
    main_window.width = width;
    main_window.hight = hight;
    glfwMakeContextCurrent(main_window.p);
    glfwSetKeyCallback(main_window.p, key_callback);
}

void createBuffers()
{
	createVertexBuffer();
	createIndexBuffer();
}

void createVertexBuffer()
{
	Vector3f Vertices[4] = {{-1.0f, -1.0f, 0.0f}, 
							{0.0f, -1.0f, 1.0f},
							{1.0f, -1.0f, 0.0f},
							{0.0f, 1.0f, 0.0f}};

 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void createIndexBuffer() 
{
	GLuint Indices[] = { 0, 3, 1,
                         1, 3, 2,
                         2, 3, 0,
                         0, 2, 1 };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void mainloop()
{
	glClearColor(0.0, 0.0, 0.4, 0.0);
	do
	{
		glfwPollEvents();

		render();

		glfwSwapBuffers(main_window.p);
	} while (glfwWindowShouldClose(main_window.p) == 0);
	glfwTerminate();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

    Scale += 0.01f;

    Matrix4f World;

    World.m[0][0] = 1.0f; World.m[0][1] = 0.0f; World.m[0][2] = 0.0f; World.m[0][3] = 0.0f;
    World.m[1][0] = 0.0f; World.m[1][1] = 1.0f; World.m[1][2] = 0.0f; World.m[1][3] = 0.0f;
    World.m[2][0] = 0.0f; World.m[2][1] = 0.0f; World.m[2][2] = 1.0f; World.m[2][3] = 0.0f;
    World.m[3][0] = 0.0f; World.m[3][1] = 0.0f; World.m[3][2] = 0.0f; World.m[3][3] = 1.0f;

    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
}