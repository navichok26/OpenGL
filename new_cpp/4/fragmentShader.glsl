#version 330 core

in vec3 Oposition;

out vec4 color;

uniform float timeValue;

void main() {
    //color = vec4(abs(Oposition.xy)*sin(timeValue)*5, Oposition.x+Oposition.y*cos(timeValue), 1);
    color = vec4(abs(Oposition.x * sin(timeValue)-0.5), abs(Oposition.y * sin(timeValue)+0.5), 1, 1);
}
