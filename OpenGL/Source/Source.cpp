#include <assert.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Utils.h"
#include "glUtils.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};
enum class ShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};
static ShaderProgramSource ParseShader(const char* i_FilePath)
{
	std::ifstream stream(i_FilePath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[static_cast<int>(type)] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}
unsigned int CompileShader(unsigned int i_ShaderType, std::string i_ShaderSource) // i_Shader type is a GL_Enum which is a typedef
{
	unsigned int id = glCreateShader(i_ShaderType);
	const char * src = i_ShaderSource.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id,GL_COMPILE_STATUS,&result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(_malloca(length * sizeof(char)));
		glGetShaderInfoLog(id,length,&length,message);
		std::cout << "Error:" << message << std::endl;
		return 0;
	}
	return id;
}
static unsigned int CreateShader(const std::string i_VertexShader, const std::string i_FragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, i_VertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, i_FragmentShader);

	glAttachShader(program,vs);
	glAttachShader(program,fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;

}

int main(void)
{
	srand((unsigned int)time(0));
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(1280, 720, "OPEN GL", NULL, NULL);  //Create Window
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);                                 //Make the window's context current
	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error" << std::endl;
	}
	{
		float vertexPositions[] =
		{ -0.5f,-0.5f,
			0.0f,-0.5f,
			0.0f, 0.5f,
			-0.5f,  0.5f

		};
		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};
		std::cout << glGetString(GL_VERSION) << std::endl;
		VertexBuffer vb(vertexPositions,8*sizeof(float));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr));
		GLCall(glEnableVertexAttribArray(0));
		IndexBuffer ib(indices,6);
		ShaderProgramSource shaderSource = ParseShader("Resources/Shaders/BasicTriangle.shader");	
		unsigned int shader = CreateShader(shaderSource.VertexShader, shaderSource.FragmentShader);
		GLCall(glUseProgram(shader));

		int uColorLocation = glGetUniformLocation(shader, "u_Color");
		ASSERT(uColorLocation != -1);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR);

			//glDrawArrays(GL_TRIANGLES,0,3);
			GLCall(glUniform4f(uColorLocation, GetNCV(RandomInRange(1, 255)), 0.0f, 0.0f, 0.1f));
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		glDeleteProgram(shader);
	}
	
	glfwTerminate();
	return 0;
}