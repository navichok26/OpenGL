#include "utils.hpp"

int main(int argc, char **argv) {
    initGlfw();
    
    Window mainWin(1280, 720, "OpenGL");

    const GLfloat vertexBufferData[] = {
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
        0.0, 0.5, 0.0
    };

	float scale = 0.0;

	float matrixMove[4][4] = {
		{1.0, 0.0, 0.0, 0.0},
		{0.0, 1.0, 0.0, 0.0},
		{0.0, 0.0, 1.0, 0.0},
		{0.0, 0.0, 0.0, 1.0}
	};

    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(vertexBufferData), 
        vertexBufferData,
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3*sizeof(float),
        (void*)0
    );

    GLuint programId = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
    glUseProgram(programId);

    glClearColor(0.0, 0.0, 0.4, 0.0);

    do{
        glfwPollEvents();

		// Помещаем время в переменную шейдеров timeValue
        float timeValue = glfwGetTime();
        int timeValueLocation = glGetUniformLocation(programId, "timeValue");
        glUniform1f(timeValueLocation, timeValue);

		scale += 0.001;
		matrixMove[0][0] = sin(scale);
        matrixMove[1][1] = cos(scale);
        matrixMove[2][2] = sin(scale);
		int matrixMoveLocation = glGetUniformLocation(programId, "matrixMove");
		glUniformMatrix4fv(matrixMoveLocation, 1, GL_TRUE, &matrixMove[0][0]);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Сбрасываем буферы
        mainWin.swapBuffers();
    } // Проверяем закрытие окна
    while (mainWin.getShouldClose() == 0);

    glfwTerminate();
    return 0;
}
