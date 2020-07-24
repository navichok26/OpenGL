#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

using namespace std;

class Window {
private:
    GLFWwindow *window;
    unsigned int width;
    unsigned int height;
    string title;
public: 
    Window(unsigned int width, unsigned height, string title);
    ~Window();

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    int getShouldClose();
    // Обертка
    void swapBuffers();

    unsigned int getWidth();
    unsigned int getHeight();
    string getTitle();
};

void initGlfw();
GLuint LoadShaders(const string vertexFilePath, const string fragmentFilePath);

#endif
