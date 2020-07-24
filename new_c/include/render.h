#ifndef RENDER_H
#define RENDER_H 
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "math_3d.h"
#include <float.h>

typedef struct Window
{
	GLFWwindow *p;
	uint16_t width;
	uint16_t hight;
} Window;

Window main_window;
GLuint VBO;
GLuint IBO;
GLuint gWorldLocation;
static float Scale = 0.0f;

void glfw_init();
void key_callback(
	GLFWwindow *window,
	int key,
	int scancode,
	int action,
	int mode
);
void window_init(uint16_t width, uint16_t hight, char *title);

void createBuffers();
void createVertexBuffer();
void createIndexBuffer();

void mainloop();
void render();

#endif
