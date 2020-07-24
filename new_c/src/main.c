#include "render.h"
#include "shaders.h"
#define WIDTH 1280
#define HIGHT 720

int main()
{
	glfw_init();
	window_init(WIDTH, HIGHT, "OpenGL");
	createBuffers();
	ShadersLoad shaders = {"vertexShader.glsl", NULL};
	load_shaders(shaders);

	mainloop();
	return 0;
}