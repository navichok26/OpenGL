#ifndef SHADERS_H
#define SHADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLES3/gl3.h>
#include <assert.h>

typedef struct ShadersLoad
{
	char *vertex;
	char *fragment;
} ShadersLoad;

GLuint shader_program;
GLuint gWorldLocation;

void load_shaders(ShadersLoad shaders);
char* read_shader_file(char *filename);
void add_shader(char *text_program, GLenum shader_type);
void compile_shaders();
void include_shaders_variables();

#endif
