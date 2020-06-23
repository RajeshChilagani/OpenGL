#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glUtils.h"

Shader::Shader(const std::string& i_Filepath): m_FilePath(i_Filepath),m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(i_Filepath);
	m_RendererID = CreateShader(source.VertexShader, source.FragmentShader);
}
Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}
void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}
void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}
ShaderProgramSource Shader::ParseShader(const std::string& i_FilePath)
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
unsigned int Shader::CreateShader(const std::string i_VertexShader, const std::string i_FragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, i_VertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, i_FragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
unsigned int Shader::CompileShader(unsigned int i_ShaderType, std::string i_ShaderSource)
{
	unsigned int id = glCreateShader(i_ShaderType);
	const char* src = i_ShaderSource.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(_malloca(length * sizeof(char)));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Error:" << message << std::endl;
		return 0;
	}
	return id;
}
void Shader::SetUniform1i(const std::string& i_Name, int v)
{
	GLCall(glUniform1i(GetUniformLocation(i_Name), v));
}
void Shader::SetUniform4f(const std::string& i_Name, float v1, float v2, float v3, float v4) 
{
	GLCall(glUniform4f(GetUniformLocation(i_Name),v1,v2,v3,v4));
}
void Shader::SetUniformMat4f(const std::string& i_Name, glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(i_Name), 1, GL_FALSE, &matrix[0][0]));
}
int Shader::GetUniformLocation(const std::string& i_Name) 
{
	if (m_UniformLocationCache.find(i_Name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[i_Name];
	GLCall(int location = glGetUniformLocation(m_RendererID, i_Name.c_str()));
	if (location == -1)
		std::cout << "Warning: Uniform " << i_Name << " Does not exist" << std::endl;
	m_UniformLocationCache[i_Name] = location;
	return location;
}