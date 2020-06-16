#pragma once
#include <iostream>

#include <GL/glew.h>

static const char* GlErrorValues[] = { "Inavlid Enum","Invalid Value","Invalid Operation", "Stack Overflow","Stack_UnderFlow","Out Of Memeory" };
#define GetGlErrorString(x) (((x-0x500)>=0 && (x-0x500<6))?GlErrorValues[x-0x500]:"UnKnown")
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

inline void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
inline bool GLLogCall(const char* FunctionName, const char* File, int Line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error]: " << GetGlErrorString(error) << std::endl;
		std::cout << "[FunctionName]:" << FunctionName << std::endl << "[File]:" << File << std::endl << "[Line]:" << Line << std::endl;
		std::cout << "------------------------------------------------------------------------------------------";
		return false;
	}
	return true;
}
