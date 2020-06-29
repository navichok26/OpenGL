#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>


using namespace std;

const unsigned int width = 1280;
const unsigned int height = 720;

GLuint LoadShaders(const string vertexFilePath, const string fragmentFilePath);

int main(int argc, char **argv) {
    // Инициализируем GLFW
    if (!glfwInit()) {
        // fprintf(stderr, "Ошибка при инициализации GLFWn");
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
    glfwWindowHint(GLFW_VERSION_MAJOR, 3); // Мы хотим использовать OpenGL 3.3
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    
    GLFWwindow *window;
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (window == NULL) {
        // fprintf( stderr, "Невозможно открыть окно GLFW. Если у вас Intel GPU, то он не поддерживает версию 3.3. Попробуйте версию уроков для OpenGL 2.1.n" );
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Включим режим отслеживания нажатия клавиш, для проверки ниже
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    const GLfloat vertexBufferData[] = {
        -1.0, -1.0, 0.0,
        1.0, -1.0, 0.0,
        0.0, 1.0, 0.0
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
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Сбрасываем буферы
        glfwSwapBuffers(window);
    } // Проверяем нажатие клавиши Escape или закрытие окна
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0);

    glfwTerminate();
    return 0;
}

GLuint LoadShaders(const string vertexFilePath, const string fragmentFilePath) {
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Загрузка кода вершинного шейдера
    string vertexShaderCode;
    ifstream vertexShaderStream(vertexFilePath, ios::in);
    if (vertexShaderStream.is_open()) {
        stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        vertexShaderCode = sstr.str();
        vertexShaderStream.close();
    }
    
    // Загрузка кода фрагментного шейдера
    string fragmentShaderCode;
    ifstream fragmentShaderStream(fragmentFilePath, ios::in);
    if (fragmentShaderStream.is_open()) {
        stringstream sstr;
        sstr << fragmentShaderStream.rdbuf();
        fragmentShaderCode = sstr.str();
        fragmentShaderStream.close();
    } 

    GLint result = GL_FALSE;
    int infoLogLength;

    cout << "Компиляция шейдера: " << vertexFilePath << endl;
    const char *vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderId, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderId);

    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> vertexShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(
            vertexShaderId, 
            infoLogLength, 
            NULL, 
            &vertexShaderErrorMessage[0]
        );
        cout << &vertexShaderErrorMessage[0] << endl;
    } 



    cout << "Компиляция шейдера: " << fragmentFilePath << endl;
    const char *fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> fragmentShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(
            fragmentShaderId, 
            infoLogLength, 
            NULL, 
            &fragmentShaderErrorMessage[0]
        );
        cout << &fragmentShaderErrorMessage[0] << endl;
    }


    cout << "Создание шейдерной программы " << endl;
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> programErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programId, infoLogLength, NULL, &programErrorMessage[0]);
        cout << &programErrorMessage[0] << endl;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}





