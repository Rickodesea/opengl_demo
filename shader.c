#include <SDL2/SDL.h>
#include "glad.h"

#include "shader.h"

static void run_compile_errors(unsigned int shader, const char * type);

void shader_fileinit(Shader * this, const char * vertf, const char * fragf)
{
	SDL_RWops * vf = SDL_RWFromFile(vertf, "r");
	Sint64 vs = SDL_RWsize(vf);
	char vbuf[vs + 1]; vbuf[vs] = 0;
	SDL_RWread(vf, vbuf, vs, 1);

	SDL_RWops * ff = SDL_RWFromFile(fragf, "r");
	Sint64 fs = SDL_RWsize(ff);
	char fbuf[fs + 1]; fbuf[fs] = 0;
	SDL_RWread(ff, fbuf, fs, 1);

	shader_init(this, vbuf, fbuf);
}

void shader_init(Shader * this, const char * vert, const char * frag)
{
	// vertex shader
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vert, 0);
	glCompileShader(vertex);
	run_compile_errors(vertex, "VERTEX");

	// fragment shader
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &frag, 0);
	glCompileShader(fragment);
	run_compile_errors(fragment, "FRAGMENT");

	// shader program
	this->id = glCreateProgram();
	glAttachShader(this->id, vertex);
	glAttachShader(this->id, fragment);
	glLinkProgram(this->id);
	run_compile_errors(this->id, "PROGRAM");

	// delete the shaders that are now linked
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void shader_delete(Shader * this)
{
	glDeleteProgram(this->id);
}

void shader_use(Shader * this) 
{
	glUseProgram(this->id);
}

void shader_set_int(Shader * this, const char * name, int value)
{
	glUniform1i(glGetUniformLocation(this->id, name), value);
}

void shader_set_float(Shader * this, const char * name, float value)
{
	glUniform1f(glGetUniformLocation(this->id, name), value);
}

static void run_compile_errors(unsigned int shader, const char * type)
{
	int success;
	char infoLog[1024];
	
	if (strcmp(type, "PROGRAM") == 0) 
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		
		if (success == 0) 
		{
			glGetShaderInfoLog(shader, 1024, 0, infoLog);
			SDL_Log(
				"ERROR::PROGRAM_LINKING_ERROR of type: %s\n"
				"%s\n"
				"------------------------------------------------",
				type, infoLog
			);
		}
	} 
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success == 0) 
		{
			glGetShaderInfoLog(shader, 1024, 0, infoLog);
			SDL_Log(
				"ERROR::SHADER_COMPILATION_ERROR of type: %s\n"
				"%s\n"
				"------------------------------------------------",
				type, infoLog
			);
		}
	} 
}
