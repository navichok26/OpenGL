#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>


int width = 1280;
int height = 720;



void key_callback(GLFWwindow *window, 
                int key, 
                int scancode, 
                int action, 
                int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}



int main(int argc, char **argv) {
    GLFWwindow *window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (!window) {
        return -2;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwSetKeyCallback(window, key_callback);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // левая вершина
         0.5f, -0.5f, 0.0f, // правая вершина
         0.0f,  0.5f, 0.0f  // верхняя вершина   
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}