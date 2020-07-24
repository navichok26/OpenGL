#include "utils.hpp"

Window::Window(unsigned int width, unsigned int height, string title) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL) {
        cerr << "Невозможно открыть окно GLFW." << endl;
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
}

Window::~Window() {
    glfwDestroyWindow(this->window);
}

void Window::keyCallback(GLFWwindow* window, 
                        int key, 
                        int scancode, 
                        int action, 
                        int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwDestroyWindow(window);
    }
}

int Window::getShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(this->window);
}

unsigned int Window::getWidth() {
    return this->width;
}

unsigned int Window::getHeight() {
    return this->height;
}

string Window::getTitle() {
    return this->title;
}


void initGlfw() {
    // Инициализируем GLFW
    if (!glfwInit()) {
        cerr << "Ошибка при инициализации GLFWn" << endl;
        exit(-1);
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
    glfwWindowHint(GLFW_VERSION_MAJOR, 3); // Мы хотим использовать OpenGL 3.3
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
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





