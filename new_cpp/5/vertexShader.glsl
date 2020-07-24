#version 330 core

layout(location = 0) in vec3 position;

out vec3 Oposition;

uniform mat4 matrixMove;

void main() {
    // vec3 new_position = vec3(position*abs(sin(timeValue)));
    Oposition = position;
    gl_Position = matrixMove * vec4(position, 1.0);
}
