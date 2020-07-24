#version 330 core

layout(location = 0) in vec3 Position;

out vec4 color;

uniform mat4 matrixMove;

void main() {
    color = vec4(clamp(Position, 0.0, 1.0), 1.0);
    gl_Position = matrixMove * vec4(Position, 1.0);
}
