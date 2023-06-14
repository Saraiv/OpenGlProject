#pragma once

#include <iostream>
#include <fstream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

typedef struct {
	GLenum       type;
	const char*  filename;
	GLuint       shader;
} ShaderInfo;

GLuint LoadShaders(ShaderInfo*);