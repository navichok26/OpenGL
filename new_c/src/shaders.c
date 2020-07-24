#include "shaders.h"

void load_shaders(ShadersLoad shaders)
{
	shader_program = glCreateProgram();
    if (shader_program == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

	if (shaders.vertex)
	{
		char *text_program = read_shader_file(shaders.vertex);
		add_shader(text_program, GL_VERTEX_SHADER);
		free(text_program);
	}
	if (shaders.fragment)
	{
		char *text_program = read_shader_file(shaders.fragment);
		add_shader(text_program, GL_FRAGMENT_SHADER);
		free(text_program);
		
	}
	compile_shaders();
}

char* read_shader_file(char *filename)
{
	FILE *file;
	uint64_t size_buffer = 10;
	char *buffer = (char*) malloc(size_buffer * sizeof(char));
	char ch;
	file = fopen(filename, "r");
	if (!file)
	{
		printf("Error file dont open\n");
		exit(-1);
	}
	uint64_t count = 0;
	ch = fgetc(file);
	while (!feof(file)) 
	{
		if (ferror(file))
		{
			printf("Error file\n");
			exit(-1);
		}
		if (count % size_buffer == 0) 
		{
			char tmp[strlen(buffer)];
			strcpy(tmp, buffer);
			uint32_t buffer_len = strlen(buffer);
			free(buffer);
			buffer = (char*) malloc((buffer_len + size_buffer) * sizeof(char));
			strcpy(buffer, tmp);
		}
		buffer[count] = ch;
		count++;
		ch = fgetc(file);
	}
	fclose(file);
	return buffer;	
}

void add_shader(char *shader_text, GLenum shader_type)
{
	GLuint ShaderObj = glCreateShader(shader_type);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", shader_type);
        exit(0);
    }

	const GLchar* p[1];
    p[0] = shader_text;
    GLint Lengths[1];
    Lengths[0]= strlen(shader_text);	
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", shader_type, InfoLog);
        exit(1);
    }

    glAttachShader(shader_program, ShaderObj);
}

void compile_shaders()
{
	GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(shader_program, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
	}

    glValidateProgram(shader_program);
    glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(shader_program, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(shader_program);

	include_shaders_variables();
}

void include_shaders_variables()
{
	gWorldLocation = glGetUniformLocation(shader_program, "gWorld");
}