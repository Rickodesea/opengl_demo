#ifndef H_SHADER
#define H_SHADER

#include <SDL2/SDL.h>
#include "glad.h"

typedef struct {
	unsigned int id;
} Shader;

void shader_fileinit(Shader * this, const char * vertf, const char * fragf);
void shader_init(Shader * this, const char * vert, const char * frag);
void shader_delete(Shader * this);
void shader_use(Shader * this);
void shader_set_int(Shader * this, const char * name, int value);
void shader_set_float(Shader * this, const char * name, float value);

#endif